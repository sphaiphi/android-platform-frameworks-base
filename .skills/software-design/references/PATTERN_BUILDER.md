---
pattern: builder
category: creational
cpp_standard: c++23
complexity: low
zero_cost: true
tags: [fluent-interface, deducing-this, method-chaining, step-by-step-construction]
---

## Intent

Separate the construction of a complex object from its representation, allowing the same construction process to create different representations. In modern C++23, implemented via **deducing this** for perfect method chaining with zero overhead.

## When to Use

- Object requires many optional parameters (telescoping constructor problem)
- Construction involves multiple steps in a defined sequence
- Same construction process should produce different representations
- Immutable objects need complex initialization

## When NOT to Use

- Simple objects with few parameters → use designated initializers
- All parameters are mandatory → use constructor directly
- No variation in construction → no need for builder

## Structure

```
Director (optional)
    │
    └── Builder<Derived, RoleData...>
            ├── PersonBuilder (base: common fields)
            ├── EmployeeRoleMixin (role: employee fields)
            ├── ManagerRoleMixin  (role: manager fields)
            └── build() → Product
```

## Implementation

```cpp
#include <string>
#include <tuple>
#include <concepts>
#include <print>

// Concepts for type constraints [T.10]
template<typename T>
concept StringLike = std::convertible_to<T, std::string>;

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Role check concept
template<typename Role, typename... Roles>
concept HasRole = (std::is_same_v<Role, Roles> || ...);

// Strong domain types [P.1, I.4]
struct PersonData {
    std::string name;
    std::string email;
    unsigned int age{};
};

struct EmployeeData {
    std::string employee_id;
    std::string department;
    double salary{};
};

// Product: Person with multiple roles
template<typename... Roles>
struct Person {
    PersonData base;
    std::tuple<Roles...> roles;

    template<typename Role>
    auto get_role(this auto&& self) -> decltype(auto) {  // Deducing this [C++23]
        return std::get<Role>(std::forward<decltype(self)>(self).roles);
    }

    static constexpr auto has_role() -> bool {
        return HasRole<typename std::remove_cvref_t<void>, Roles...>;
    }
};

// Base builder — common person fields [C.46: explicit ctor]
template<typename Derived, typename... Roles>
class PersonBuilder {
protected:
    PersonData person_data_{};               // In-class init [C.48]
    std::tuple<Roles...> roles_data_{};

public:
    template<StringLike S>
    auto name(this auto&& self, S&& n) -> decltype(auto) {   // Deducing this
        self.person_data_.name = std::forward<S>(n);
        return std::forward<decltype(self)>(self);
    }

    template<StringLike S>
    auto email(this auto&& self, S&& e) -> decltype(auto) {
        self.person_data_.email = std::forward<S>(e);
        return std::forward<decltype(self)>(self);
    }

    template<Numeric N>
    auto age(this auto&& self, N a) -> decltype(auto) {
        self.person_data_.age = static_cast<unsigned int>(a);
        return std::forward<decltype(self)>(self);
    }

    auto build(this auto&& self) -> Person<Roles...> {
        return Person<Roles...>{
            std::move(self.person_data_),
            std::move(self.roles_data_)
        };
    }
};

// Role mixin — conditionally available methods [requires]
template<typename Derived, typename... Roles>
requires HasRole<EmployeeData, Roles...>
class EmployeeRoleMixin {
public:
    template<StringLike S>
    auto employee_id(this auto&& self, S&& id) -> decltype(auto) {
        std::get<EmployeeData>(self.roles_data_).employee_id = std::forward<S>(id);
        return std::forward<decltype(self)>(self);
    }

    template<StringLike S>
    auto department(this auto&& self, S&& dept) -> decltype(auto) {
        std::get<EmployeeData>(self.roles_data_).department = std::forward<S>(dept);
        return std::forward<decltype(self)>(self);
    }

    template<Numeric N>
    auto salary(this auto&& self, N sal) -> decltype(auto) {
        std::get<EmployeeData>(self.roles_data_).salary = static_cast<double>(sal);
        return std::forward<decltype(self)>(self);
    }
};

// Conditional mixin inheritance
template<typename Mixin, bool Enable>
struct MaybeInherit {};

template<typename Mixin>
struct MaybeInherit<Mixin, true> : Mixin {};

// Final builder — composed from mixins automatically
template<typename... Roles>
class RoleBuilder
    : public PersonBuilder<RoleBuilder<Roles...>, Roles...>
    , public MaybeInherit<
        EmployeeRoleMixin<RoleBuilder<Roles...>, Roles...>,
        HasRole<EmployeeData, Roles...>
      > {

    friend class PersonBuilder<RoleBuilder<Roles...>, Roles...>;

    template<typename, typename...>
    friend class EmployeeRoleMixin;
};

// Type aliases [I.4]
using EmployeeBuilder = RoleBuilder<EmployeeData>;
```

## Usage

```cpp
auto main() -> int {
    // Fluent, type-safe construction
    auto emp = EmployeeBuilder{}
        .name("Alice")
        .email("alice@company.com")
        .age(30)
        .employee_id("EMP001")
        .department("Engineering")
        .salary(95000.0)
        .build();

    std::println("Name: {}", emp.base.name);
    std::println("Dept: {}", emp.get_role<EmployeeData>().department);

    // Compile-time error: salary() not available on PersonBuilder
    // RoleBuilder<>{}.salary(1000);  // ✗ concept constraint violation
}
```

## Safety Checklist

```
✓ Type Safety    — StringLike/Numeric concepts constrain all setters
✓ Bounds Safety  — No arrays; std::tuple for role storage
✓ Lifetime Safety — build() moves data; no dangling refs
✓ Init Safety    — All members have in-class initializers {}
✓ Error Safety   — Invalid role methods rejected at compile-time
Guidelines: T.10, C.46, C.48, ES.20, P.1
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect        | Benefit                              | Cost                          |
|---------------|--------------------------------------|-------------------------------|
| Readability   | Fluent API is self-documenting       | More boilerplate code         |
| Safety        | Invalid configs fail at compile-time | Requires concept knowledge    |
| Performance   | Zero runtime cost (deducing this)    | Longer compilation            |
| Extensibility | Add roles without changing base      | Mixin specialization required |

## Related Patterns

- **Factory** — Creates objects without exposing construction logic
- **Prototype** — Clones existing objects instead of constructing new ones
- **Fluent Interface** — Method chaining style used by builder
