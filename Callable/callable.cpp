#include <cassert>
#include <type_traits>
#include <functional>
#include <string>

using namespace std::literals::string_literals;

template <typename T>
T add(T a, T b) {
    return a + b;
}

template <typename T>
struct add_t {
    virtual T do_add(T, T) const = 0;

    virtual ~add_t() = 0;
};

template <typename T>
add_t<T>::~add_t() {}

template <typename T>
struct normal_add_t: add_t<T> {
    virtual T do_add(T a, T b) const override {
        return a + b;
    }
};

template <typename T>
struct bias_add_t: add_t<T> {
    T t_;

    bias_add_t(T t): t_(t) {}

    virtual T do_add(T a, T b) const override {
        return do_bias_add(a, b);
    }

    T do_normal_add(T a, T b) const {
        return a + b;
    }

    T do_bias_add(T a, T b) const {
        return t_ + (a + b);
    }

    T operator()(T a, T b) const {
        return t_ + (a + b);
    }
};

template <typename T>
auto bias_add(T bias) {
    return bias_add_t{bias};
}

struct generic_add_t {
    template <typename T>
    T operator()(T a, T b) const {
        return a + b;
    }
};

struct sub_t {
    template <typename T>
    T operator()(T a, T b) const {
        return a - b;
    }
};

inline constexpr generic_add_t generic_add{};
inline constexpr sub_t sub{};

int main() {
    assert(add(1, 2) == 3);
    assert((&add<int>)(1, 2) == 3);
    // assert(std::invoke(add, 1, 2) == 3); -> compile time error, add is not a function
    assert(std::invoke(add<int>, 1, 2) == 3);

    assert(add("a"s, "b"s) == "ab"s);
    assert((&add<std::string>)("a"s, "b"s) == "ab"s);
    // assert(std::invoke(add, "a"s, "b"s) == "ab"s); -> compile time error, add is not a function
    assert(std::invoke(add<std::string>, "a"s, "b"s) == "ab"s);

    // pointers to member functions, use object
    auto bias10_add = bias_add_t<int>{10};

    auto p_do_bias_add = &decltype(bias10_add)::do_normal_add;
    assert((bias10_add.*p_do_bias_add)(1, 2) == 3);
    assert(std::invoke(p_do_bias_add, bias10_add, 1, 2) == 3);
    p_do_bias_add = &decltype(bias10_add)::do_bias_add;
    assert((bias10_add.*p_do_bias_add)(1, 2) == 13);
    assert(std::invoke(p_do_bias_add, bias10_add, 1, 2) == 13);

    // pointers to member functions, use reference_wrapper to object
    auto normal_add = normal_add_t<int>{};
    auto p_do_add = &add_t<int>::do_add;

    std::reference_wrapper<add_t<int>> ref_add{normal_add};
    assert((ref_add.get().*p_do_add)(1, 2) == 3);
    assert(std::invoke(p_do_add, ref_add, 1, 2) == 3);
    ref_add = bias10_add;
    assert((ref_add.get().*p_do_add)(1, 2) == 13);
    assert(std::invoke(p_do_add, ref_add, 1, 2) == 13);

    // pointers to member functions, use pointers to object
    add_t<int>* p_add{&normal_add};
    assert(((*p_add).*p_do_add)(1, 2) == 3);
    assert(std::invoke(p_do_add, p_add, 1, 2) == 3);
    p_add = &bias10_add;
    assert(((*p_add).*p_do_add)(1, 2) == 13);
    assert(std::invoke(p_do_add, p_add, 1, 2) == 13);

    // pointers to data members, use object
    auto p_bias = &decltype(bias10_add)::t_;
    assert(bias10_add.*p_bias == 10);
    assert(std::invoke(p_bias, bias10_add) == 10);

    // pointers to data members, use reference_wrapper to object
    std::reference_wrapper<bias_add_t<int>> ref_bias_add{bias10_add};
    assert(ref_bias_add.get().*p_bias == 10);
    assert(std::invoke(p_bias, ref_bias_add) == 10);

    // pointers to data members, use reference_wrapper to object
    bias_add_t<int>* p_bias_add{&bias10_add};
    assert((*p_bias_add).*p_bias == 10);
    assert(std::invoke(p_bias, p_bias_add) == 10);

    // funtion object
    assert(generic_add(1, 2) == 3);
    assert(std::invoke(generic_add, 1, 2) == 3);
    assert(generic_add("a"s, "b"s) == "ab"s);
    assert(std::invoke(generic_add, "a"s, "b"s) == "ab"s);
    assert(bias10_add(1, 2) == 13);
    assert(std::invoke(bias10_add, 1, 2) == 13);
    assert(sub(3, 2) == 1);
    assert(std::invoke(sub, 3, 2) == 1);

    //higher order function
    assert(bias_add(20)(1, 2) == 23);
}