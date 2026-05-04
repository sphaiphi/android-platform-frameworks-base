# Track Learnings: windowing_ipc_20260502

Patterns, gotchas, and context discovered during implementation.

---

<!-- Learnings from implementation will be appended below -->

## [2026-05-04] - Phase 1: AIDL Generation & Skeleton
- **Implemented:** Point, Insets, Surface, InputChannel, PrivacyIndicatorBounds, InsetsSource, InsetsSourceControl, InsetsSourceControlArray, InsetsState, WindowRelayoutResult, IWindow, IWindowSession, WindowSession
- **Files changed:** 12 headers, 6 sources, 10 test files, 2 CMakeLists files
- **Commit:** f94c4553
- **Checkpoint:** 038fdd21
- **Learnings:**
  - Patterns: This codebase uses snake_case for C++ method names (set_initially_visible, not setInitiallyVisible)
  - Gotchas: Rect uses isEmpty() (camelCase) while most other methods use snake_case — inherited from existing code
  - Gotchas: Builder pattern with && ref-qualifier on build() requires std::move() on the caller side
  - Gotchas: std::make_shared requires public constructor; friend class not enough for allocator_traits
  - Gotchas: auto return type deduction in header declarations requires definition visible at call site — use explicit return types
  - Context: AIDL compiler v36 cannot parse parcelable types with ndk_header annotation — hand-written interfaces needed
  - Context: IWindowSession has 42 methods; only core methods (add_to_display, relayout, finish_drawing, cancel_draw, out_of_memory, remove) were implemented
  - Context: The existing codebase uses android::view namespace (not aidl::android::view)
---
