# Specification: NDK Upgrade and Bundle/Intent Refactoring

## Overview
This track involves upgrading the project's toolchain to Android NDK r29, which enables the use of `std::expected` for error handling. Consequently, we will revert the temporary use of `std::optional` in the `Bundle` and `Intent` implementations and perform additional refactoring to improve project structure and test quality.

## Functional Requirements
1.  **Toolchain Upgrade**: Update `conductor/tech-stack.md` and relevant build configuration files to use NDK r29.
2.  **Standardize Error Handling**: Replace all instances of `std::optional` with `std::expected` for recoverable errors in `Bundle` and `Intent` APIs.
3.  **Namespace/Directory Alignment**: Refactor the directory structure and namespaces for `Bundle` and `Intent` to ensure strict adherence to Android Framework conventions.
4.  **Test Suite Enhancement**: Reorganize and expand unit tests for `Bundle` and `Intent` to ensure robustness after refactoring.

## Non-Functional Requirements
- **C++23 Compliance**: All new and refactored code must use C++23 features where applicable (especially `std::expected`).
- **Zero-Cost Abstractions**: Maintain performance parity with previous implementations.

## Acceptance Criteria
- [ ] Project builds successfully using NDK r29.
- [ ] `Bundle` and `Intent` APIs return `std::expected` for fallible operations.
- [ ] Directory structure reflects updated namespace decisions.
- [ ] All unit tests and CTS-style tests pass.

## Out of Scope
- Implementation of additional Android Framework components beyond `Bundle` and `Intent`.
- Migration of build system from CMake to other tools (e.g., Soong/Blueprint) unless required for NDK r29.
