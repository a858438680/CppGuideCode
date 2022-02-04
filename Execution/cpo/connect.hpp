#ifndef EXECUTION_CPO_CONNECT_HPP_
#define EXECUTION_CPO_CONNECT_HPP_

#include "tag_invoke.hpp"
#include "../concepts/tag_invoke_concepts.hpp"

namespace standard {

namespace execution {

namespace connect_detail {

struct connect_t {    
    template <typename S, typename R>
        requires tag_invocable<connect_t, S&&, R&&>
    auto operator()(S&& s, R&& r) const
        noexcept(tag_nothrow_invocable<connect_t, S&&, R&&>)
        -> tag_invoke_result_t<connect_t, S&&, R&&>
    {
        return std::invoke(tag_invoke, connect_t{}, static_cast<S&&>(s), static_cast<R&&>(r));
    }
};

} // namespace connect_detail

inline constexpr connect_detail::connect_t connect{};

} // namespace execution

} // namespace standard

#endif // EXECUTION_CPO_CONNECT_HPP_