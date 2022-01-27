#include <memory>
#include <iostream>

struct A {
    A(int x): x(x) { std::cout << "constructed node " << x << std::endl; }
    ~A() { std::cout << "destructed node " << x << std::endl; }
    std::unique_ptr<A> next;
    int x;
};

int main() {
    {
        auto node1 = std::make_unique<A>(1);
        auto node2 = std::make_unique<A>(2);
        node1->next = std::move(node2);
    }
    {
        auto node3 = std::make_unique<A>(3);
        auto node4 = std::make_unique<A>(4);
        node3->next = std::move(node4);
        node3->next->next = std::move(node3);
    }
}