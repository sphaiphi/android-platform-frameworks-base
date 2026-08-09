# Safety & Guidelines Reference

## C++ Core Guidelines, mapped to what to actually check

- **P (Philosophy)** — does the code express intent directly, or does the reader have to infer it?
- **R (Resource)** — is ownership managed by RAII, with a clear owner for every resource?
- **C (Class)** — does the type follow Rule of Zero (preferred) or Rule of Five (when it must manage a resource directly)?
- **ES (Expressions & statements)** — is everything initialized at declaration, and is scope as narrow as possible?
- **E (Error handling)** — is the exception-vs-`expected` choice deliberate (see below), not incidental?
- **I (Interfaces)** — are types strong instead of primitive, and is `span`/`string_view` used for non-owning views instead of raw pointer+length pairs?
- **T (Templates)** — are constraints expressed with concepts rather than left implicit or enforced via SFINAE?

## Error handling design

- **`std::expected`** for recoverable errors that a caller is expected to handle — parse failures, "not found," validation errors.
- **Exceptions** for truly exceptional, typically unrecoverable conditions — invariant violations, out-of-memory, programmer errors.
- Avoid raw error codes with no compiler enforcement — nothing forces the caller to check them.
- Design an error taxonomy up front (an `enum class` or a small hierarchy of error types) rather than letting ad hoc string messages accumulate.
- Log and surface diagnostics at the boundary where an error is handled, not at every layer it passes through.

## Type design checklist

- Strong types for domain concepts (a `UserId` type, not a bare `int`).
- `enum class` hierarchies instead of plain `enum` or magic integers.
- `std::variant`-based sum types for "one of several known shapes" instead of a tagged struct with a manually-maintained tag.
- `std::optional` for genuine absence, not a sentinel value like `-1` or an empty string.
- `std::span` for array views instead of a pointer+size pair.

## Static analysis red flags

Watch for these even without running a tool — they're the highest-signal indicators of undefined behavior, races, leaks, and dangling references:

- Any raw pointer whose ownership isn't immediately obvious from the type
- A destructor, copy constructor, or copy assignment operator defined without its Rule-of-Five siblings
- Shared mutable state touched from more than one thread without a documented synchronization strategy
- A returned reference/pointer to a local, a temporary, or a container element that could reallocate

## Code review checklist

When reviewing (yours or someone else's) C++ code, walk through in this order:

1. **Safety compliance** — the five dimensions in the main SKILL.md, one by one.
2. **Pattern appropriateness** — is a design pattern being force-fit where a simpler structure would do, or is real complexity being under-modeled? (Defer to `software-design` skill for pattern-specific judgment.)
3. **Performance implications** — is there an obviously worse algorithmic complexity choice, or premature optimization obscuring intent?
4. **API usability** — could a caller misuse this interface and have it compile anyway? Tighten the types until misuse doesn't compile.
5. **Documentation completeness** — are non-obvious preconditions, postconditions, and ownership semantics written down, or only "known" by the author?

## Giving feedback

- Be constructive and specific: point at the line and the guideline (e.g., "R.3 — this raw pointer implies ownership; consider `unique_ptr`") rather than a general "this looks unsafe."
- Offer the alternative, not just the objection — a reviewer who says "don't use a raw pointer" without suggesting the RAII replacement isn't done reviewing.
- Explain the *why*, not just the *what* — this is what makes review feedback educational rather than just corrective.

## Quality bar (what "done" looks like)

- Zero warnings under `-Wall -Wextra -Wpedantic -Werror`
- Clean static analysis (clang-tidy, cppcheck)
- Zero sanitizer errors (ASan/TSan/UBSan)
- Every design pattern or non-obvious construct has a one-line justification for why it's there
