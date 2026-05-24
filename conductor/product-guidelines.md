# Product Guidelines

## Core Development Philosophy
The Android Framework Core project is built on the pillars of safety, performance, and modernity. Every line of code must adhere to the highest standards of C++23 excellence while remaining deeply integrated with the Android ecosystem.

## Coding Standards & Modernity
*   **C++23 Strictness:** Adhere strictly to C++23 standards. Utilize modern features like `std::expected`, concepts, and ranges to express intent and ensure safety.
*   **Safety-First Idioms:**
    *   **Type Safety:** Use strong types and `enum class`. Avoid primitive obsession.
    *   **Bounds Safety:** Prefer `std::span` and standard containers. No pointer arithmetic.
    *   **Lifetime Safety:** Strict RAII for all resources. Smart pointers only; no manual `new`/`delete`.
*   **Zero-Cost Abstractions:** Design for performance parity with C. If an abstraction adds overhead, it must be justified or replaced with a more efficient alternative.

## Architectural Guidelines
*   **Static Polymorphism First:** Prioritize templates and concepts over virtual functions to minimize runtime overhead and enable better compiler optimizations.
*   **Asynchronous Patterns:** Use coroutines and modern async primitives instead of callback patterns to maintain readability and avoid "callback hell."
*   **Error Handling:** Use `std::expected<T, E>` for recoverable errors. `std::optional` should denote the absence of a value, not an error state. Exceptions are reserved for truly exceptional, unrecoverable circumstances (e.g., OOM).
*   **Resource Management:** Every resource (memory, file descriptors, synchronization primitives) must be managed by an RAII-compliant object.

## Android Integration
*   **NDK Alignment:** Mirror the structure and naming conventions of the Android SDK where appropriate to ensure a familiar experience for developers.
*   **Namespace Structure:** Organize code within `android::*` namespaces (e.g., `android::view`, `android::os`) to reflect the framework's layered architecture.

## Testing & Validation
*   **Safety Compliance:** Every component must be verified against the project's five safety dimensions (Type, Bounds, Lifetime, Initialization, Error Handling).
*   **CTS Validation:** Functionality must be validated using the Android Compatibility Test Suite (CTS) to ensure system-wide reliability and interoperability.
