#ifndef EXECUTION_CPO_START_HPP_
#define EXECUTION_CPO_START_HPP_

#include "tag_invoke.hpp"
#include "../concepts/tag_invoke_concepts.hpp"

namespace standard {

namespace execution {

namespace start_detail {

struct start_t {    
    template <typename O>
        requires tag_invocable<start_t, O&&>
    auto operator()(O&& o) const noexcept
        -> tag_invoke_result_t<start_t, O&&>
    {
        return std::invoke(tag_invoke, start_t{}, static_cast<O&&>(o));
    }
};

} // namespace start_detail

inline constexpr start_detail::start_t start{};

} // namespace execution

} // namespace standard

#endif // EXECUTION_CPO_START_HPP_