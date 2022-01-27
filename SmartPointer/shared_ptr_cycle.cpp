#include <memory>
#include <iostream>

struct A {
    A(int x): x(x) { std::cout << "constructed node " << x << std::endl; }
    ~A() { std::cout << "destructed node " << x << std::endl; }
    std::shared_ptr<A> next;
    int x;
};

int main() {
    {
        auto node1 = std::make_shared<A>(1);
        auto node2 = std::make_shared<A>(2);
        node1->next = node2;
    }
    {
        auto node3 = std::make_shared<A>(3);
        auto node4 = std::make_shared<A>(4);
        node3->next = node4;
        node4->next = node3;
    }
}