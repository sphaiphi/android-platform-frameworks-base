---
name: cpp-coding
description: Expert C++ standards to apply while writing or reviewing C++ code — five safety dimensions, Core Guidelines, C++23 idioms, legacy anti-patterns, Android NDK/Linux platform and tooling knowledge, performance/concurrency practice, industry standards. Consult before producing or approving any C++, even routine snippets, not only on explicit review requests. Defers design-pattern selection to software-design.
---

# C++ Expert Competency Checklist

Internalized standards, not a workflow — no deliverable of its own. Apply silently and continuously to every line of C++ written or reviewed, so output quality holds regardless of which agent produced it.

## Relationship to other skills

- **Design patterns** (creational/structural/behavioral, GoF-with-C++23) live in the `software-design` skill. If the task is "which pattern fits this problem" or "modernize this pattern implementation," go there.
- This skill covers the rest of what makes C++ code *expert-grade*: safety, idiom choice, anti-pattern recognition, platform fit, performance, and the standards a reviewer would hold code to.

## Always-apply: the five safety dimensions

Before considering any C++ code (yours or someone else's) finished, check it against all five. These are the dimensions most C++ bugs trace back to:

1. **Type safety** — no unnecessary casts, no `void*`, strong types for domain concepts instead of raw `int`/`bool` soup.
2. **Bounds safety** — containers and `span` over raw arrays/pointers; no manual index arithmetic without a guard.
3. **Lifetime safety** — RAII everywhere; no raw owning pointers; watch for dangling references and `shared_ptr` cycles.
4. **Initialization correctness** — no uninitialized variables; designated initializers and default member initializers over "set it later."
5. **Error handling** — a deliberate choice between `std::expected` and exceptions, not an accident. Recoverable errors → `std::expected`. Exceptional/unrecoverable → exceptions. Never error codes with no enforcement.

## Quick anti-pattern scan

Flag these on sight — they're near-certain signs of pre-C++23 habits leaking into new code:

- Manual `new`/`delete`, raw pointers used for ownership
- `NULL` instead of `nullptr`
- C-style casts instead of `static_cast`/`static_cast<T>`
- `typedef` instead of `using`
- Macros standing in for constants
- Plain `enum` instead of `enum class`
- SFINAE where a concept would read cleaner
- `virtual` dispatch where static polymorphism (CRTP, deducing `this`, templates) would do
- Exceptions used for ordinary control flow rather than exceptional conditions

If you catch yourself defending one of these, check `references/misconceptions.md` first — most defenses ("templates are slow," "virtual is always needed") are outdated and addressed there.

## Where to go for more depth

| Need | Reference |
|---|---|
| C++23/20 language features, type system, memory model, functional idioms | `references/language-and-idioms.md` |
| Core Guidelines mapping, code review checklist, error-handling design, API design | `references/safety-and-guidelines.md` |
| Android NDK, Linux systems programming, cross-platform build concerns, common frameworks | `references/platform-and-tooling.md` |
| Profiling, optimization technique selection, concurrency/lock-free patterns | `references/performance-and-concurrency.md` |
| Application-domain context (embedded, HPC, networking, graphics), industry/safety-certification standards | `references/domain-and-standards.md` |
| Why a "legacy" pattern is actually fine, or why a common belief about C++ is wrong | `references/misconceptions.md` |

Each file is self-contained — load only the one relevant to the current task rather than reading all of them.

## Mastery gut-check

Before an agent returns C++ code as finished — whether it's the implementation itself or a review/approval of someone else's — it should pass this quick self-test:

- Did I reach for the modern idiom first (ranges before loops, concepts before SFINAE, `expected` before exceptions-as-control-flow)?
- Is every unsafe construct (raw pointer, cast, unchecked index) either eliminated or explicitly justified?
- Would a senior reviewer need to ask "why" about any design choice, or is the intent already expressed in the types?
- Does it compile clean under `-Wall -Wextra -Wpedantic -Werror` and pass sanitizers?

If any answer is "no" or "not sure," that's the thing to fix before moving on — not a footnote for later.
