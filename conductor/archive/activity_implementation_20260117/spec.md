# Specification: Implement Activity based on Spec

## Overview
Implement the modern C++ version of the `android::app::Activity` class, following the specification in `core/cpp/specs/android/app/Activity.md`. This implementation will prioritize lifecycle management, context integration, and strict adherence to Android platform behaviors, validated via TDD and CTS tests.

## Functional Requirements

### 1. Spec Analysis & Update
- Analyze `core/cpp/specs/android/app/Activity.md`.
- Resolve open questions regarding **Context integration** and inheritance.
- Define the modern C++23 interface for `Activity` methods, including lifecycle callbacks (`onCreate`, `onStart`, `onResume`, etc.).

### 2. Lifecycle Management
- Implement the core lifecycle state machine for `Activity`.
- Ensure state transitions match the Android framework's behavior.

### 3. Context Integration
- Correctly inherit from and integrate with `android::content::Context`.
- Ensure `Activity` has access to system services and resources through its context.

### 4. Testing & Validation
- **Unit Testing (TDD):** Write failing GoogleTest cases for lifecycle transitions and context usage *before* implementation.
- **CTS Validation:** Port or implement C++ CTS tests based on Java references in `cts/java/tests/app/src/android/app/cts/` (e.g., `LifecycleTest.java`, `ActivityCallbacksTest.java`).

## Non-Functional Requirements
- **Performance:** Zero-cost abstractions for lifecycle callbacks.
- **Safety:** Strict adherence to C++23 safety standards (Type, Bounds, Lifetime).
- **Parity:** Maintain functional parity with the Java `Activity` implementation.

## Out of Scope
- Complex UI rendering logic (handled by `View` and `SurfaceControl` tracks).
- Full `FragmentManager` implementation (if scoped as a separate track).
