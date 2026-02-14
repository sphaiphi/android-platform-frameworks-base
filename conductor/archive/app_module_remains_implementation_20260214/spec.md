# Specification - Remaining App Module Implementation

## Overview
This track involves implementing the remaining core components of the `android.app` module in C++. The goal is to provide native equivalents of essential Java framework classes, enabling native applications to interact with the Android system lifecycle and management services with minimal overhead. The implementation will prioritize existing C++ specifications as the architectural source of truth while utilizing C++23 idiomatic patterns for internal logic.

## Functional Requirements
- **Prioritized Component Implementation**: Implement the following C++ classes based on the specifications in `@core/cpp/specs/android/app/`:
    - **Lifecycle & Execution**: `ActivityThread`, `Instrumentation`, `Application`, `ActivityGroup`, `AliasActivity`.
    - **Management & IPC**: `ActivityTaskManager`, `ActivityManager`, `IActivityClientController`, `AppOpsManager`.
    - **Data & Configuration**: `ActivityOptions`, `ActivityTransition`, `ApplicationErrorReport`, `ApplicationExitInfo`, `AsyncNotedAppOp`, `TaskInfo`, `WindowConfiguration`, `Notification`.
- **API Parity**: Ensure public API parity with the Java counterparts while allowing for native optimizations in internal implementation details.
- **Source of Truth**: Adhere strictly to existing `.md` specifications in `@core/cpp/specs/android/app/`. If a specification is missing or incomplete, refer to `@core/java/android.app/` for functional baseline.

## Non-Functional Requirements
- **Modern C++23 Implementation**: Use idiomatic C++23 patterns (e.g., `std::expected`, coroutines, atomic operations) for all internal logic and state management.
- **Performance**: Minimize memory footprint and ensure zero-cost abstractions wherever possible.
- **Reliability**: Maintain high stability across complex lifecycle state transitions.

## Acceptance Criteria
1.  C++ headers and source files created for all prioritized components.
2.  Components build successfully within the `ndk-build` environment.
3.  Comprehensive unit tests implemented in `core/cpp/tests/` covering public API and state transitions.
4.  Validation against relevant CTS tests shows behavioral parity with the Java framework.
5.  Lifecycle stress tests confirm stability of execution components (e.g., `ActivityThread`).

## Out of Scope
- Full reimplementation of UI rendering logic (delegated to existing windowing system).
- Implementation of deprecated components not explicitly listed.
