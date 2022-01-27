#include <iostream>

template <typename Derived>
class Singleton {
public:
    static Derived& getInstance() {
        static Derived instance;
        return instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
protected:
    Singleton() = default;
    ~Singleton() = default;
};

struct config: public Singleton<config> {
    config(): a(0), b(1) {}
    int a;
    int b;
};

int main() {
    std::cout << "a = " << config::getInstance().a << std::endl;
    std::cout << "b = " << config::getInstance().b << std::endl;
    //compile error:
    //auto config_copy = config::getInstance();
}