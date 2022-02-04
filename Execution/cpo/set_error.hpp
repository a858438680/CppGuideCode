#ifndef EXECUTION_CPO_SET_ERROR_HPP_
#define EXECUTION_CPO_SET_ERROR_HPP_

#include "tag_invoke.hpp"
#include "../concepts/tag_invoke_concepts.hpp"

namespace standard {

namespace execution {

namespace set_error_detail {

struct set_error_t {    
    template <typename R, typename E>
        requires tag_invocable<set_error_t, R&&, E&&>
    auto operator()(R&& r, E&& e) const noexcept
        -> tag_invoke_result_t<set_error_t, R&&, E&&>
    {
        return std::invoke(tag_invoke, set_error_t{}, static_cast<R&&>(r), static_cast<E&&>(e));
    }
};

} // namespace set_error_detail

inline constexpr set_error_detail::set_error_t set_error{};

} // namespace execution

} // namespace standard

#endif // EXECUTION_CPO_SET_ERROR_HPP_