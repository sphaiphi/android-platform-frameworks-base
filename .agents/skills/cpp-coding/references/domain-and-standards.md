# Domain & Standards Reference

## Problem-solving methodology

1. **Pattern recognition** — identify the problem category first, match it to a known pattern or technique, and evaluate the trade-offs before writing code. (Defer to the `software-design` skill for GoF pattern selection specifically.)
2. **Design decisions to make explicitly**, not by default:
   - Static vs. dynamic polymorphism
   - Compile-time vs. runtime resolution
   - Value vs. reference semantics
   - Ownership model (who owns this, and how is that expressed in the type?)
3. **Safety-first approach** — type safety by construction, bounds safety through containers, lifetime safety via RAII, a deliberate error-handling strategy, and a bias toward making illegal states unrepresentable in the type system rather than checked at runtime.

## Application domains — what to weight differently by context

- **Systems programming**: OS concepts, device drivers, kernel modules, real-time constraints, direct hardware interaction.
- **Embedded systems**: resource constraints, frequently no-exceptions environments, deterministic timing requirements, power management — `std::expected` and static allocation matter more here than in general-purpose code.
- **High-performance computing**: parallel algorithms, GPU programming (CUDA/OpenCL), distributed computing, MPI, numerical stability.
- **Network programming**: socket programming, protocol implementation, async I/O (ASIO), serialization, RPC frameworks.
- **Graphics & gaming**: rendering pipelines, physics engines, entity-component systems, resource streaming, frame timing — different performance/latency tradeoffs than typical backend code.

## Industry coding standards

- Google C++ Style Guide, LLVM Coding Standards — general-purpose style references.
- AUTOSAR C++ Guidelines, MISRA C++ — automotive; considerably stricter about undefined behavior and dynamic allocation.
- JSF++ — aerospace.

## Certification contexts

Know these exist and roughly what they gate, even without being a certifying expert:

- Safety-critical: DO-178C (avionics), IEC 61508 (functional safety generally)
- Automotive: ISO 26262
- Medical: IEC 62304
- Security: Common Criteria

If a task mentions any of these domains or certifications, treat the safety bar as considerably higher than general-purpose code — favor static allocation, avoid exceptions where the standard restricts them, and be explicit about the extra rigor rather than applying the default safety checklist unchanged.

## Documentation & communication expectations

- Prefer self-documenting code through strong types over comments that explain what a weakly-typed value "really" means.
- Doxygen comments on public APIs, including preconditions/postconditions and example usage.
- Design documentation (architecture notes, pattern justification, trade-off analysis, ADRs) belongs alongside the code it explains, not only in a person's head or a chat log.
