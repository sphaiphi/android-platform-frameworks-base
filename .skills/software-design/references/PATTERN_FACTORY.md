---
pattern: factory
category: creational
cpp_standard: c++23
complexity: low
zero_cost: true
tags: [concepts, expected, polymorphic-creation, type-safe]
---

## Intent

Define an interface for creating objects without specifying exact classes. In modern C++23, expressed through **concepts** for type-safe creation contracts and **std::expected** for error-aware factory results.

## When to Use

- Object creation logic is complex or context-dependent
- Caller should not depend on concrete types
- Creation can fail in expected ways
- Plugin or registry system needed

## When NOT to Use

- Simple construction → use constructor directly
- Type always known at compile time → use template directly
- Single product type → no need for factory

## Structure

```
FactoryRegistry
    │
    ├── concept Creatable<T>
    ├── make<T>(params) → std::expected<T, CreationError>
    └── register<T>(key)
```

## Implementation

```cpp
#include <expected>
#include <functional>
#include <string_view>
#include <unordered_map>
#include <memory>
#include <concepts>
#include <print>

// Strong error type [I.4, Enum.3]
enum class CreationError {
    unknown_type,
    invalid_params,
    construction_failed
};

// Concept: type must be self-constructing from params [T.10]
template<typename T>
concept Creatable = requires(typename T::Params p) {
    { T::create(p) } -> std::same_as<std::expected<T, CreationError>>;
};

// Strong param types — no primitive obsession [P.1]
struct ShapeParams {
    double width{};
    double height{};
};

// Products — self-contained factories via static create()
struct Rectangle {
    using Params = ShapeParams;
    double width_;
    double height_;

    [[nodiscard]] static auto create(Params p)
        -> std::expected<Rectangle, CreationError> {
        if (p.width <= 0 || p.height <= 0) {
            return std::unexpected(CreationError::invalid_params);
        }
        return Rectangle{p.width, p.height};
    }

    [[nodiscard]] auto area() const -> double { return width_ * height_; }
};

struct Circle {
    using Params = ShapeParams;
    double radius_;

    [[nodiscard]] static auto create(Params p)
        -> std::expected<Circle, CreationError> {
        if (p.width <= 0) {
            return std::unexpected(CreationError::invalid_params);
        }
        return Circle{p.width};  // width as radius
    }

    [[nodiscard]] auto area() const -> double { return 3.14159 * radius_ * radius_; }
};

// Generic factory function [T.10: Creatable constraint]
template<Creatable T>
[[nodiscard]] auto make(typename T::Params params)
    -> std::expected<T, CreationError> {
    return T::create(std::move(params));
}

// Dynamic factory registry — runtime type selection
class ShapeFactory {
public:
    using Creator = std::function<
        std::expected<std::unique_ptr<void*>, CreationError>(ShapeParams)
    >;

    // Polymorphic product base [C.2]
    struct IShape {
        [[nodiscard]] virtual auto area() const -> double = 0;
        virtual ~IShape() = default;
    };

    using ShapeCreator = std::function<
        std::expected<std::unique_ptr<IShape>, CreationError>(ShapeParams)
    >;

private:
    std::unordered_map<std::string, ShapeCreator> registry_;  // [ES.20]

public:
    template<typename T>
    requires std::derived_from<T, IShape> && Creatable<T>
    auto register_type(std::string key) -> void {
        registry_[std::move(key)] = [](ShapeParams p)
            -> std::expected<std::unique_ptr<IShape>, CreationError> {
            return T::create(p).transform([](T obj) {
                return std::unique_ptr<IShape>(
                    std::make_unique<T>(std::move(obj))
                );
            });
        };
    }

    [[nodiscard]] auto create(std::string_view type, ShapeParams params)
        -> std::expected<std::unique_ptr<IShape>, CreationError> {
        auto it = registry_.find(std::string(type));
        if (it == registry_.end()) {
            return std::unexpected(CreationError::unknown_type);
        }
        return it->second(params);
    }
};
```

## Usage

```cpp
auto main() -> int {
    // Compile-time factory: type-safe, zero overhead
    auto rect = make<Rectangle>({.width = 10.0, .height = 5.0});
    if (rect) {
        std::println("Area: {}", rect->area());
    }

    // Error path: invalid params
    auto bad = make<Rectangle>({.width = -1.0, .height = 5.0});
    if (!bad) {
        std::println("Error: invalid params");  // ✓ caught
    }

    // Monadic chain
    auto result = make<Circle>({.width = 7.0})
        .transform([](Circle c) { return c.area(); })
        .value_or(0.0);

    std::println("Circle area: {:.2f}", result);

    // Compile-time error: non-Creatable type
    // make<int>({});  // ✗ concept violation
}
```

## Safety Checklist

```
✓ Type Safety    — Creatable concept enforces interface contract
✓ Bounds Safety  — No arrays; std::unordered_map for registry
✓ Lifetime Safety — unique_ptr for polymorphic products
✓ Init Safety    — Params use designated initializers {}
✓ Error Safety   — std::expected; no sentinel -1 or nullptr
Guidelines: T.10, R.20, I.4, ES.20, Enum.3, E.2
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect        | Benefit                              | Cost                          |
|---------------|--------------------------------------|-------------------------------|
| Type Safety   | Creatable concept enforces protocol  | Product must implement create()|
| Error Safety  | Failures via std::expected           | Callers must handle result     |
| Flexibility   | Runtime registry for dynamic types   | Registry adds indirection      |
| Performance   | Compile-time path is zero cost       | Runtime registry has map lookup|

## Related Patterns

- **Builder** — Constructs objects step-by-step
- **Abstract Factory** — Family of related factories
- **Prototype** — Creates by cloning existing instances
