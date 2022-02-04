#ifndef EXECUTION_SENDERS_JUST_SENDER_HPP_
#define EXECUTION_SENDERS_JUST_SENDER_HPP_

#include <tuple>

#include "../cpo/cpo.hpp"
#include "../concepts/concepts.hpp"

namespace standard {

namespace execution {

template <typename... Args>
struct just_sender {
    just_sender(Args&&... args): values_(std::make_tuple(static_cast<Args&&>(args)...)) {}

    [[no_unique_address]] std::tuple<Args...> values_;

    template <receiver R>
    struct operation {
        [[no_unique_address]] std::tuple<Args...> values_;
        [[no_unique_address]] R r_;

        friend void tag_invoke(tag_t<start>, operation& s) noexcept {
            try {
                std::apply([&s](Args&... values_) {
                    std::invoke(set_value, static_cast<R&&>(s.r_), values_...);
                }, s.values_);
            }
            catch (...) {
                std::invoke(set_error, static_cast<R&&>(s.r_), std::current_exception());
            }
        }
    };

    template <receiver R>
    friend auto tag_invoke(tag_t<connect>, const just_sender& s, R&& r) {
        return operation<std::remove_cvref_t<R>>{s.values_, static_cast<R&&>(r)};
    }

    template <receiver R>
    friend auto tag_invoke(tag_t<connect>, just_sender&& s, R&& r) {
        return operation<std::remove_cvref_t<R>>{std::move(s.values_), static_cast<R&&>(r)};
    }
};

} // namespace execution

} // namespace standard

#endif // EXECUTION_SENDERS_JUST_SENDER_HPP_