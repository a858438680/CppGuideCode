#ifndef EXECUTION_CPO_SET_DONE_HPP_
#define EXECUTION_CPO_SET_DONE_HPP_

#include "tag_invoke.hpp"
#include "../concepts/tag_invoke_concepts.hpp"

namespace standard {

namespace execution {

namespace set_done_detail {

struct set_done_t {    
    template <typename R>
        requires tag_invocable<set_done_t, R&&>
    auto operator()(R&& r) const noexcept
        -> tag_invoke_result_t<set_done_t, R&&>
    {
        return std::invoke(tag_invoke, set_done_t{}, static_cast<R&&>(r));
    }
};

} // namespace set_done_detail

inline constexpr set_done_detail::set_done_t set_done{};

} // namespace execution

} // namespace standard

#endif // EXECUTION_CPO_SET_DONE_HPP_