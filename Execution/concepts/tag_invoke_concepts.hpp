#ifndef EXECUTION_CONCEPTS_TAG_INVOKE_CONCEPTS_HPP_
#define EXECUTION_CONCEPTS_TAG_INVOKE_CONCEPTS_HPP_

#include "../cpo/tag_invoke.hpp"

namespace standard {

template <typename Tag, typename... Args>
concept tag_invocable =
    std::is_invocable_v<decltype(tag_invoke), Tag, Args...>;

template <typename Tag, typename... Args>
concept tag_nothrow_invocable =
    std::is_nothrow_invocable_v<decltype(tag_invoke), Tag, Args...>;

} // namespace standard

#endif // EXECUTION_CONCEPTS_TAG_INVOKE_CONCEPTS_HPP_