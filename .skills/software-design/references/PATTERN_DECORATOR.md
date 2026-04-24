---
pattern: decorator
category: structural
cpp_standard: c++23
complexity: medium
zero_cost: true
tags: [deducing-this, mixin, crtp-elimination, transparent-wrapper, composition]
---

## Intent

Attach additional responsibilities to an object dynamically. In modern C++23, **deducing this** enables transparent decorator wrappers with zero overhead, while **mixin inheritance** composes behaviors at compile time.

## When to Use

- Add behavior to individual objects without affecting others
- Subclassing would create a combinatorial explosion
- Behaviors should be composable and removable
- Cross-cutting concerns (logging, caching, timing)

## When NOT to Use

- All objects need the same behavior → put it in base class
- Behavior changes based on state → use State pattern
- Decoration at runtime not needed → use compile-time mixin only

## Structure

```
Compile-Time (preferred — zero cost):
    LoggingDecorator<TimingDecorator<Core>>
        → zero overhead, resolved at compile time

Runtime (when needed):
    ConcreteComponent
        ↑ wraps
    Decorator(unique_ptr<IComponent>)
        ↑ wraps
    LoggingDecorator
```

## Implementation

```cpp
#include <concepts>
#include <memory>
#include <string>
#include <string_view>
#include <print>
#include <expected>
#include <chrono>
#include <functional>

// Strong types [P.1, I.4]
enum class ServiceError {
    unavailable,
    timeout,
    invalid_request
};

struct Request  { std::string_view data; };
struct Response { std::string result; };

// Concept: type is a service [T.10]
template<typename T>
concept Service = requires(T t, Request r) {
    { t.handle(r) } -> std::same_as<std::expected<Response, ServiceError>>;
    { t.name()    } -> std::convertible_to<std::string_view>;
};

// Core service — no decorations
class DataService {
public:
    [[nodiscard]] auto handle(Request req)
        -> std::expected<Response, ServiceError> {
        if (req.data.empty()) {
            return std::unexpected(ServiceError::invalid_request);
        }
        return Response{.result = std::string("Processed: ") + std::string(req.data)};
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "DataService";
    }
};

// Compile-time decorator: Logging mixin [deducing this]
template<Service Base>
class LoggingDecorator : public Base {
public:
    using Base::Base;

    [[nodiscard]] auto handle(this auto&& self, Request req)
        -> std::expected<Response, ServiceError> {
        std::println("[LOG][{}] Request: {}", self.name(), req.data);

        auto result = Base::handle(std::forward<decltype(self)>(self), req);

        if (result) {
            std::println("[LOG][{}] Response: {}", self.name(), result->result);
        } else {
            std::println("[LOG][{}] Error: {}",
                self.name(), static_cast<int>(result.error()));
        }
        return result;
    }
};

// Compile-time decorator: Timing mixin
template<Service Base>
class TimingDecorator : public Base {
public:
    using Base::Base;

    [[nodiscard]] auto handle(this auto&& self, Request req)
        -> std::expected<Response, ServiceError> {
        const auto start = std::chrono::steady_clock::now();

        auto result = Base::handle(std::forward<decltype(self)>(self), req);

        const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now() - start
        );
        std::println("[TIMING][{}] {}µs", self.name(), elapsed.count());
        return result;
    }
};

// Compile-time decorator: Caching mixin
template<Service Base>
class CachingDecorator : public Base {
    std::unordered_map<std::string, Response> cache_{};   // [C.48]

public:
    using Base::Base;

    [[nodiscard]] auto handle(this auto&& self, Request req)
        -> std::expected<Response, ServiceError> {
        auto key = std::string(req.data);
        if (auto it = self.cache_.find(key); it != self.cache_.end()) {
            std::println("[CACHE][{}] Hit: {}", self.name(), key);
            return it->second;
        }
        auto result = Base::handle(std::forward<decltype(self)>(self), req);
        if (result) {
            self.cache_[key] = *result;
        }
        return result;
    }
};

// Runtime decorator base [C.2] — for dynamic composition
class IService {
public:
    [[nodiscard]] virtual auto handle(Request req)
        -> std::expected<Response, ServiceError> = 0;
    [[nodiscard]] virtual auto name() const -> std::string_view = 0;
    virtual ~IService() = default;
    IService() = default;
    IService(const IService&) = delete;
    IService(IService&&) = delete;
    auto operator=(const IService&) -> IService& = delete;
    auto operator=(IService&&) -> IService& = delete;
};

// Runtime wrapper for compile-time service [Bridge]
template<Service S>
class ServiceAdapter final : public IService {
    S service_{};
public:
    [[nodiscard]] auto handle(Request req)
        -> std::expected<Response, ServiceError> override {
        return service_.handle(req);
    }
    [[nodiscard]] auto name() const -> std::string_view override {
        return service_.name();
    }
};

// Runtime logging decorator [R.20]
class RuntimeLoggingDecorator final : public IService {
    std::unique_ptr<IService> inner_;   // [R.20]
public:
    explicit RuntimeLoggingDecorator(std::unique_ptr<IService> inner)
        : inner_(std::move(inner)) {}

    [[nodiscard]] auto handle(Request req)
        -> std::expected<Response, ServiceError> override {
        std::println("[RT-LOG][{}] >> {}", inner_->name(), req.data);
        auto result = inner_->handle(req);
        std::println("[RT-LOG][{}] << {}", inner_->name(),
            result ? result->result : "ERROR");
        return result;
    }

    [[nodiscard]] auto name() const -> std::string_view override {
        return inner_->name();
    }
};
```

## Usage

```cpp
auto main() -> int {
    // Compile-time composition — zero overhead
    // Order: Timing → Logging → Core (inner-to-outer)
    using DecoratedService = TimingDecorator<LoggingDecorator<DataService>>;
    auto svc = DecoratedService{};
    auto r1 = svc.handle(Request{.data = "hello"});

    // Compile-time with caching
    using CachedService = CachingDecorator<LoggingDecorator<DataService>>;
    auto cached = CachedService{};
    cached.handle(Request{.data = "world"});  // Miss → logs
    cached.handle(Request{.data = "world"});  // Hit → no log

    // Runtime composition — dynamic wrapping
    auto runtime = std::make_unique<RuntimeLoggingDecorator>(
        std::make_unique<ServiceAdapter<DataService>>()
    );
    runtime->handle(Request{.data = "dynamic"});

    // Error path
    auto err = svc.handle(Request{.data = ""});
    if (!err) {
        std::println("Error caught by decorator chain");
    }

    // Compile-time error: non-Service type rejected
    // LoggingDecorator<int>{};  // ✗ Service concept violation
}
```

## Safety Checklist

```
✓ Type Safety    — Service concept constrains all decorators
✓ Bounds Safety  — unordered_map; no arrays; range-for
✓ Lifetime Safety — unique_ptr for runtime; value types for compile-time
✓ Init Safety    — All members initialized; cache_ in-class
✓ Error Safety   — std::expected propagated through entire chain
Guidelines: T.10, R.20, C.48, ES.20, E.2, C.46
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect          | Benefit                                    | Cost                              |
|-----------------|--------------------------------------------|-----------------------------------|
| Composition     | Behaviors compose freely                   | Compile-time: recompile per combo |
| Performance     | Compile-time: zero overhead                | Runtime: indirection per layer    |
| Flexibility     | Runtime: swap decorators dynamically       | Runtime: vtable overhead          |
| Safety          | Concept prevents invalid decoration        | More template boilerplate         |

## Related Patterns

- **Proxy** — Controls access; Decorator adds behavior
- **Composite** — Decorates a tree structure
- **Strategy** — Changes algorithm; Decorator adds behavior to same interface
