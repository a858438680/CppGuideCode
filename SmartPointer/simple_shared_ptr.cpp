#include <utility>
#include <iostream>
#include <atomic>

template <typename T>
struct deleter_base {
    virtual void operator()(T* ptr) = 0;
    virtual deleter_base* copy() const = 0;
    virtual ~deleter_base() = 0;
};

template <typename T>
deleter_base<T>::~deleter_base() {}

template <typename T, typename Deleter>
struct deleter_derived: public deleter_base<T> {
    deleter_derived(Deleter deleter): m_deleter(deleter) {}
    virtual void operator()(T* ptr) override {
        m_deleter(ptr);
    }
    virtual deleter_base<T>* copy() const override {
        return new deleter_derived<T, Deleter>(m_deleter);
    }
    Deleter m_deleter;
};

template <typename T>
struct default_deleter {
    void operator()(T* ptr) {
        delete ptr;
    }
};

template <typename T>
class shared_ptr {
public:
    shared_ptr(): m_count(nullptr), m_pointer(nullptr), m_deleter(nullptr) {}
    template <typename Deleter = default_deleter<T>>
    shared_ptr(T* p, Deleter deleter = Deleter())
        : m_count(new std::atomic<size_t>(1))
        , m_pointer(p)
        , m_deleter(new deleter_derived<T, Deleter>(deleter))
    {}
    shared_ptr(const shared_ptr& x)
        : m_count(x.m_count)
        , m_pointer(x.m_pointer)
        , m_deleter(x.m_deleter->copy())
    {
        m_count->fetch_add(1, std::memory_order_relaxed);
    }
    shared_ptr(shared_ptr&& x)
        : m_count(x.m_count)
        , m_pointer(x.m_pointer)
        , m_deleter(x.m_deleter->copy())
    {
        x.m_pointer = nullptr;
    }
    shared_ptr& operator=(shared_ptr rhs) {
        using std::swap;
        swap(m_count, rhs.m_count);
        swap(m_pointer, rhs.m_pointer);
        swap(m_deleter, rhs.m_deleter);
    }
    ~shared_ptr() {
        if (m_pointer != nullptr) {
            if (m_count->fetch_sub(1, std::memory_order_relaxed) == 1) {
                (*m_deleter)(m_pointer);
                delete m_count;
            }
        }
        delete m_deleter;
    }
    T& operator*() { return *m_pointer; }
    T* operator->() { return m_pointer; }
    T* get() { return m_pointer; }
private:
    std::atomic<size_t>* m_count;
    T* m_pointer;
    deleter_base<T>* m_deleter;
};

struct A {
    A() { std::cout << "A constructed" << std::endl; }
    ~A() { std::cout << "A destructed" << std::endl; }
    int a;
    double b;
};

auto borrow_int(shared_ptr<int> pi) {
    std::cout << "int = " << *pi << std::endl;
}

auto consume_A(shared_ptr<A> pa) {
    std::cout << "a = " << pa->a << std::endl;
    std::cout << "b = " << pa->b << std::endl;
}

int main() {
    shared_ptr<int> empty;
    auto p1 = shared_ptr<int>(new int);
    *p1 = 1;
    auto p2 = shared_ptr<A>(new A, [](A* ptr){
        std::cout << "in lambda" << std::endl;
        delete ptr;
    });
    p2.get()->a = 42;
    p2->b = 3.1415926;

    //copy shared_ptr
    borrow_int(p1);

    //copy shared_ptr
    consume_A(p2);
}