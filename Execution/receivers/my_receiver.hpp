#ifndef EXECUTION_RECEIVERS_MY_RECEIVER_HPP_
#define EXECUTION_RECEIVERS_MY_RECEIVER_HPP_

#include <iostream>
#include <thread>
#include <string_view>

#include "../cpo/cpo.hpp"
#include "../concepts/concepts.hpp"

using namespace std::literals::string_view_literals;

namespace standard {

namespace execution {

struct my_receiver {
    friend void tag_invoke(tag_t<set_done>, my_receiver&&) {
        std::cout << "my_receiver set done in thread " << std::this_thread::get_id() << std::endl;
    }

    template <typename E>
    friend void tag_invoke(tag_t<set_error>, my_receiver&&, E&&) {
        std::cout << "my_receiver set error in thread " << std::this_thread::get_id() << std::endl;
    }

    friend void tag_invoke(tag_t<set_value>, my_receiver&&) {
        std::cout << "my_receiver set value in thread " << std::this_thread::get_id() << std::endl;
    }

    template <typename T, typename... Args>
    friend void tag_invoke(tag_t<set_value>, my_receiver&&, T&& t, Args&&... args) {
        std::cout << "my_receiver set value in thread " << std::this_thread::get_id() << std::endl;
        std::cout << t;
        ((std::cout << ", "sv << args), ...) << std::endl;
    }
};

} // namespace execution

} // namespace standard

#endif // EXECUTION_RECEIVERS_MY_RECEIVER_HPP_