---
pattern: visitor
category: behavioral
cpp_standard: c++23
complexity: medium
zero_cost: true
tags: [variant, visit, overload, exhaustive-dispatch, double-dispatch]
---

## Intent

Represent an operation to be performed on elements of an object structure, allowing new operations without modifying the elements. In modern C++23, **std::visit** with **overload sets** replaces traditional double-dispatch with zero overhead and compiler-enforced exhaustiveness.

## When to Use

- Many distinct operations on a heterogeneous collection
- Operations vary but element types are stable
- Adding operations without modifying element types
- Exhaustive handling of all variants required

## When NOT to Use

- Element types change frequently → variant extension is costly
- Single operation on homogeneous types → use algorithm
- Elements define their own operations cleanly → use virtual

## Structure

```
Element = std::variant<CircleEl, RectEl, TriangleEl>

Visitor = overload{ lambda_A, lambda_B, lambda_C }

std::visit(Visitor, Element)
    → dispatches to correct lambda — exhaustive, zero overhead
```

## Implementation

```cpp
#include <variant>
#include <vector>
#include <cmath>
#include <string>
#include <print>
#include <ranges>
#include <expected>
#include <numeric>

// Overload helper — compose lambdas into visitor [C++17/20]
template<typename... Ts>
struct overload : Ts... { using Ts::operator()...; };

// Strong element types [P.1, I.4]
struct Circle {
    double radius{};
};

struct Rectangle {
    double width{};
    double height{};
};

struct Triangle {
    double base{};
    double height{};
};

// Element variant — exhaustive, closed set
using Shape = std::variant<Circle, Rectangle, Triangle>;

// Visitor 1: Area calculator (stateless)
struct AreaVisitor {
    auto operator()(const Circle& c) const -> double {
        return std::numbers::pi * c.radius * c.radius;
    }
    auto operator()(const Rectangle& r) const -> double {
        return r.width * r.height;
    }
    auto operator()(const Triangle& t) const -> double {
        return 0.5 * t.base * t.height;
    }
};

// Visitor 2: Perimeter calculator
struct PerimeterVisitor {
    auto operator()(const Circle& c) const -> double {
        return 2.0 * std::numbers::pi * c.radius;
    }
    auto operator()(const Rectangle& r) const -> double {
        return 2.0 * (r.width + r.height);
    }
    auto operator()(const Triangle& t) const -> double {
        // Isosceles approximation
        const auto side = std::sqrt(
            (t.base / 2.0) * (t.base / 2.0) + t.height * t.height
        );
        return t.base + 2.0 * side;
    }
};

// Visitor 3: Serializer (stateful via lambda)
auto make_serializer() {
    return overload{
        [](const Circle& c) -> std::string {
            return std::format("Circle(r={:.2f})", c.radius);
        },
        [](const Rectangle& r) -> std::string {
            return std::format("Rect({}x{})", r.width, r.height);
        },
        [](const Triangle& t) -> std::string {
            return std::format("Tri(b={},h={})", t.base, t.height);
        }
    };
}

// Visitor 4: Scale transformer — returns new Shape
struct ScaleVisitor {
    double factor{1.0};

    auto operator()(const Circle& c) const -> Shape {
        return Circle{.radius = c.radius * factor};
    }
    auto operator()(const Rectangle& r) const -> Shape {
        return Rectangle{.width = r.width * factor, .height = r.height * factor};
    }
    auto operator()(const Triangle& t) const -> Shape {
        return Triangle{.base = t.base * factor, .height = t.height * factor};
    }
};

// Shape collection operations using ranges
class ShapeCollection {
    std::vector<Shape> shapes_{};   // [C.48]

public:
    auto add(Shape s) -> void {
        shapes_.push_back(std::move(s));
    }

    // Total area via ranges + visit
    [[nodiscard]] auto total_area(this auto const& self) -> double {
        return std::ranges::fold_left(
            self.shapes_ | std::views::transform([](const Shape& s) {
                return std::visit(AreaVisitor{}, s);
            }),
            0.0, std::plus{}
        );
    }

    // Serialize all shapes
    [[nodiscard]] auto serialize(this auto const& self)
        -> std::vector<std::string> {
        auto serializer = make_serializer();
        std::vector<std::string> result;
        result.reserve(self.shapes_.size());
        for (const auto& s : self.shapes_) {
            result.push_back(std::visit(serializer, s));
        }
        return result;
    }

    // Scale all and return new collection
    [[nodiscard]] auto scaled(this auto const& self, double factor)
        -> ShapeCollection {
        ShapeCollection out{};
        for (const auto& s : self.shapes_) {
            out.add(std::visit(ScaleVisitor{.factor = factor}, s));
        }
        return out;
    }

    [[nodiscard]] auto size(this auto const& self) -> std::size_t {
        return self.shapes_.size();
    }
};
```

## Usage

```cpp
auto main() -> int {
    ShapeCollection col{};
    col.add(Circle{.radius = 5.0});
    col.add(Rectangle{.width = 4.0, .height = 6.0});
    col.add(Triangle{.base = 3.0, .height = 8.0});

    // Visitor 1: Area
    std::println("Total area: {:.2f}", col.total_area());

    // Visitor 2: Per-shape perimeter
    for (const auto& name : col.serialize()) {
        std::println("Shape: {}", name);
    }

    // Visitor 3: Transform
    auto big = col.scaled(2.0);
    std::println("Scaled area: {:.2f}", big.total_area());

    // Direct visit with overload
    Shape s = Circle{.radius = 3.0};
    auto area = std::visit(AreaVisitor{}, s);
    std::println("Circle area: {:.2f}", area);

    // Compile-time exhaustiveness: adding a new Shape member
    // without updating visitors → compile error (missing overload)
    // ✗ std::visit(AreaVisitor{}, std::variant<Circle, Rectangle, Triangle, Polygon>{...})
}
```

## Safety Checklist

```
✓ Type Safety    — variant ensures only legal Shape types; overload set exhaustive
✓ Bounds Safety  — std::vector; ranges::fold_left; no indexing
✓ Lifetime Safety — Shapes are value types; no ownership issues
✓ Init Safety    — All members initialized; shapes_ in-class
✓ Error Safety   — No exceptions; visitors return values
Guidelines: P.4, ES.20, C.48, T.10, ES.71
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect          | Benefit                                    | Cost                              |
|-----------------|--------------------------------------------|-----------------------------------|
| Exhaustiveness  | Compiler enforces all variants handled     | Add new type = update all visitors|
| Performance     | Zero overhead (no vtable)                  | Variant size = max element        |
| Extensibility   | New operations = new visitor struct        | Element set must be closed        |
| Readability     | Operations colocated in visitor struct     | Verbose for many element types    |

## Traditional vs Modern Comparison

| Approach           | Mechanism            | Exhaustiveness | Overhead   |
|--------------------|----------------------|----------------|------------|
| Classic Visitor    | Virtual + accept()   | No             | vtable     |
| Modern std::visit  | variant + overload   | **Yes**        | **Zero**   |

## Related Patterns

- **Strategy** — Per-object algorithm variation vs per-type operation
- **Composite** — Visitor commonly traverses composite structures
- **Iterator** — Visit elements of a structure sequentially
