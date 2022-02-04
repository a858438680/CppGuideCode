#ifndef EXECUTION_CPO_TAG_INVOKE_HPP_
#define EXECUTION_CPO_TAG_INVOKE_HPP_

#include <functional>

namespace standard {

namespace tag_invoke_detail {

    void tag_invoke();

    struct tag_invoke_t {
        template <typename Tag, typename... Args>
        constexpr auto operator()(Tag&& tag, Args&&... args) const
            noexcept(noexcept(tag_invoke(static_cast<Tag&&>(tag), static_cast<Args&&>(args)...)))
            -> decltype(tag_invoke(static_cast<Tag&&>(tag), static_cast<Args&&>(args)...))
        {
            return tag_invoke(static_cast<Tag&&>(tag), static_cast<Args&&>(args)...);
        }
    };

} // namespace tag_invoke_detail

inline constexpr tag_invoke_detail::tag_invoke_t tag_invoke{};

template <auto& tag>
using tag_t = std::decay_t<decltype(tag)>;

template <typename Tag, typename... Args>
using tag_invoke_result_t = std::invoke_result_t<decltype(tag_invoke), Tag, Args...>;

} // namespace standard

#endif // EXECUTION_CPO_TAG_INVOKE_HPP_