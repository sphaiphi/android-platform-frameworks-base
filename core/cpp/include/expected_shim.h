#pragma once

#if __has_include(<expected>) && __cplusplus >= 202302L
#include <expected>
#else
#include <variant>
#include <stdexcept>
#include <system_error>

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

template <typename T, typename E>
class expected {
public:
    expected(const T& value) : data_(value) {}
    expected(T&& value) : data_(std::move(value)) {}
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

private:
    std::variant<T, unexpected<E>> data_;
};

} // namespace std
#endif
