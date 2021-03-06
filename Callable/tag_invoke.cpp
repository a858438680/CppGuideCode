#include <iostream>
#include <type_traits>

namespace standard
{
namespace detail
{
void tag_invoke();
struct tag_invoke_t
{
    template <typename Tag, typename... Args>
    constexpr auto operator()(Tag tag, Args &&...args) const
        noexcept(noexcept(tag_invoke(static_cast<Tag &&>(tag), static_cast<Args &&>(args)...)))
            -> decltype(tag_invoke(static_cast<Tag &&>(tag), static_cast<Args &&>(args)...))
    {
        return tag_invoke(static_cast<Tag &&>(tag), static_cast<Args &&>(args)...);
    }
};
} // namespace detail

inline constexpr detail::tag_invoke_t tag_invoke{};

template <auto &Tag> using tag_t = std::decay_t<decltype(Tag)>;
} // namespace standard

namespace standard
{

namespace detail
{
struct do_something_t
{
    template <typename T> void operator()(T &t) noexcept
    {
        tag_invoke(do_something_t{}, t);
    }
};

template <typename T> void tag_invoke(do_something_t, T &t) noexcept
{
    std::cout << "standard do something" << std::endl;
}
} // namespace detail

inline detail::do_something_t do_something{};
} // namespace standard

namespace thirdparty
{
struct complicated_structure
{

    friend void tag_invoke(standard::tag_t<standard::do_something>, complicated_structure &t) noexcept
    {
        std::cout << "customized do something" << std::endl;
    }
};

struct simple_structure
{
};
} // namespace thirdparty

int main()
{
    thirdparty::simple_structure s;
    standard::do_something(s);

    thirdparty::complicated_structure c;
    standard::do_something(c);

    using namespace standard;
    do_something(s);
    do_something(c);

    return 0;
}