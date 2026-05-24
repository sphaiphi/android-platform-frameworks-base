---
pattern: composite
category: structural
cpp_standard: c++23
complexity: medium
zero_cost: true
tags: [variant, recursive-variant, visit, tree-structure, uniform-interface]
---

## Intent

Compose objects into tree structures to represent part-whole hierarchies, allowing clients to treat individual objects and compositions uniformly. In modern C++23, **std::variant** with **recursive types** replaces virtual inheritance with type-safe, zero-overhead tree nodes.

## When to Use

- Part-whole hierarchy needed (files/folders, UI widgets, AST)
- Clients should treat leaf and composite uniformly
- Recursive structure with operations applied at every level
- Tree traversal with different operation types

## When NOT to Use

- No hierarchy needed → use flat containers
- Only one level deep → no need for composite
- Nodes are heterogeneous with unrelated interfaces → use variant directly

## Structure

```
Node = std::variant<Leaf, Composite>

Composite { name, children: vector<Node> }
Leaf      { name, value }

Operations via std::visit:
    → sum(), count(), find(), serialize(), depth()
```

## Implementation

```cpp
#include <variant>
#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <print>
#include <ranges>
#include <expected>
#include <numeric>
#include <concepts>

// Strong types [P.1, I.4]
struct NodeName  { std::string value; };
struct NodeValue { double value{}; };

// Strong error type [Enum.3]
enum class TreeError {
    node_not_found,
    empty_composite,
    cycle_detected
};

// Forward declare Composite for recursive variant
struct Composite;

// Leaf node — terminal value
struct Leaf {
    NodeName  name;
    NodeValue value;

    [[nodiscard]] auto sum()   const -> double       { return value.value; }
    [[nodiscard]] auto count() const -> std::size_t  { return 1; }
    [[nodiscard]] auto depth() const -> std::size_t  { return 0; }
    [[nodiscard]] auto display(std::size_t indent = 0) const -> void {
        std::println("{:>{}}{}: {}", "", indent * 2, name.value, value.value);
    }
};

// Node variant — recursive via unique_ptr [R.20]
using Node = std::variant<Leaf, std::unique_ptr<Composite>>;

// Composite node — contains children
struct Composite {
    NodeName          name;
    std::vector<Node> children;   // [C.48]

    // Forward-declared operations — defined after Node
    [[nodiscard]] auto sum()   const -> double;
    [[nodiscard]] auto count() const -> std::size_t;
    [[nodiscard]] auto depth() const -> std::size_t;
    [[nodiscard]] auto display(std::size_t indent = 0) const -> void;

    auto add(Leaf leaf) -> void {
        children.push_back(std::move(leaf));
    }

    auto add(std::unique_ptr<Composite> child) -> void {
        children.push_back(std::move(child));
    }

    [[nodiscard]] auto find(std::string_view target_name) const
        -> std::expected<const Leaf*, TreeError>;
};

// Visitor helpers for Node operations
struct SumVisitor {
    auto operator()(const Leaf& l) const -> double { return l.sum(); }
    auto operator()(const std::unique_ptr<Composite>& c) const -> double {
        return c->sum();
    }
};

struct CountVisitor {
    auto operator()(const Leaf& l) const -> std::size_t { return l.count(); }
    auto operator()(const std::unique_ptr<Composite>& c) const -> std::size_t {
        return c->count();
    }
};

struct DepthVisitor {
    auto operator()(const Leaf& l) const -> std::size_t { return l.depth(); }
    auto operator()(const std::unique_ptr<Composite>& c) const -> std::size_t {
        return c->depth();
    }
};

struct DisplayVisitor {
    std::size_t indent{};
    auto operator()(const Leaf& l) const -> void { l.display(indent); }
    auto operator()(const std::unique_ptr<Composite>& c) const -> void {
        c->display(indent);
    }
};

// Deferred definitions [require complete Node]
inline auto Composite::sum() const -> double {
    return std::ranges::fold_left(
        children | std::views::transform([](const Node& n) {
            return std::visit(SumVisitor{}, n);
        }), 0.0, std::plus{}
    );
}

inline auto Composite::count() const -> std::size_t {
    return std::ranges::fold_left(
        children | std::views::transform([](const Node& n) {
            return std::visit(CountVisitor{}, n);
        }), std::size_t{0}, std::plus{}
    );
}

inline auto Composite::depth() const -> std::size_t {
    if (children.empty()) return 1;
    auto depths = children | std::views::transform([](const Node& n) {
        return std::visit(DepthVisitor{}, n);
    });
    return 1 + std::ranges::max(depths);
}

inline auto Composite::display(std::size_t indent) const -> void {
    std::println("{:>{}}{}/", "", indent * 2, name.value);
    for (const auto& child : children) {
        std::visit(DisplayVisitor{.indent = indent + 1}, child);
    }
}

inline auto Composite::find(std::string_view target_name) const
    -> std::expected<const Leaf*, TreeError> {
    for (const auto& child : children) {
        if (auto* leaf = std::get_if<Leaf>(&child)) {
            if (leaf->name.value == target_name) return leaf;
        } else if (auto* comp = std::get_if<std::unique_ptr<Composite>>(&child)) {
            auto result = (*comp)->find(target_name);
            if (result) return result;
        }
    }
    return std::unexpected(TreeError::node_not_found);
}

// Factory helpers [I.4]
[[nodiscard]] auto make_leaf(std::string name, double value) -> Leaf {
    return Leaf{
        .name  = NodeName{std::move(name)},
        .value = NodeValue{value}
    };
}

[[nodiscard]] auto make_composite(std::string name)
    -> std::unique_ptr<Composite> {
    return std::make_unique<Composite>(
        Composite{.name = NodeName{std::move(name)}}
    );
}
```

## Usage

```cpp
auto main() -> int {
    // Build file system tree
    auto root = make_composite("root");

    auto src = make_composite("src");
    src->add(make_leaf("main.cpp", 1200));
    src->add(make_leaf("engine.cpp", 3400));

    auto tests = make_composite("tests");
    tests->add(make_leaf("unit_test.cpp", 800));
    tests->add(make_leaf("bench.cpp", 600));

    root->add(make_leaf("CMakeLists.txt", 150));
    root->add(std::move(src));
    root->add(std::move(tests));

    // Uniform operations on entire tree
    root->display();
    std::println("Total size: {:.0f} bytes", root->sum());
    std::println("File count: {}", root->count());
    std::println("Tree depth: {}", root->depth());

    // Search
    auto found = root->find("engine.cpp");
    if (found) {
        std::println("Found: {} = {}", (*found)->name.value, (*found)->value.value);
    }

    auto missing = root->find("missing.cpp");
    if (!missing) {
        std::println("File not found");
    }
}
```

## Safety Checklist

```
✓ Type Safety    — variant enforces Leaf/Composite; NodeName/NodeValue strong types
✓ Bounds Safety  — std::vector; ranges::fold_left; views::transform; no indexing
✓ Lifetime Safety — unique_ptr for Composite children; value semantics for Leaf
✓ Init Safety    — All members initialized; children empty by default
✓ Error Safety   — std::expected on find(); no sentinel nullptr
Guidelines: P.4, R.20, C.48, ES.20, E.2, ES.71, T.10
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect        | Benefit                                  | Cost                               |
|---------------|------------------------------------------|------------------------------------|
| Uniformity    | Leaf and Composite treated identically   | Recursive type needs unique_ptr    |
| Type Safety   | variant enforces valid node types        | Adding node type = update visitors |
| Performance   | No vtable; stack-allocated leaves        | unique_ptr heap alloc for composites|
| Operations    | New operations = new visitor struct      | Recursive traversal can be deep    |

## Related Patterns

- **Visitor** — Apply operations to composite structures
- **Iterator** — Traverse composite structure linearly
- **Decorator** — Wraps single object; Composite wraps many
