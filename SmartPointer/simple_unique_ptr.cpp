#include <utility>
#include <iostream>

template <typename T>
struct default_deleter {
    void operator()(T* ptr) {
        delete ptr;
    }
};

template <typename T, typename Deleter = default_deleter<T>>
class unique_ptr {
public:
    unique_ptr(): m_pointer(nullptr) {}
    unique_ptr(T* p, Deleter deleter = Deleter()): m_pointer(p), m_deleter(deleter) {}
    unique_ptr(unique_ptr&& x): m_pointer(x.m_pointer), m_deleter(std::move(x.m_deleter)) {
        x.m_pointer = nullptr;
    }
    unique_ptr& operator=(unique_ptr&& rhs) {
        auto new_pointer = rhs.m_pointer;
        auto new_deleter = std::move(rhs.m_deleter);
        rhs.m_pointer = nullptr;
        if (m_pointer != nullptr) {
            m_deleter(m_pointer);
        }
        m_pointer = new_pointer;
        m_deleter = std::move(new_deleter);
    }
    ~unique_ptr() {
        if (m_pointer != nullptr) {
            m_deleter(m_pointer);
        }
    }
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    T& operator*() { return *m_pointer; }
    T* operator->() { return m_pointer; }
    T* get() { return m_pointer; }
private:
    T* m_pointer;
    Deleter m_deleter;
};

struct A {
    int a;
    double b;
};

auto borrow_int(int* pi) {
    std::cout << "int = " << *pi << std::endl;
}

auto consume_A(unique_ptr<A> pa) {
    std::cout << "a = " << pa->a << std::endl;
    std::cout << "b = " << pa->b << std::endl;
}

int main() {
    unique_ptr<int> empty;
    auto p1 = unique_ptr<int>(new int);
    *p1 = 1;
    auto p2 = unique_ptr<A>(new A);
    p2.get()->a = 42;
    p2->b = 3.1415926;

    //use raw pointer
    borrow_int(p1.get());

    //transfer ownership
    consume_A(std::move(p2));
}