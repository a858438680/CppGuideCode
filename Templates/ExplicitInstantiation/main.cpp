#include <iostream>
#include "add.h"

int main() {
    using namespace std::literals::string_literals;
    std::cout << add(1, 2) << std::endl;
    std::cout << add("hello"s, "world"s) << std::endl;
    std::cout << add(1., 2.) << std::endl;
}