# Anti-Patterns & Misconceptions Reference

## Legacy patterns to unlearn

Each of these was reasonable at some point in C++'s history but has a strictly better modern replacement — flag them even in code that "already works":

| Legacy pattern | Why it's out | Modern replacement |
|---|---|---|
| Manual memory management (`new`/`delete`) | No exception safety, easy to leak or double-free | RAII, smart pointers |
| Raw pointers for ownership | Ownership is invisible in the type | `unique_ptr`/`shared_ptr`, or a non-owning `span`/reference if it never owned anything |
| `NULL` instead of `nullptr` | `NULL` is often just `0`, which is type-unsafe in overload resolution | `nullptr` |
| C-style casts | Silently does whatever cast is "closest," hiding intent and danger | `static_cast`, `dynamic_cast`, `const_cast` as appropriate |
| `typedef` instead of `using` | `using` supports template aliases and reads left-to-right | `using` |
| Macros for constants | No type, no scope, no debugger visibility | `constexpr` variables |
| Plain `enum` | Implicit int conversion, name pollution in enclosing scope | `enum class` |
| SFINAE when concepts are available | Cryptic error messages, harder to read | Concepts |
| Virtual functions when static polymorphism suffices | Runtime overhead and indirection for a decision known at compile time | Templates, CRTP, deducing `this` |
| Exceptions for control flow | Expensive on the thrown path, obscures normal flow | `std::expected`/`std::optional` for expected outcomes |

## Misconceptions worth correcting

These come up often enough in review discussions that it's worth having the counter-argument ready:

- **"Templates are slow"** — they're resolved at compile time; the generated code is typically as fast as hand-written specialized code, sometimes faster due to inlining opportunities.
- **"Virtual functions are always needed for polymorphism"** — static polymorphism (templates, CRTP, concepts) covers most cases where the concrete type is known at compile time, with zero runtime indirection.
- **"Exceptions are expensive"** — only on the thrown path; the non-throwing happy path costs nothing on modern implementations (table-based unwinding).
- **"`shared_ptr` is always safe"** — it can leak via reference cycles; `weak_ptr` exists specifically to break them, and using `shared_ptr` by default without considering ownership shape is itself a smell.
- **"C++ is fundamentally unsafe"** — modern C++ (RAII, smart pointers, containers, `span`, `expected`) is safe by construction when these tools are actually used; unsafety in modern C++ is usually an unforced choice, not an inherent property of the language.
- **"Performance requires unsafe code"** — zero-cost abstractions exist precisely to prove this false; safe code and fast code are usually the same code once idioms are chosen well.

## Using this reference in review

When code triggers one of the "quick anti-pattern scan" items in the main SKILL.md, this file is where the fuller explanation lives — use it to write a review comment that explains *why*, not just *what*, so the feedback teaches rather than just corrects.
