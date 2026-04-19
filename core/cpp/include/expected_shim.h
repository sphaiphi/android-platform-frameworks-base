#pragma once

#include <variant>
#include <stdexcept>
#include <system_error>
#include <type_traits>
#include <string>

// Force custom implementation to ensure ABI parity between library and client utilities
namespace std {

template <typename E>
class unexpected {
public:
    unexpected() = delete;
    constexpr explicit unexpected(const E& error) : error_(error) {}
    constexpr explicit unexpected(E&& error) : error_(std::move(error)) {}

    constexpr const E& error() const& noexcept { return error_; }
    constexpr E& error() & noexcept { return error_; }
    constexpr E&& error() && noexcept { return std::move(error_); }
    constexpr const E&& error() const&& noexcept { return std::move(error_); }

private:
    E error_;
};

// Deduction guides
template <typename E>
unexpected(E) -> unexpected<E>;

unexpected(const char*) -> unexpected<std::string>;

template <typename T, typename E>
class expected {
public:
    using value_type = T;
    using error_type = E;
    using unexpected_type = unexpected<E>;

    template <typename U = T, typename = std::enable_if_t<std::is_constructible_v<T, U>>>
    constexpr expected(U&& value) : data_(std::in_place_index<0>, std::forward<U>(value)) {}

    constexpr expected(const unexpected<E>& error) : data_(std::in_place_index<1>, error) {}
    constexpr expected(unexpected<E>&& error) : data_(std::in_place_index<1>, std::move(error)) {}

    constexpr bool has_value() const noexcept { return data_.index() == 0; }
    constexpr explicit operator bool() const noexcept { return has_value(); }

    constexpr const T& value() const& {
        if (!has_value()) throw std::runtime_error("expected has no value");
        return std::get<0>(data_);
    }

    constexpr T& value() & {
        if (!has_value()) throw std::runtime_error("expected has no value");
        return std::get<0>(data_);
    }

    constexpr const T& operator*() const& noexcept { return std::get<0>(data_); }
    constexpr T& operator*() & noexcept { return std::get<0>(data_); }
    constexpr const T* operator->() const noexcept { return &std::get<0>(data_); }
    constexpr T* operator->() noexcept { return &std::get<0>(data_); }

    constexpr const E& error() const& {
        if (has_value()) throw std::runtime_error("expected has no error");
        return std::get<1>(data_).error();
    }

    constexpr E& error() & {
        if (has_value()) throw std::runtime_error("expected has no error");
        return std::get<1>(data_).error();
    }

    template <typename U>
    constexpr T value_or(U&& default_value) const& {
        return has_value() ? std::get<0>(data_) : static_cast<T>(std::forward<U>(default_value));
    }

    template <typename U>
    constexpr T value_or(U&& default_value) && {
        return has_value() ? std::move(std::get<0>(data_)) : static_cast<T>(std::forward<U>(default_value));
    }

private:
    std::variant<T, unexpected<E>> data_;
};

template <typename E>
class expected<void, E> {
public:
    using value_type = void;
    using error_type = E;
    using unexpected_type = unexpected<E>;

    constexpr expected() noexcept : data_(std::in_place_index<0>, std::monostate{}) {}
    constexpr expected(const unexpected<E>& error) : data_(std::in_place_index<1>, error) {}
    constexpr expected(unexpected<E>&& error) : data_(std::in_place_index<1>, std::move(error)) {}

    constexpr bool has_value() const noexcept { return data_.index() == 0; }
    constexpr explicit operator bool() const noexcept { return has_value(); }

    constexpr void value() const {
        if (!has_value()) throw std::runtime_error("expected has no value");
    }

    constexpr const E& error() const& {
        if (has_value()) throw std::runtime_error("expected has no error");
        return std::get<1>(data_).error();
    }

    constexpr E& error() & {
        if (has_value()) throw std::runtime_error("expected has no error");
        return std::get<1>(data_).error();
    }

private:
    std::variant<std::monostate, unexpected<E>> data_;
};

} // namespace std
