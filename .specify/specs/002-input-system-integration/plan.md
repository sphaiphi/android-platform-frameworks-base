# Implementation Plan: Input System Integration (InputEventReceiver)

**Branch**: `002-input-system-integration` | **Date**: 2026-05-23 | **Spec**: [spec.md](specs/002-input-system-integration/spec.md)
**Input**: Feature specification from `/specs/002-input-system-integration/spec.md`

## Summary

Implement the complete input event reception and dispatch pipeline for the Android framework C++ core. The `InputEventReceiver` reads raw `MotionEvent`/`KeyEvent` data from an `InputChannel` socket pair via a `Looper`-registered FD watcher, parses the Android `InputEvent` wire protocol binary format, and delivers events through a `std::variant<MotionEvent, KeyEvent>` callback (`onInputEvent`). After processing, `finishInputEvent()` sends the handled status back through the channel. The `ViewGroup` dispatch chain performs hit-testing, coordinate transformation, and event interception.

## Technical Context

**Language/Version**: C++23 (NDK r29 compatible)
**Primary Dependencies**: Existing `View`, `ViewGroup`, `ViewRootImpl`, `InputChannel`, `Looper` classes in `core/cpp/`
**Storage**: N/A (IPC via socket pair, no local storage)
**Testing**: GoogleTest/GoogleMock via CMake host build; Android CTS for on-device compliance
**Target Platform**: Linux host (build/test), Android device (NDK runtime)
**Project Type**: Library (static .a via CMake, shared .so via ndk-build)
**Performance Goals**: Sub-millisecond socket-to-callback latency (SC-001); zero-cost event type dispatch via `std::variant` (no virtual dispatch)
**Constraints**: Lock-free, single-threaded (Looper-thread-only); no internal synchronization; no pointer arithmetic; RAII for all resources; `std::expected` for error handling
**Scale/Scope**: ~6 new/modified headers, ~5 new/modified .cpp files, ~8+ test files; covers InputEventReceiver, InputChannel FD polling, ViewGroup dispatch, ViewRootImpl stub

## Constitution Check

*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

| Principle | Compliance | Notes |
|-----------|-----------|-------|
| I. Safety-First Design | PASS | `std::span` for buffer views, smart pointers for ownership, `std::expected` for errors, no pointer arithmetic |
| II. Zero-Cost Abstractions | PASS | `std::variant<MotionEvent, KeyEvent>` instead of virtual dispatch; `consumeEvents()` direct socket read |
| III. TDD (NON-NEGOTIABLE) | PASS | All modules have corresponding test plans in tasks.md (upcoming) |
| IV. Plan as Source of Truth | PASS | Tracked in conductor/tracks/ plan files |
| V. Tech Stack Deliberation | PASS | C++23, GoogleTest, CMake, AIDL bindings — all in approved stack |
| Code Quality: Type Safety | PASS | `enum class` for actions, strong types, no primitive obsession |
| Code Quality: Bounds Safety | PASS | `std::span<uint8_t>` for wire buffer, standard containers |
| Code Quality: Lifetime Safety | PASS | `std::shared_ptr`/`std::unique_ptr` only, RAII for FDs |
| Code Quality: Error Safety | PASS | `std::expected<T, Error>` for recoverable parse errors |

## Project Structure

### Documentation (this feature)

```text
.specify/specs/002-input-system-integration/
├── plan.md              # This file
├── research.md          # Phase 0 output
├── data-model.md        # Phase 1 output
├── quickstart.md        # Phase 1 output
├── contracts/           # Phase 1 output
│   └── input-event-receiver-api.md
└── tasks.md             # Phase 2 output (speckit-tasks)
```

### Source Code (repository)

```text
core/cpp/
├── include/android/view/
│   ├── InputEventReceiver.h       # NEW (replaces stub)
│   ├── InputEvent.h               # NEW (std::variant wrapper)
│   ├── MotionEvent.h              # EXISTING (extend)
│   ├── KeyEvent.h                 # EXISTING (extend)
│   ├── ViewGroup.h                # EXISTING (extend dispatch)
│   ├── ViewRootImpl.h             # EXISTING (add input dispatch stub)
│   └── InputChannel.h             # EXISTING (extend for FD polling)
├── src/android/view/
│   ├── InputEventReceiver.cpp     # NEW
│   ├── InputEvent.cpp             # NEW
│   ├── MotionEvent.cpp            # EXTEND
│   ├── ViewGroup.cpp              # EXTEND (add dispatch logic)
│   ├── ViewRootImpl.cpp           # EXTEND (add input dispatch stub)
│   └── InputChannel.cpp           # EXTEND (add read helpers)
├── tests/
│   ├── input_event_receiver_test.cpp    # NEW
│   ├── input_event_test.cpp             # NEW
│   ├── view_group_dispatch_test.cpp     # NEW
│   ├── view_root_impl_input_test.cpp    # NEW
│   ├── input_channel_test.cpp           # NEW (extend)
│   └── motion_event_test.cpp            # NEW (extend)
└── include/android_mock/          # EXISTING (mock Looper FD helpers)
```

**Structure Decision**: Extend existing view/ directory with new InputEventReceiver/InputEvent files. No new subdirectories needed — all files fit within the existing `core/cpp/include/android/view/`, `core/cpp/src/android/view/`, and `core/cpp/tests/` layout.

## Complexity Tracking

Not applicable — no constitution violations.
