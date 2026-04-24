---
name: software-design
description: |
  Expertise in software design using Gang of Four (GoF) design patterns
  implemented with modern C++23 idioms. Thinks in patterns first — identifies
  the appropriate creational, structural, or behavioral pattern before writing
  any code, then expresses intent through the C++23 type system using concepts,
  std::variant, std::expected, and deducing this. Prioritizes static
  polymorphism and compile-time safety over runtime overhead. Every design
  decision maps to C++ Core Guidelines and enforces all five safety dimensions:
  type, bounds, lifetime, initialization, and error handling.

capabilities:
  - Identify and apply GoF creational patterns (Builder, Factory, Singleton)
  - Identify and apply GoF structural patterns (Adapter, Composite, Decorator, Proxy, Bridge, Facade)
  - Identify and apply GoF behavioral patterns (Chain, Command, Observer, State, Strategy, Visitor, Template Method, Iterator)
  - Select static vs dynamic polymorphism based on compile-time knowledge
  - Implement zero-cost abstractions using concepts and templates
  - Replace virtual dispatch with std::variant and std::visit where appropriate
  - Design type-safe APIs using strong types, enum class, and explicit constructors
  - Apply std::expected for error-safe pattern interfaces
  - Compose behaviors via mixin inheritance and deducing this
  - Map every design decision to C++ Core Guidelines

constraints:
  - C++23 minimum standard; no accommodation for C++17 or below
  - All pattern implementations must pass five safety dimensions
  - Virtual functions only when runtime open-set polymorphism is required
  - No sentinel values, raw error codes, or nullable pointers for errors
  - No unconstrained templates; concepts required on all template parameters

pattern_catalog:
  creational:
    - name: Builder
      mechanism: deducing-this, mixin-inheritance
      zero_cost: true
      reference: PATTERN_BUILDER.md
    - name: Factory
      mechanism: Creatable-concept, std::expected
      zero_cost: true
      reference: PATTERN_FACTORY.md
    - name: Singleton
      mechanism: static-local, thread-safe
      zero_cost: true
      reference: null
  structural:
    - name: Adapter
      mechanism: ModernSensor-concept, std::expected
      zero_cost: true
      reference: PATTERN_ADAPTER.md
    - name: Composite
      mechanism: recursive-variant, unique_ptr
      zero_cost: true
      reference: PATTERN_COMPOSITE.md
    - name: Decorator
      mechanism: deducing-this, Service-concept, mixin
      zero_cost: true
      reference: PATTERN_DECORATOR.md
    - name: Proxy
      mechanism: std::optional, shared_ptr, std::expected
      zero_cost: false
      reference: PATTERN_PROXY.md
    - name: Bridge
      mechanism: concept-separation
      zero_cost: true
      reference: null
    - name: Facade
      mechanism: simplified-interface
      zero_cost: true
      reference: null
  behavioral:
    - name: Chain of Responsibility
      mechanism: Handler-concept, std::expected, ranges
      zero_cost: false
      reference: PATTERN_CHAIN.md
    - name: Command
      mechanism: unique_ptr, std::expected, views::reverse
      zero_cost: false
      reference: PATTERN_COMMAND.md
    - name: Observer
      mechanism: weak_ptr, SubscriptionToken, spaceship
      zero_cost: false
      reference: PATTERN_OBSERVER.md
    - name: State
      mechanism: std::variant, std::visit, type-states
      zero_cost: true
      reference: PATTERN_STATE.md
    - name: Strategy
      mechanism: SortStrategy-concept, std::function
      zero_cost: true
      reference: PATTERN_STRATEGY.md
    - name: Visitor
      mechanism: std::visit, overload-set
      zero_cost: true
      reference: PATTERN_VISITOR.md
    - name: Template Method
      mechanism: CRTP, deducing-this
      zero_cost: true
      reference: null
    - name: Iterator
      mechanism: ranges, views
      zero_cost: true
      reference: null

polymorphism_guide:
  compile_time_known: "concepts + templates (zero cost)"
  closed_set_runtime: "std::variant + std::visit (zero cost)"
  open_set_runtime: "std::function or virtual dispatch (runtime cost)"

safety_dimensions:
  - type: "strong types, enum class, explicit ctors, concepts"
  - bounds: "std::span, std::vector, ranges, no C arrays"
  - lifetime: "RAII, smart pointers, weak_ptr, [[nodiscard]]"
  - initialization: "in-class initializers, const default, no two-phase init"
  - error_handling: "std::expected for recoverable, [[nodiscard]] on fallible"

core_guidelines:
  - "P.1: Express ideas directly in code"
  - "P.4: Ideally, a program should be statically type safe"
  - "P.5: Prefer compile-time checking to run-time checking"
  - "R.1: Manage resources automatically using RAII"
  - "R.20: Use unique_ptr or shared_ptr to represent ownership"
  - "C.46: By default, declare single-argument constructors explicit"
  - "ES.20: Always initialize an object"
  - "I.4: Make interfaces precisely and strongly typed"
  - "I.13: Do not pass an array as a single pointer"
  - "T.10: Specify concepts for all template arguments"
  - "E.2: Throw an exception to signal that a function can't perform its task"
  - "Enum.3: Prefer class enums over plain enums"

references:
  - PATTERN_BUILDER.md
  - PATTERN_FACTORY.md
  - PATTERN_STRATEGY.md
  - PATTERN_STATE.md
  - PATTERN_OBSERVER.md
  - PATTERN_COMMAND.md
  - PATTERN_VISITOR.md
  - PATTERN_DECORATOR.md
  - PATTERN_PROXY.md
  - PATTERN_COMPOSITE.md
  - PATTERN_ADAPTER.md
  - PATTERN_CHAIN.md
---

## Description

Expertise in software design using Gang of Four (GoF) design patterns implemented with modern C++23 idioms. Prioritizes static polymorphism, compile-time safety, and zero-cost abstractions. Thinks in patterns first — identifies the appropriate pattern before writing any code, then expresses it through the C++23 type system.

---

## Design Thinking Process

Every design task follows this sequence:

```
1. CLASSIFY PROBLEM
   → Creational?  — object creation is complex or must vary
   → Structural?  — interface mismatch or composition needed
   → Behavioral?  — algorithm, responsibility, or state varies

2. SELECT PATTERN
   → Match problem to pattern catalog (see Pattern Selection Matrix)
   → Evaluate compile-time vs runtime polymorphism

3. APPLY SAFETY
   → Type safety: strong types, concepts, enum class
   → Bounds: span, ranges, standard containers
   → Lifetime: RAII, smart pointers, weak_ptr
   → Init: in-class initializers, const default
   → Error: std::expected for recoverable failures

4. IMPLEMENT
   → Use C++23 features: deducing this, ranges, variant, expected
   → Annotate with Core Guideline references

5. VALIDATE
   → Compile-time: concept violations caught
   → Runtime: std::expected error paths covered
   → Zero-cost: no vtable where static polymorphism suffices
```

---

## Pattern Catalog

### Creational Patterns

#### Builder [`PATTERN_BUILDER.md`]

**Intent:** Step-by-step construction of complex objects with fluent interface.

**C++23 Key:** Deducing this for method chaining; mixin inheritance for role composition.

**Signature:**
```cpp
template<typename... Roles>
class RoleBuilder
    : public PersonBuilder<RoleBuilder<Roles...>, Roles...>
    , public MaybeInherit<EmployeeRoleMixin<...>, HasRole<EmployeeData, Roles...>>;

auto result = EmployeeBuilder{}
    .name("Alice").department("Eng").salary(95000).build();
```

**Use when:** Multi-step construction, optional parameters, immutable product.

**Zero cost:** ✓ Deducing this inlined by compiler.

---

#### Factory [`PATTERN_FACTORY.md`]

**Intent:** Create objects without specifying exact type; creation can fail.

**C++23 Key:** `Creatable` concept enforces `T::create(Params)` contract; `std::expected` for creation errors.

**Signature:**
```cpp
template<typename T>
concept Creatable = requires(typename T::Params p) {
    { T::create(p) } -> std::same_as<std::expected<T, CreationError>>;
};

template<Creatable T>
[[nodiscard]] auto make(typename T::Params params)
    -> std::expected<T, CreationError>;
```

**Use when:** Polymorphic creation, plugin systems, creation can fail in expected ways.

**Zero cost:** ✓ Compile-time path; runtime registry adds map lookup.

---

### Structural Patterns

#### Adapter [`PATTERN_ADAPTER.md`]

**Intent:** Convert legacy/third-party interface to modern target interface.

**C++23 Key:** `ModernSensor` concept defines target contract; legacy int error codes mapped to `std::expected`.

**Signature:**
```cpp
template<typename T>
concept ModernSensor = requires(T t, SensorId id) {
    { t.read(id) }  -> std::same_as<std::expected<Temperature, SensorError>>;
    { t.connect() } -> std::same_as<std::expected<void, SensorError>>;
};

class LegacySensorAdapter { /* wraps C API → std::expected */ };
static_assert(ModernSensor<LegacySensorAdapter>);
```

**Use when:** C API wrapping, third-party library integration, interface unification.

**Zero cost:** ✓ Concept adapter; object adapter is thin wrapper.

---

#### Composite [`PATTERN_COMPOSITE.md`]

**Intent:** Tree structures where leaves and composites are treated uniformly.

**C++23 Key:** Recursive `std::variant<Leaf, unique_ptr<Composite>>`; `std::visit` for exhaustive operations.

**Signature:**
```cpp
using Node = std::variant<Leaf, std::unique_ptr<Composite>>;

struct Composite {
    NodeName          name;
    std::vector<Node> children;
    auto sum()   const -> double;
    auto depth() const -> std::size_t;
    auto find(std::string_view) const -> std::expected<const Leaf*, TreeError>;
};
```

**Use when:** File systems, UI trees, AST, recursive part-whole hierarchies.

**Zero cost:** ✓ No vtable; stack-allocated leaves.

---

#### Decorator [`PATTERN_DECORATOR.md`]

**Intent:** Layer cross-cutting behavior (logging, caching, timing) without modifying base type.

**C++23 Key:** Deducing this for transparent forwarding; `Service` concept constrains decoration target.

**Signature:**
```cpp
template<Service Base>
class LoggingDecorator : public Base {
    auto handle(this auto&& self, Request req) -> decltype(auto) {
        log_before(req);
        auto r = Base::handle(std::forward<decltype(self)>(self), req);
        log_after(r);
        return r;
    }
};

using Decorated = TimingDecorator<LoggingDecorator<DataService>>;
```

**Use when:** Cross-cutting concerns, behavior composition without inheritance explosion.

**Zero cost:** ✓ Compile-time mixin; no vtable.

---

#### Proxy [`PATTERN_PROXY.md`]

**Intent:** Control access to a subject — lazy init, protection, caching.

**C++23 Key:** `std::optional` for lazy init; `std::expected` for access errors; `[[nodiscard]]` enforces result checking.

**Proxy Types:**

| Type       | Mechanism           | Use Case                  |
|------------|---------------------|---------------------------|
| Virtual    | `std::optional`     | Expensive init on demand  |
| Protection | `std::expected`     | Authorization / ACL       |
| Cache      | `unordered_map`+TTL | Transparent result caching|

**Signature:**
```cpp
class LazyDatabaseProxy {
    mutable std::optional<DatabaseService> service_{};
public:
    [[nodiscard]] auto fetch(ResourceId id) const
        -> std::expected<Data, AccessError>;
};
```

**Use when:** Expensive object init, access control, transparent caching.

**Zero cost:** ✗ Adds optional/shared_ptr indirection by design.

---

### Behavioral Patterns

#### Chain of Responsibility [`PATTERN_CHAIN.md`]

**Intent:** Pass request through a handler pipeline; first handler to claim it wins.

**C++23 Key:** `Handler` concept; `std::expected` with `not_handled` sentinel; range-based pipeline.

**Signature:**
```cpp
template<typename T>
concept Handler = requires(T t, const Request& r) {
    { t.handle(r) } -> std::same_as<std::expected<Response, HandlerError>>;
};

auto chain = HandlerChain{}
    .add(AuthHandler{})
    .add(ValidationHandler{})
    .add(ProcessingHandler{});

auto result = chain.process(request);
```

**Use when:** Middleware pipelines, configurable processing chains, auth/validation stacks.

**Zero cost:** ✗ std::function indirection per handler.

---

#### Command [`PATTERN_COMMAND.md`]

**Intent:** Encapsulate operations as objects with undo/redo support.

**C++23 Key:** `unique_ptr<ICommand>` ownership; `std::expected` for execute/undo errors; `views::reverse` for undo.

**Signature:**
```cpp
class ICommand {
    [[nodiscard]] virtual auto execute() -> std::expected<void, CommandError> = 0;
    [[nodiscard]] virtual auto undo()    -> std::expected<void, CommandError> = 0;
};

class CommandHistory {
    [[nodiscard]] auto execute(std::unique_ptr<ICommand>) -> std::expected<void, CommandError>;
    [[nodiscard]] auto undo() -> std::expected<void, CommandError>;
    [[nodiscard]] auto redo() -> std::expected<void, CommandError>;
};
```

**Use when:** Undo/redo, operation queuing, macro recording.

**Zero cost:** ✗ Virtual dispatch required for runtime composability.

---

#### Observer [`PATTERN_OBSERVER.md`]

**Intent:** One-to-many event notification with automatic lifetime management.

**C++23 Key:** `weak_ptr` auto-cleans destroyed observers; `SubscriptionToken` for type-safe unsubscription; spaceship operator on token.

**Signature:**
```cpp
struct SubscriptionToken {
    std::uint64_t id{};
    auto operator<=>(const SubscriptionToken&) const = default;
};

class SensorSubject {
    [[nodiscard]] auto attach(std::shared_ptr<ISensorObserver>) -> SubscriptionToken;
    [[nodiscard]] auto attach(std::function<void(const SensorEvent&)>) -> SubscriptionToken;
    auto detach(SubscriptionToken) -> void;
    auto notify(const SensorEvent&) -> void;
};
```

**Use when:** Event-driven systems, UI data binding, publish-subscribe.

**Zero cost:** ✗ weak_ptr lock + std::function indirection.

---

#### State [`PATTERN_STATE.md`]

**Intent:** Behavior changes with state; illegal states unrepresentable.

**C++23 Key:** `std::variant<Idle, Running, Paused, Stopped>`; legal transitions encoded in return types; `std::visit` for dispatch.

**Signature:**
```cpp
using State = std::variant<Idle, Running, Paused, Stopped>;

class StateMachine {
    State state_{Idle{}};
public:
    [[nodiscard]] auto handle(Event event)
        -> std::expected<void, TransitionError>;
};

// Illegal states are compile-time impossible:
// State s = 42;  // ✗ not a legal state type
```

**Use when:** Object behavior depends on internal state; illegal transitions must be prevented.

**Zero cost:** ✓ No vtable; variant is stack-allocated.

---

#### Strategy [`PATTERN_STRATEGY.md`]

**Intent:** Swap algorithms independently of their context.

**C++23 Key:** `SortStrategy` concept for compile-time selection; `std::function` for runtime selection.

**Signature:**
```cpp
template<typename T>
concept SortStrategy = requires(T t, std::span<int> data) {
    { t.sort(data) } -> std::same_as<SortMetrics>;
};

// Compile-time: zero overhead
template<SortStrategy Strategy>
class Sorter { Strategy strategy_{}; };

// Runtime: user-driven
class RuntimeSorter { std::function<SortMetrics(std::span<int>)> strategy_; };
```

**Use when:** Multiple algorithm variants; compile-time if known, runtime if user-driven.

**Zero cost:** ✓ Compile-time path; ✗ runtime std::function.

---

#### Visitor [`PATTERN_VISITOR.md`]

**Intent:** Operations on heterogeneous collections without modifying element types.

**C++23 Key:** `overload{}` helper + `std::visit`; compiler enforces exhaustive handling of all variant types.

**Signature:**
```cpp
template<typename... Ts>
struct overload : Ts... { using Ts::operator()...; };

using Shape = std::variant<Circle, Rectangle, Triangle>;

auto area = std::visit(AreaVisitor{}, shape);

// Compile-time exhaustiveness:
// Add new Shape member → all visitors must be updated ✓
```

**Use when:** Heterogeneous collections with stable element types; many operations added over time.

**Zero cost:** ✓ No vtable; overload resolved at compile time.

---

## Pattern Selection Matrix

```
PROBLEM                                  PATTERN
─────────────────────────────────────────────────────────────────
Complex object construction            → Builder
Creation varies by type or config      → Factory
Interface mismatch / C API wrapping    → Adapter
Tree / part-whole hierarchy            → Composite
Add behavior without modifying class   → Decorator
Control access to another object       → Proxy
Pipeline of conditional handlers       → Chain of Responsibility
Encapsulate operation with undo/redo   → Command
One-to-many event notification         → Observer
Behavior changes with internal state   → State
Swap algorithm at compile or runtime   → Strategy
Operations on heterogeneous collection → Visitor
```

---

## Polymorphism Decision Guide

```
Is the type known at compile time?
├── Yes → Static Polymorphism (concepts + templates)
│         Zero cost, compiler-enforced
│         Examples: Strategy, Builder, Decorator (compile-time)
│
└── No  → Dynamic Polymorphism
          ├── Closed set of types → std::variant + std::visit
          │   Zero cost, exhaustive (State, Visitor, Composite)
          │
          └── Open set of types  → std::function / virtual
              std::function: lightweight, stateless or stateful closure
              virtual: stateful, hierarchical, complex behavior
              Examples: Observer, Command, Chain (runtime)
```

---

## C++23 Feature → Pattern Mapping

| C++23 Feature       | Patterns Using It                              |
|---------------------|------------------------------------------------|
| Deducing this       | Builder, Decorator, Strategy (compile-time)    |
| Concepts            | Builder, Factory, Adapter, Decorator, Strategy |
| std::variant        | State, Visitor, Composite                      |
| std::visit          | State, Visitor, Composite                      |
| std::expected       | Factory, Adapter, Command, Chain, Proxy        |
| std::optional       | Proxy (lazy init), Factory (absence)           |
| weak_ptr            | Observer (lifetime safety)                     |
| Spaceship operator  | Observer (SubscriptionToken), Builder (types)  |
| Ranges / views      | Visitor, Chain, Composite, Command             |
| unique_ptr          | Command, Composite, Proxy, Chain               |
| std::function       | Observer, Strategy (runtime), Chain            |

---

## Safety Quick Reference

Every pattern output must satisfy:

```
✓ Type Safety    — Strong domain types; enum class; concepts constrain templates
✓ Bounds Safety  — std::span; std::vector; ranges; no C arrays
✓ Lifetime Safety— RAII; smart pointers; weak_ptr for cycles; no dangles
✓ Init Safety    — In-class initializers; const default; no two-phase init
✓ Error Safety   — std::expected for recoverable; [[nodiscard]] on fallible
```

---

## Anti-Pattern Reference

| Anti-Pattern                       | Modern Replacement                      | Guideline |
|------------------------------------|-----------------------------------------|-----------|
| Visitor via virtual `accept()`     | `std::visit` + overload set             | P.4, T.10 |
| State via raw `enum` + switch      | `std::variant` type states              | Enum.3    |
| Strategy via virtual base          | Concept-constrained template            | T.10      |
| Builder via telescoping ctor       | Deducing this + mixin builder           | C.46      |
| Observer raw callbacks             | `weak_ptr` + `SubscriptionToken`        | R.21      |
| Chain via raw linked-list pointers | `std::vector<HandlerEntry>` + ranges    | R.11      |
| Composite via virtual + raw ptr    | `std::variant` + `unique_ptr` node      | R.20      |
| Decorator via inheritance explosion| Concept-constrained mixin template      | T.10      |
| Adapter returning error int        | `std::expected<T, ErrorEnum>`           | E.2       |
| Factory returning nullptr on fail  | `std::expected<T, CreationError>`       | E.2, I.4  |
| Command throwing on undo failure   | `std::expected<void, CommandError>`     | E.2       |
| Proxy returning null on no access  | `std::expected<T, AccessError>`         | E.2       |

---

## Validation Checklist

Before finalizing any design:

```
[ ] Pattern identified and justified
[ ] Polymorphism type selected (static / variant / dynamic)
[ ] All five safety dimensions satisfied
[ ] C++23 features used where applicable
[ ] [[nodiscard]] on all fallible and resource-returning functions
[ ] No sentinel values for errors (use std::expected)
[ ] No illegal states representable (use variant / strong types)
[ ] No raw ownership pointers
[ ] Compile-time violations demonstrated in usage examples
[ ] Related patterns considered
```

---

## Dependencies

```yaml
language: c++23
compiler:
  gcc: ">=13.0"
  clang: ">=16.0"

standard_library:
  - "<expected>"
  - "<variant>"
  - "<concepts>"
  - "<ranges>"
  - "<memory>"
  - "<functional>"
  - "<coroutine>"

pattern_references:
  - PATTERN_BUILDER.md
  - PATTERN_FACTORY.md
  - PATTERN_ADAPTER.md
  - PATTERN_COMPOSITE.md
  - PATTERN_DECORATOR.md
  - PATTERN_PROXY.md
  - PATTERN_CHAIN.md
  - PATTERN_COMMAND.md
  - PATTERN_OBSERVER.md
  - PATTERN_STATE.md
  - PATTERN_STRATEGY.md
  - PATTERN_VISITOR.md

guidelines:
  core: https://isocpp.github.io/CppCoreGuidelines/
  patterns: https://refactoring.guru/design-patterns
```

---

## References

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [GoF Design Patterns](https://refactoring.guru/design-patterns)
- [cppreference C++23](https://en.cppreference.com/w/cpp/23)
- [Agent Skills Specification](https://agentskills.io/specification)
- [Agent Skills](./SKILL.md)