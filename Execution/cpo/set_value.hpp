#ifndef EXECUTION_CPO_SET_VALUE_HPP_
#define EXECUTION_CPO_SET_VALUE_HPP_

#include "tag_invoke.hpp"
#include "../concepts/tag_invoke_concepts.hpp"

namespace standard {

namespace execution {

namespace set_value_detail {

struct set_value_t {    
    template <typename R, typename... Args>
        requires tag_invocable<set_value_t, R&&, Args&&...>
    auto operator()(R&& r, Args&&... args) const
        noexcept(tag_nothrow_invocable<set_value_t, R&&, Args&&...>)
        -> tag_invoke_result_t<set_value_t, R&&, Args&&...>
    {
        return std::invoke(tag_invoke, set_value_t{}, static_cast<R&&>(r), static_cast<Args&&>(args)...);
    }
};

} // namespace set_value_detail

inline constexpr set_value_detail::set_value_t set_value{};

} // namespace execution

} // namespace standard

#endif // EXECUTION_CPO_SET_VALUE_HPP_