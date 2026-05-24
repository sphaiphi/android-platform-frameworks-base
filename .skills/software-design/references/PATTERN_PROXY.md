---
pattern: proxy
category: structural
cpp_standard: c++23
complexity: low
zero_cost: false
tags: [shared-ptr, nodiscard, lazy-init, access-control, raii]
---

## Intent

Provide a surrogate or placeholder for another object to control access to it. In modern C++23, proxies use **smart pointers** for lifetime safety, **std::expected** for access errors, and **[[nodiscard]]** to enforce checked access.

## Proxy Types

| Type            | Intent                                    | Key Mechanism              |
|-----------------|-------------------------------------------|----------------------------|
| Virtual Proxy   | Lazy initialization on first access       | `std::optional` + `[[nodiscard]]` |
| Protection Proxy| Access control / permissions              | `std::expected` + enum class |
| Remote Proxy    | Abstract remote resource (IPC, network)   | `std::expected` + async     |
| Cache Proxy     | Transparent caching layer                 | `std::unordered_map`        |

## When to Use

- Lazy initialization of expensive objects
- Access control / authorization required
- Remote resource needs local representative
- Reference counting / copy-on-write

## When NOT to Use

- Direct access is acceptable → use the object directly
- Adding behavior → use Decorator instead
- No access control needed → use smart pointer directly

## Structure

```
ISubject (concept or interface)
    │
    ├── RealSubject   — the actual implementation
    └── Proxy         — controls access to RealSubject
            ├── lazy_init() on first request
            └── access_check() before forwarding
```

## Implementation

```cpp
#include <expected>
#include <optional>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <print>
#include <concepts>
#include <chrono>

// Strong types [P.1, Enum.3, I.4]
enum class AccessError {
    unauthorized,
    resource_unavailable,
    quota_exceeded
};

enum class Permission { read, write, admin };

struct UserId    { int value{}; auto operator<=>(const UserId&) const = default; };
struct ResourceId{ int value{}; auto operator<=>(const ResourceId&) const = default; };
struct Data      { std::string content; };

// Subject concept [T.10]
template<typename T>
concept DataSource = requires(T t, ResourceId id) {
    { t.fetch(id) } -> std::same_as<std::expected<Data, AccessError>>;
    { t.name()    } -> std::convertible_to<std::string_view>;
};

// Real subject — expensive to initialize
class DatabaseService {
    bool connected_{false};   // [C.48]
public:
    explicit DatabaseService() {
        // Simulate expensive connection
        std::println("[DB] Connecting...");
        connected_ = true;
    }

    [[nodiscard]] auto fetch(ResourceId id)
        -> std::expected<Data, AccessError> {
        if (!connected_) {
            return std::unexpected(AccessError::resource_unavailable);
        }
        return Data{.content = std::format("Data for resource {}", id.value)};
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "DatabaseService";
    }
};

// Virtual Proxy — lazy init + [[nodiscard]] enforced access [R.1]
class LazyDatabaseProxy {
    mutable std::optional<DatabaseService> service_{};   // [C.48]

    auto ensure_initialized(this auto const& self) -> void {
        if (!self.service_) {
            self.service_.emplace();   // Init on first access
        }
    }

public:
    [[nodiscard]] auto fetch(ResourceId id) const
        -> std::expected<Data, AccessError> {
        ensure_initialized();
        return service_->fetch(id);
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "LazyDatabaseProxy";
    }
};

// Protection Proxy — access control layer
class ProtectedDatabaseProxy {
    std::shared_ptr<DatabaseService> service_;       // [R.20]
    std::unordered_map<int, Permission> acl_;        // user_id → permission

public:
    explicit ProtectedDatabaseProxy(
        std::shared_ptr<DatabaseService> svc)
        : service_(std::move(svc)) {}

    auto grant(UserId user, Permission perm) -> void {
        acl_[user.value] = perm;
    }

    [[nodiscard]] auto fetch(UserId user, ResourceId id)
        -> std::expected<Data, AccessError> {
        auto it = acl_.find(user.value);
        if (it == acl_.end()) {
            return std::unexpected(AccessError::unauthorized);
        }
        std::println("[ACL] User {} authorized ({})",
            user.value, static_cast<int>(it->second));
        return service_->fetch(id);
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "ProtectedDatabaseProxy";
    }
};

// Cache Proxy — transparent caching [R.1]
class CachingDatabaseProxy {
    std::shared_ptr<DatabaseService> service_;       // [R.20]
    std::unordered_map<int, Data> cache_{};          // [C.48]
    std::chrono::steady_clock::time_point last_clear_{
        std::chrono::steady_clock::now()
    };
    static constexpr auto ttl_ = std::chrono::seconds{60};

    auto is_stale(this auto const& self) -> bool {
        return std::chrono::steady_clock::now() - self.last_clear_ > ttl_;
    }

public:
    explicit CachingDatabaseProxy(std::shared_ptr<DatabaseService> svc)
        : service_(std::move(svc)) {}

    [[nodiscard]] auto fetch(ResourceId id)
        -> std::expected<Data, AccessError> {

        if (is_stale()) {
            cache_.clear();
            last_clear_ = std::chrono::steady_clock::now();
        }

        auto it = cache_.find(id.value);
        if (it != cache_.end()) {
            std::println("[CACHE] Hit: resource {}", id.value);
            return it->second;
        }

        auto result = service_->fetch(id);
        if (result) {
            cache_[id.value] = *result;
        }
        return result;
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "CachingDatabaseProxy";
    }
};
```

## Usage

```cpp
auto main() -> int {
    // Virtual Proxy — no DB init until first fetch
    std::println("--- Virtual Proxy ---");
    LazyDatabaseProxy lazy{};
    // DB not initialized yet
    auto r1 = lazy.fetch(ResourceId{1});   // DB initializes here
    auto r2 = lazy.fetch(ResourceId{2});   // Reuses connection
    if (r1) std::println("Got: {}", r1->content);

    // Protection Proxy — access control
    std::println("\n--- Protection Proxy ---");
    auto db  = std::make_shared<DatabaseService>();
    auto acl = ProtectedDatabaseProxy{db};
    acl.grant(UserId{1}, Permission::read);

    auto auth   = acl.fetch(UserId{1}, ResourceId{42});   // ✓ authorized
    auto unauth = acl.fetch(UserId{99}, ResourceId{42});  // ✗ unauthorized
    if (!unauth) std::println("Access denied as expected");

    // Cache Proxy — transparent caching
    std::println("\n--- Cache Proxy ---");
    auto cached = CachingDatabaseProxy{db};
    cached.fetch(ResourceId{5});   // Miss → DB call
    cached.fetch(ResourceId{5});   // Hit → cache

    // [[nodiscard]] enforces result checking
    // lazy.fetch(ResourceId{1});  // ✗ warning: nodiscard ignored
}
```

## Safety Checklist

```
✓ Type Safety    — Strong UserId/ResourceId; AccessError enum class
✓ Bounds Safety  — unordered_map; no C arrays; no indexing
✓ Lifetime Safety — shared_ptr for shared ownership; optional for lazy init
✓ Init Safety    — All members initialized; optional + constexpr TTL
✓ Error Safety   — std::expected; [[nodiscard]] on all fetch methods
Guidelines: R.20, R.21, C.48, ES.20, Enum.3, E.2, I.4
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect        | Benefit                              | Cost                           |
|---------------|--------------------------------------|--------------------------------|
| Lazy Init     | No cost until first access           | Thread-safety needs mutex      |
| Access Control| Centralized authorization            | ACL management overhead        |
| Caching       | Transparent, no client changes       | Stale data risk                |
| Lifetime      | shared_ptr prevents dangling         | Reference counting overhead    |

## Related Patterns

- **Decorator** — Adds behavior; Proxy controls access
- **Adapter** — Changes interface; Proxy keeps same interface
- **Facade** — Simplifies; Proxy controls same interface
