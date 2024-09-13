#pragma once

#include <type_traits>

namespace oeo {

constexpr inline struct zero_then_variadic_t {
} zero_then_variadic;
constexpr inline struct one_then_variadic_t {
} one_then_variadic;

template <class Base, class Other, bool = std::is_empty_v<Base> && !std::is_final_v<Base>>
class tight_pair final : private Base {
    Other sec;

public:
    using first_type  = Base;
    using second_type = Other;

    constexpr explicit tight_pair(
    ) noexcept(std::is_nothrow_default_constructible_v<Base> && std::is_nothrow_default_constructible_v<Other>)
    : Base(), sec() {}

    template <class... Ts2>
    constexpr explicit tight_pair(
        zero_then_variadic_t,
        Ts2&&... val2
    ) noexcept(std::is_nothrow_default_constructible_v<Base> && std::is_nothrow_constructible_v<Other, Ts2...>)
    : Base(), sec(std::forward<Ts2>(val2)...) {}

    template <class T1, class... Ts2>
    constexpr tight_pair(
        one_then_variadic_t,
        T1&& val1,
        Ts2&&... val2
    ) noexcept(std::is_nothrow_constructible_v<Base, T1> && std::is_nothrow_constructible_v<Other, Ts2...>)
    : Base(std::forward<T1>(val1)), sec(std::forward<Ts2>(val2)...) {}

    constexpr first_type& first() noexcept { return *this; }

    constexpr first_type const& first() const noexcept { return *this; }

    constexpr second_type& second() noexcept { return sec; }

    constexpr second_type const& second() const noexcept { return sec; }
};

template <class Base, class Other>
class tight_pair<Base, Other, false> final {
    Base  fst;
    Other sec;

public:
    using first_type  = Base;
    using second_type = Other;

    constexpr explicit tight_pair(
    ) noexcept(std::is_nothrow_default_constructible_v<Base> && std::is_nothrow_default_constructible_v<Other>)
    : fst(), sec() {}

    template <class... Ts2>
    constexpr explicit tight_pair(
        zero_then_variadic_t,
        Ts2&&... val2
    ) noexcept(std::is_nothrow_default_constructible_v<Base> && std::is_nothrow_constructible_v<Other, Ts2...>)
    : fst(), sec(std::forward<Ts2>(val2)...) {}

    template <class T1, class... Ts2>
    constexpr tight_pair(
        one_then_variadic_t,
        T1&& val1,
        Ts2&&... val2
    ) noexcept(std::is_nothrow_constructible_v<Base, T1> && std::is_nothrow_constructible_v<Other, Ts2...>)
    : fst(std::forward<T1>(val1)), sec(std::forward<Ts2>(val2)...) {}

    constexpr first_type& first() noexcept { return fst; }

    constexpr first_type const& first() const noexcept { return fst; }

    constexpr second_type& second() noexcept { return sec; }

    constexpr second_type const& second() const noexcept { return sec; }
};
} // namespace oeo
