#pragma once

#if __has_include(<expected>) && __cplusplus >= 202302L
#include <expected>
#else
#include <variant>
#include <stdexcept>
#include <system_error>
#include <type_traits>
#include <string>

namespace std {

template <typename E>
class unexpected {
public:
    unexpected(const E& error) : error_(error) {}
    unexpected(E&& error) : error_(std::move(error)) {}

    const E& error() const { return error_; }
private:
    E error_;
};

// Deduction guides for CTAD
template <typename E>
unexpected(E) -> unexpected<E>;

unexpected(const char*) -> unexpected<std::string>;

template <typename T, typename E>
class expected {
public:
    template <typename U = T, typename = std::enable_if_t<std::is_constructible_v<T, U>>>
    expected(U&& value) : data_(std::forward<U>(value)) {}

    expected(const unexpected<E>& error) : data_(error) {}
    expected(unexpected<E>&& error) : data_(std::move(error)) {}

    bool has_value() const { return std::holds_alternative<T>(data_); }
    const T& value() const {
        if (!has_value()) throw std::runtime_error("expected has no value");
        return std::get<T>(data_);
    }
    const T& operator*() const { return value(); }
    const T* operator->() const { return &value(); }
    const E& error() const {
        return std::get<unexpected<E>>(data_).error();
    }

    template <typename U>
    T value_or(U&& default_value) const {
        return has_value() ? value() : static_cast<T>(std::forward<U>(default_value));
    }

private:
    std::variant<T, unexpected<E>> data_;
};

template <typename E>
class expected<void, E> {
public:
    expected() : data_(std::monostate{}) {}
    expected(const unexpected<E>& error) : data_(error) {}
    expected(unexpected<E>&& error) : data_(std::move(error)) {}

    bool has_value() const { return std::holds_alternative<std::monostate>(data_); }
    void value() const {
        if (!has_value()) throw std::runtime_error("expected has no value");
    }
    void operator*() const { value(); }
    const E& error() const {
        return std::get<unexpected<E>>(data_).error();
    }

private:
    std::variant<std::monostate, unexpected<E>> data_;
};

} // namespace std
#endif
