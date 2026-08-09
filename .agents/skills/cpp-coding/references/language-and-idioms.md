# Language & Idioms Reference

## C++23/20 language features to reach for by default

- Concepts and constraints instead of SFINAE
- Ranges and views instead of raw loops
- Coroutines for async/generator-style control flow
- Spaceship operator (`<=>`) instead of hand-rolled comparison operators
- `std::expected`, `std::optional`, `std::variant` instead of sentinel values or unchecked unions
- Deducing `this` instead of CRTP where it simplifies the same result
- Designated initializers and default member initializers
- `constexpr`/`consteval` for anything computable at compile time

## Type system expertise

- Strong type design: wrap primitive types in domain-specific types rather than passing raw `int`/`std::string` for things like IDs, currency, units.
- Template metaprogramming, but prefer concept-constrained templates over unconstrained ones.
- Type traits for compile-time introspection and dispatch.
- Migrate SFINAE-based constraints to concepts whenever touching the code anyway.

## Memory model

- RAII as the default resource-management strategy — every acquire pairs with a destructor-driven release.
- Smart pointers by ownership shape: `unique_ptr` for exclusive ownership (the default), `shared_ptr` only when ownership is genuinely shared, `weak_ptr` to break cycles.
- Move semantics and perfect forwarding for efficient transfer of ownership; understand when copy elision/RVO already makes this free.
- Memory ordering and atomics only when lock-free code is genuinely justified (see `performance-and-concurrency.md`).
- Lifetime management: know what outlives what before writing a reference or a pointer.

## Zero-cost abstractions

- Compile-time polymorphism (templates, concepts) over runtime polymorphism when the call site is known at compile time.
- Constexpr evaluation to move work from runtime to compile time.
- Inline functions/lambdas and empty base optimization are free — use them without hesitation.

## Functional idioms

- Ranges and views composition over manual iterator juggling.
- Algorithms with projections instead of hand-written loops with an inner accessor.
- Prefer pure functions and immutability where mutation isn't the point of the function.
- Monadic operations on `std::expected`/`std::optional` (`and_then`, `transform`, `or_else`) instead of nested `if` checks.
- Fold expressions for variadic aggregation instead of recursive template unrolling.

These are the idioms that should be the *first* instinct, not a refactor applied later. If the first draft of a function reaches for a raw loop, a raw pointer, or an error code, that's the signal to reconsider before continuing.
