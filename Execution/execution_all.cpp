#include "execution.hpp"

using namespace standard::execution;
using namespace std::literals::string_view_literals;

int main() {
    auto op = connect(just_sender{1, 3.1415926, 'a', "abc"sv}, my_receiver{});
    start(op);
}