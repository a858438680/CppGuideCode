#ifndef EXECUTION_CONCEPTS_RECEIVER_CONCEPTS_HPP_
#define EXECUTION_CONCEPTS_RECEIVER_CONCEPTS_HPP_

#include <concepts>
#include <exception>
#include <type_traits>
#include <utility>

namespace standard {

namespace execution {

template <typename R, typename E = std::exception_ptr>
concept receiver =
    std::move_constructible<std::remove_cvref_t<R>> &&
    std::constructible_from<std::remove_cvref_t<R>, R> &&
    requires (std::remove_cvref_t<R>&& r, E&& e) {
        { set_done(std::move(r)) } noexcept;
        { set_error(std::move(r), (E&&) e) } noexcept;
    };

template <typename R, typename... Args>
concept receiver_of =
    receiver<R> &&
    requires (std::remove_cvref_t<R>&& r, Args&&... args) {
        set_value(std::move(r), static_cast<Args&&>(args)...);
    };

} // namespace execution

} // namespace standard

#endif // EXECUTION_CONCEPTS_RECEIVER_CONCEPTS_HPP_