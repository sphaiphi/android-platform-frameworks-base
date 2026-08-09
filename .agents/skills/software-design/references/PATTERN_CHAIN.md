---
pattern: chain-of-responsibility
category: behavioral
cpp_standard: c++23
complexity: medium
zero_cost: false
tags: [expected, ranges, pipeline, handler-chain, request-processing]
---

## Intent

Pass a request along a chain of handlers, where each handler decides to process it or pass it to the next. In modern C++23, chains are expressed as **ranges pipelines** of handlers returning **std::expected**, avoiding mutable linked-list pointers entirely.

## When to Use

- More than one handler may process a request
- Handler set is dynamic or configurable
- Request processing should be decoupled from handler ordering
- Middleware pipelines (auth → validation → processing → logging)

## When NOT to Use

- Only one handler processes → call directly
- All handlers must process (not exclusive) → use Observer
- Processing order is fixed and known → hardcode the sequence

## Structure

```
Request → Handler₁ → Handler₂ → Handler₃ → Response
              │            │            │
           process?     process?     process?
           yes→return   yes→return   yes→return
           no→next      no→next      no→error
```

## Implementation

```cpp
#include <expected>
#include <functional>
#include <vector>
#include <string_view>
#include <string>
#include <print>
#include <ranges>
#include <concepts>
#include <optional>

// Strong types [P.1, I.4]
enum class HandlerError {
    not_handled,
    unauthorized,
    validation_failed,
    rate_limited,
    processing_failed
};

struct Request {
    std::string_view path;
    std::string_view method;
    std::string_view auth_token;
    std::size_t      body_size{};
};

struct Response {
    int         status_code{200};
    std::string body;
};

// Handler concept [T.10]
template<typename T>
concept Handler = requires(T t, const Request& r) {
    { t.handle(r) } -> std::same_as<std::expected<Response, HandlerError>>;
    { t.name()    } -> std::convertible_to<std::string_view>;
};

// Concrete handlers — each decides to handle or decline
struct AuthHandler {
    std::string_view valid_token{"secret"};   // [C.48]

    [[nodiscard]] auto handle(const Request& req) const
        -> std::expected<Response, HandlerError> {
        if (req.auth_token != valid_token) {
            std::println("[Auth] Rejected: invalid token");
            return std::unexpected(HandlerError::unauthorized);
        }
        std::println("[Auth] Passed");
        return std::unexpected(HandlerError::not_handled);  // Pass to next
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "AuthHandler";
    }
};

struct ValidationHandler {
    static constexpr std::size_t max_body_{1024};   // [C.48]

    [[nodiscard]] auto handle(const Request& req) const
        -> std::expected<Response, HandlerError> {
        if (req.body_size > max_body_) {
            std::println("[Validation] Rejected: body too large ({})", req.body_size);
            return std::unexpected(HandlerError::validation_failed);
        }
        if (req.path.empty()) {
            return std::unexpected(HandlerError::validation_failed);
        }
        std::println("[Validation] Passed");
        return std::unexpected(HandlerError::not_handled);  // Pass to next
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "ValidationHandler";
    }
};

struct RateLimitHandler {
    mutable std::size_t requests_{0};   // [C.48]
    std::size_t         limit_{100};

    [[nodiscard]] auto handle(const Request&) const
        -> std::expected<Response, HandlerError> {
        if (++requests_ > limit_) {
            std::println("[RateLimit] Rejected: limit {} exceeded", limit_);
            return std::unexpected(HandlerError::rate_limited);
        }
        std::println("[RateLimit] Passed ({}/{})", requests_, limit_);
        return std::unexpected(HandlerError::not_handled);  // Pass to next
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "RateLimitHandler";
    }
};

struct ProcessingHandler {
    [[nodiscard]] auto handle(const Request& req) const
        -> std::expected<Response, HandlerError> {
        std::println("[Processing] Handling: {} {}", req.method, req.path);
        return Response{
            .status_code = 200,
            .body = std::format("OK: {} {}", req.method, req.path)
        };
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "ProcessingHandler";
    }
};

// Type-erased handler wrapper [R.20]
class HandlerEntry {
    using Fn = std::function<std::expected<Response, HandlerError>(const Request&)>;
    Fn fn_;
    std::string name_;

public:
    template<Handler H>
    explicit HandlerEntry(H h)
        : fn_([h = std::move(h)](const Request& r) { return h.handle(r); })
        , name_(h.name()) {}

    [[nodiscard]] auto handle(const Request& req) const
        -> std::expected<Response, HandlerError> {
        return fn_(req);
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return self.name_;
    }
};

// Chain: composes handlers as a ranges pipeline
class HandlerChain {
    std::vector<HandlerEntry> handlers_;   // [C.48]

public:
    template<Handler H>
    auto add(H handler) -> HandlerChain& {
        handlers_.emplace_back(std::move(handler));
        return *this;
    }

    // Process: first non-not_handled result wins
    [[nodiscard]] auto process(const Request& req) const
        -> std::expected<Response, HandlerError> {
        for (const auto& handler : handlers_) {
            auto result = handler.handle(req);

            // not_handled → continue to next handler
            if (!result &&
                result.error() == HandlerError::not_handled) {
                continue;
            }

            // success or terminal error → return immediately
            return result;
        }
        // All handlers declined
        return std::unexpected(HandlerError::not_handled);
    }

    // Parallel variant: all handlers must pass (middleware model)
    [[nodiscard]] auto middleware(const Request& req) const
        -> std::expected<Response, HandlerError> {
        for (const auto& handler : handlers_) {
            auto result = handler.handle(req);
            // Any error terminates the chain
            if (!result && result.error() != HandlerError::not_handled) {
                return result;
            }
        }
        return std::unexpected(HandlerError::not_handled);
    }
};
```

## Usage

```cpp
auto main() -> int {
    // Build chain: auth → validate → rate-limit → process
    auto chain = HandlerChain{}
        .add(AuthHandler{})
        .add(ValidationHandler{})
        .add(RateLimitHandler{.limit_ = 100})
        .add(ProcessingHandler{});

    // Valid request — flows through all handlers
    auto req = Request{
        .path       = "/api/data",
        .method     = "GET",
        .auth_token = "secret",
        .body_size  = 256
    };

    auto result = chain.process(req);
    if (result) {
        std::println("Response [{}]: {}", result->status_code, result->body);
    }

    // Invalid auth — short-circuits at AuthHandler
    auto bad_auth = Request{
        .path       = "/api/data",
        .method     = "GET",
        .auth_token = "wrong",
        .body_size  = 128
    };

    auto r2 = chain.process(bad_auth);
    if (!r2) {
        std::println("Failed: {}",
            r2.error() == HandlerError::unauthorized
                ? "unauthorized" : "other");
    }

    // Oversized body — short-circuits at ValidationHandler
    auto big = Request{
        .path       = "/upload",
        .method     = "POST",
        .auth_token = "secret",
        .body_size  = 9999
    };
    chain.process(big);

    // Monadic composition of result
    chain.process(req)
        .transform([](Response r) {
            std::println("Success: {}", r.body);
            return r;
        })
        .or_else([](HandlerError e) {
            std::println("Error code: {}", static_cast<int>(e));
            return std::expected<Response, HandlerError>{
                std::unexpected(e)};
        });
}
```

## Safety Checklist

```
✓ Type Safety    — Handler concept; strong Request/Response/HandlerError
✓ Bounds Safety  — std::vector; range-for; no pointer arithmetic
✓ Lifetime Safety — HandlerEntry by value; std::function captures by value
✓ Init Safety    — All members initialized; requests_ = 0 in-class
✓ Error Safety   — std::expected with not_handled sentinel; [[nodiscard]]
Guidelines: T.10, R.20, C.48, ES.20, E.2, Enum.3, I.4
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Chain vs Middleware Comparison

| Mode          | Semantics                              | Termination                    |
|---------------|----------------------------------------|--------------------------------|
| `process()`   | First handler to claim request wins    | On first success or hard error |
| `middleware()`| All handlers must pass (gate-keeping)  | On first error                 |

## Trade-offs

| Aspect        | Benefit                                  | Cost                           |
|---------------|------------------------------------------|--------------------------------|
| Flexibility   | Add/remove/reorder handlers dynamically  | Order bugs can be subtle       |
| Decoupling    | Handlers know nothing about each other   | Debugging chain flow is harder |
| Error Safety  | std::expected propagates cleanly         | not_handled vs error ambiguity |
| Performance   | std::function: slight overhead per call  | Better than virtual + vtable   |

## Related Patterns

- **Command** — Encapsulates requests; Chain processes them
- **Decorator** — Wraps single object; Chain has multiple independent handlers
- **Observer** — All observers notified; Chain stops at first handler
