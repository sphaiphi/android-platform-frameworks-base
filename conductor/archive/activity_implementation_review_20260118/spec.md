# Specification - Activity Implementation Review and Correction

## 1. Overview
This track involves a comprehensive review of the current C++ implementation of the `Activity` class (`core/cpp/include/android/app/Activity.h` and `core/cpp/src/android/app/Activity.cpp`) against its reverse-engineered specification (`core/cpp/specs/android/app/Activity.md`). The goal is to ensure a 1:1 parity between the implemented code and the specification, specifically focusing on the public API surface and lifecycle behavior.

## 2. Functional Requirements
- **1:1 API Parity**: Every public and protected method defined in `specs/android/app/Activity.md` must be present in the C++ implementation with the correct signature and return type.
- **Lifecycle Alignment**: The internal state machine transitions (e.g., `perform_create` setting the state to `CREATED`) must match the specification's logic exactly.
- **Signature Correction**: Any discrepancies in naming conventions (e.g., camelCase vs. snake_case) or parameter types between the current implementation and the spec must be corrected to align with the project's C++23 standards while respecting the spec's intent.
- **Implementation completion**: Stubs for specified methods (like `set_content_view`) should be refined to match the functional expectations of the spec where feasible within the current architecture.

## 3. Non-Functional Requirements
- **C++23 Adherence**: All corrections must use idiomatic C++23 features (e.g., `std::expected`, `[[nodiscard]]`).
- **Test Coverage**: Existing unit tests in `core/cpp/tests/Activity_test.cpp` must be updated and expanded to verify all specified methods, ensuring 100% coverage of the public API surface.

## 4. Acceptance Criteria
- All methods defined in `Activity.md` are implemented in `Activity.h/cpp`.
- Code correctly compiles and links within the existing build system.
- `framework_tests` (specifically `ActivityTest`) passes with 100% success rate.
- Any "TBD" comments in `Activity.cpp` that relate to specified functionality are addressed or updated to reflect the current implementation state accurately.

## 5. Out of Scope
- Implementation of deep dependencies like the full `Window` or `WindowManager` logic, unless required for basic API stubs.
- Refactoring of classes other than `Activity` and its direct helpers.
