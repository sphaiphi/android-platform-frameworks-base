# Research: WindowManager Implementation

## Overview

This document records technical decisions for the WindowManager implementation, resolving all unknowns from the plan.

---

## Decision 1: WindowManager Architecture (Impl + Global)

**Context**: The Java Android framework uses a two-class pattern: `WindowManagerImpl` (public API) delegates to `WindowManagerGlobal` (singleton manager). This separates the public interface from internal state management.

**Decision**: Use `WindowManagerImpl` + `WindowManagerGlobal` pattern.

**Rationale**:
- Mirrors the Java API that NDK developers expect
- `WindowManagerImpl` can be constructed per-display (matching Java's `createWindowContext(Display)`)
- `WindowManagerGlobal` is a singleton that tracks all registered views and their ViewRootImpls
- Clean separation: public API vs. internal bookkeeping

**Alternatives considered**:
- Single WindowManager class: Simpler but mixes public API with internal state. Not idiomatic Android.
- WindowManager with injected dependencies: More testable but adds complexity for a framework class that is inherently a singleton.

---

## Decision 2: ViewRootImpl Per-View Model

**Context**: Each view added to a window gets its own `ViewRootImpl` instance. The ViewRootImpl owns the IWindow callback and the IWindowSession communication.

**Decision**: WindowManagerGlobal creates a `ViewRootImpl` for each view added via `addView()`. The ViewRootImpl is stored alongside the view in the root views list.

**Rationale**:
- Matches Android's one-ViewRootImpl-per-window model
- ViewRootImpl already exists and handles the IWindowSession IPC
- Each view is independently addressable for update/remove operations

**Alternatives considered**:
- Shared ViewRootImpl for multiple views: Would require a view hierarchy above ViewRootImpl. Not how Android works; the root view IS the window content.

---

## Decision 3: IWindow Implementation

**Context**: The IWindowSession.add_to_display() requires an `IWindow` callback. The Java `ViewRootImpl` implements `IWindow` (via `ViewRootImpl.W`).

**Decision**: `ViewRootImpl` will implement the `IWindow` interface. WindowManagerGlobal will create a `ViewRootImpl` (which is also an `IWindow`) and pass it to `IWindowSession::add_to_display()`.

**Rationale**:
- `ViewRootImpl` already has `IWindow` as a member in its header
- `ViewRootImpl` already calls `IWindowSession::add_to_display()` in `set_view()`
- The existing codebase already follows this pattern

**Alternatives considered**:
- Separate IWindow implementation class: Adds indirection without benefit. ViewRootImpl is the natural owner of the IWindow callback.

---

## Decision 4: Error Handling with std::expected

**Context**: The constitution mandates `std::expected` for recoverable errors and exceptions only for truly exceptional cases.

**Decision**: Public methods that can fail (addView, updateViewLayout, removeView) will use `std::expected<void, std::string>` to report errors. Internal methods use exceptions for programmer errors (null pointers, invalid state).

**Rationale**:
- `std::expected<void, std::string>` cleanly represents success/failure without exceptions
- Error messages map to Java exception types (BadTokenException, IllegalArgumentException)
- Consistent with project's C++23 error handling approach

**Alternatives considered**:
- Return bool with out-parameter for error: Less expressive, harder to chain.
- Exceptions for all errors: Constitution reserves exceptions for truly exceptional cases. WindowManager errors (bad token, view not attached) are recoverable programmer errors.

---

## Decision 5: Display Management

**Context**: The Java WindowManager provides `getDefaultDisplay()` and `getDisplays()`. Android supports multiple displays.

**Decision**: WindowManagerImpl will hold a `DisplayInfo` for its bound display. `getDefaultDisplay()` returns this info. `getDisplays()` returns a vector of all available displays (initially just the primary display for host builds).

**Rationale**:
- `DisplayInfo` already exists with logicalWidth, logicalHeight, rotation
- Host build has only one display, so `getDisplays()` returns a single-element vector
- Secondary display support can be added later without API changes

**Alternatives considered**:
- Full Display class with all Java Display features: Out of scope for this feature. DisplayInfo suffices for initial implementation.

---

## Decision 6: Threading Model

**Context**: WindowManager operations must handle the case where calls come from non-UI threads. Android requires WindowManager calls on the main looper.

**Decision**: For host/mock builds, WindowManager operations execute synchronously without thread checking. A `check_thread()` helper will verify the calling thread matches the main thread in future on-device builds.

**Rationale**:
- Host builds don't have a Looper/Choreographer infrastructure yet
- Synchronous execution is correct for the mock WindowSession
- Thread checking can be added when Looper infrastructure exists

**Alternatives considered**:
- Full Looper integration now: Requires implementing Choreographer, Handler, Looper infrastructure. Out of scope.
- Async operations: Adds complexity without benefit for host builds.

---

## Decision 7: LayoutParams Extension

**Context**: The current LayoutParams is minimal (width, height, MATCH_PARENT, WRAP_CONTENT). The Java WindowManager uses full WindowManager.LayoutParams with type, flags, format, gravity, etc.

**Decision**: Create a `WindowLayoutParams` class that extends `LayoutParams` with window-specific fields (type, flags, format, gravity, x, y, width, height). The `addView()` and `updateViewLayout()` methods accept `WindowLayoutParams`.

**Rationale**:
- WindowManager needs window-specific attributes beyond basic sizing
- Extending LayoutParams preserves the inheritance hierarchy
- Window types (APPLICATION, SYSTEM_OVERLAY, etc.) are defined as constants

**Alternatives considered**:
- Use existing LayoutParams directly: Would require casting everywhere and loses type safety.
- New standalone class: Duplicates LayoutParams fields and breaks compatibility.
