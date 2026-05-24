---
pattern: strategy
category: behavioral
cpp_standard: c++23
complexity: low
zero_cost: true
tags: [concepts, static-polymorphism, compile-time, policy-based]
---

## Intent

Define a family of algorithms, encapsulate each one, and make them interchangeable. In modern C++23, prefer **compile-time strategy** via concepts and templates (zero cost) over runtime strategy via virtual functions.

## When to Use

- Algorithm should vary independently from clients
- Multiple variants of an algorithm exist
- **Compile-time**: algorithm known at instantiation → concepts + templates
- **Runtime**: algorithm selected by user input → std::function / virtual

## When NOT to Use

- Only one algorithm exists → use directly
- Algorithm never changes → inline the logic
- Strategy adds no behavioral variation → overcomplicated

## Structure

```
Compile-Time (preferred):
    Context<Strategy>
        └── Strategy (concept-constrained template param)

Runtime (when needed):
    Context
        └── std::function<Result(Args)>   — lightweight
        └── std::unique_ptr<IStrategy>    — stateful
```

## Implementation

```cpp
#include <concepts>
#include <functional>
#include <span>
#include <vector>
#include <algorithm>
#include <print>
#include <expected>

// Strong types [P.1, I.4]
struct SortMetrics {
    std::size_t comparisons{};
    std::size_t swaps{};
};

// Strategy concept — defines required interface [T.10]
template<typename T>
concept SortStrategy = requires(T t, std::span<int> data) {
    { t.sort(data) } -> std::same_as<SortMetrics>;
    { t.name() } -> std::convertible_to<std::string_view>;
};

// Concrete strategies
struct QuickSort {
    auto name() const -> std::string_view { return "QuickSort"; }

    auto sort(std::span<int> data) -> SortMetrics {
        SortMetrics m{};
        std::ranges::sort(data, [&](int a, int b) {
            ++m.comparisons;
            return a < b;
        });
        return m;
    }
};

struct StableSort {
    auto name() const -> std::string_view { return "StableSort"; }

    auto sort(std::span<int> data) -> SortMetrics {
        SortMetrics m{};
        std::ranges::stable_sort(data, [&](int a, int b) {
            ++m.comparisons;
            return a < b;
        });
        return m;
    }
};

// Compile-time strategy context — zero overhead [Per.10]
template<SortStrategy Strategy>
class Sorter {
    Strategy strategy_{};   // [C.48: in-class init]

public:
    explicit Sorter() = default;
    explicit Sorter(Strategy s) : strategy_(std::move(s)) {}

    [[nodiscard]] auto sort(std::span<int> data) -> SortMetrics {
        return strategy_.sort(data);
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return self.strategy_.name();
    }
};

// Runtime strategy context — for user-driven selection
class RuntimeSorter {
public:
    using StrategyFn = std::function<SortMetrics(std::span<int>)>;

private:
    StrategyFn strategy_;   // [ES.20]
    std::string name_;

public:
    explicit RuntimeSorter(StrategyFn fn, std::string name)
        : strategy_(std::move(fn))
        , name_(std::move(name)) {}

    // Hot-swap strategy at runtime
    auto set_strategy(StrategyFn fn, std::string name) -> void {
        strategy_ = std::move(fn);
        name_ = std::move(name);
    }

    [[nodiscard]] auto sort(std::span<int> data) -> SortMetrics {
        return strategy_(data);
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return self.name_;
    }
};

// Strategy registry — select by name [I.4]
enum class SortAlgorithm { quick, stable, partial };

[[nodiscard]] auto make_sorter(SortAlgorithm algo) -> RuntimeSorter {
    switch (algo) {
        case SortAlgorithm::quick:
            return RuntimeSorter{
                [s = QuickSort{}](std::span<int> d) mutable { return s.sort(d); },
                "QuickSort"
            };
        case SortAlgorithm::stable:
            return RuntimeSorter{
                [s = StableSort{}](std::span<int> d) mutable { return s.sort(d); },
                "StableSort"
            };
        case SortAlgorithm::partial:
            return RuntimeSorter{
                [](std::span<int> d) -> SortMetrics {
                    std::ranges::nth_element(d, d.begin() + d.size() / 2);
                    return {};
                },
                "PartialSort"
            };
    }
    std::unreachable();
}
```

## Usage

```cpp
auto main() -> int {
    auto data = std::vector{5, 3, 8, 1, 9, 2, 7};

    // Compile-time strategy — zero cost, resolved at instantiation
    auto sorter = Sorter<QuickSort>{};
    auto metrics = sorter.sort(data);
    std::println("[{}] comparisons: {}", sorter.name(), metrics.comparisons);

    // Runtime strategy — user-driven selection
    auto runtime = make_sorter(SortAlgorithm::stable);
    auto data2 = std::vector{5, 3, 8, 1, 9};
    auto m2 = runtime.sort(data2);
    std::println("[{}] comparisons: {}", runtime.name(), m2.comparisons);

    // Hot-swap at runtime
    runtime.set_strategy(
        [s = QuickSort{}](std::span<int> d) mutable { return s.sort(d); },
        "QuickSort"
    );

    // Compile-time error: non-strategy type rejected
    // Sorter<int>{};  // ✗ SortStrategy concept violation
}
```

## Safety Checklist

```
✓ Type Safety    — SortStrategy concept enforces interface contract
✓ Bounds Safety  — std::span for array params; ranges algorithms
✓ Lifetime Safety — std::function captures by value; no dangles
✓ Init Safety    — All members initialized; strategy_ in-class
✓ Error Safety   — SortMetrics returned; no sentinel values
Guidelines: T.10, I.13, F.16, C.48, ES.20, Per.10
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Compile-Time vs Runtime Comparison

| Aspect         | Compile-Time (`template<SortStrategy>`) | Runtime (`std::function`)      |
|----------------|------------------------------------------|--------------------------------|
| Performance    | Zero overhead (inlined by compiler)      | Indirect call overhead         |
| Flexibility    | Fixed at instantiation                   | Swappable at runtime           |
| Error detection| Concept violation at compile             | Fails at runtime               |
| Code size      | One binary per strategy                  | Single binary, multiple paths  |
| Use case       | Algorithm known at compile-time          | User/config-driven selection   |

## Trade-offs

| Aspect        | Benefit                              | Cost                            |
|---------------|--------------------------------------|---------------------------------|
| Isolation     | Algorithm independent of context     | Extra types per strategy        |
| Testability   | Strategies testable in isolation     | Runtime: type-erasure overhead  |
| Extensibility | New strategies without modifying ctx | Compile-time: recompile needed  |

## Related Patterns

- **Template Method** — Defines skeleton with steps overridden by subclasses
- **Command** — Encapsulates a request as an object
- **State** — Strategy changes based on object state
