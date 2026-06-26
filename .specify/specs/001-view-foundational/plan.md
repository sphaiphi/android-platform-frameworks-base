# Implementation Plan: Foundational View Classes

**Feature ID:** 001-view-foundational
**Spec:** .specify/specs/001-view-foundational/spec.md
**Status:** Draft
**Created:** 2026-06-13

---

## Architecture Overview

This feature implements the core building blocks of a standalone C++ View system: `View`, `ViewGroup`, `ViewParent` (via CRTP), `ViewManager` (via CRTP), `LayoutParams`, and `MeasureSpec`. The system is a native C++23 reimplementation of the Java `android.view.*` package, not a JNI wrapper.

Data flows through three phases: measure (top-down, children report desired size), layout (top-down, parent assigns absolute position), and draw (top-down, parent draws background, children, then foreground). Touch events flow bottom-up through dispatch, with optional interception by ViewGroups.

The key architectural decision is using CRTP (Curiously Recursive Template Pattern) for the ViewParent and ViewManager interfaces, satisfying Constitution Principle II (zero-cost abstractions). View and ViewGroup inherit from CRTP mixins via private inheritance, so the VTable overhead is zero for all ViewParent/ViewManager method calls -- dispatch is resolved at compile time.

```
                    +------------------+
                    |  ViewParentMixin |  (CRTP, zero overhead)
                    |  <ViewGroup>     |
                    +--------+---------+
                             | private
                             v
+-----------+    +------------------+    +-------------------+
|  LayoutParams  |  ViewGroup<T>    |<-->|  ViewManagerMixin |
|  (concrete)    |  : public View   |    |  <ViewGroup>      |
+-----------+    |  private VPMix   |    +-------------------+
                 +------------------+
                          ^
                          | public
                          v
                 +------------------+
                 |     View         |
                 | : VPMix<View>    |
                 | : VMMix<View>    |
                 +------------------+
```

---

## Stack Decisions

| Layer | Choice | Rationale |
|-------|--------|-----------|
| Language | C++23 | Constitution Mandate. NDK r29 Clang 18 supports all required features. |
| Build (host) | CMake | Existing repo pattern. FetchContent for GoogleTest. |
| Build (device) | ndk-build | Constitution Dependency Management table. |
| Testing | GoogleTest 1.15.2 | Existing repo pattern. Latest stable. |
| Polymorphism | CRTP (ViewParentMixin, ViewManagerMixin) | Constitution Principle II. Zero vtable overhead. |
| LayoutParams | Concrete class hierarchy + template ViewGroup | FR-39. Static polymorphism, no virtual dispatch on LayoutParams. |
| Error handling | std::expected where applicable | Constitution Principle I. |
| Container types | std::vector, std::shared_ptr | Constitution Principle I (RAII, smart pointers). |
| Any-type storage | std::any | For setTag/getTag (FR-25). |

---

## Constitution Compliance

| Principle | Compliance |
|-----------|-----------|
| **I - Safety (enum class)** | All constants use `enum class`: Visibility, LayoutDirection, ViewFlags, ViewGroupFlags, DescendantFocusability. No magic integers. |
| **I - Safety (std::span)** | No raw pointer arithmetic. Bounds-checked access via `std::span` where iterating collections. |
| **I - Safety (RAII)** | All objects use smart pointers (std::shared_ptr for View ownership). No new/delete. |
| **I - Safety (initialization)** | All fields have default values in the class definition. No uninitialized reads. |
| **I - Safety (std::expected/optional)** | std::any for getTag (null tag case). std::expected where recoverable errors possible. |
| **II - Zero-cost** | ViewParent/ViewManager via CRTP. No virtual dispatch on any ViewParent or ViewManager method. LayoutParams accessed statically through template parameter. |
| **III - TDD** | All tests written Red-Green-Refactor. Coverage target >80% per module. |
| **IV - Spec as truth** | Every FR traces to a method, field, or test. See FR traceability table below. |
| **V - Tech Stack** | All dependencies documented in research.md. No new libraries introduced. |

---

## Data Layer

### Header Files (Public API)

```
core/cpp/include/android/view/
    View.h              -- View class, enum classes, MeasureSpec
    ViewGroup.h         -- ViewGroup<TLayoutParams> class
    ViewParentMixin.h   -- CRTP ViewParent interface
    ViewManagerMixin.h  -- CRTP ViewManager interface
    LayoutParams.h      -- LayoutParams, MarginLayoutParams (existing, may be updated)
    MotionEvent.h       -- (existing, no changes)
```

### Source Files (Implementation)

```
core/cpp/src/android/view/
    View.cpp                    -- View constructor, properties, measure, layout, draw, touch
    ViewGroup.cpp               -- ViewGroup child management, measureChildren, layoutChildren, dispatchDraw, touch dispatch
    ViewParentMixin.cpp         -- (header-only CRTP, no separate .cpp needed)
    ViewManagerMixin.cpp        -- (header-only CRTP, no separate .cpp needed)
```

### Test Files

```
core/cpp/tests/
    View_foundational_test.cpp  -- View construction, properties, measure, layout, draw
    ViewGroup_foundational_test.cpp -- ViewGroup child management, measureChildren, layoutChildren, dispatchDraw
    ViewParentMixin_test.cpp    -- CRTP parent chain propagation (requestLayout, invalidate, focus)
    ViewManagerMixin_test.cpp   -- addView, updateViewLayout, removeView
    LayoutParams_test.cpp       -- (existing, extended for template ViewGroup)
```

### Key Design Decisions

1. **CRTP header-only**: ViewParentMixin and ViewManagerMixin are header-only templates. No separate .cpp files needed. The CRTP pattern resolves all dispatch at compile time.

2. **View ownership**: Children are stored as `std::shared_ptr<View>`. This matches the existing codebase pattern (existing ViewGroup_test.cpp uses shared_ptr throughout). The parent reference is a raw ViewParentMixin pointer (non-owning, set during addView).

3. **LayoutParams template**: `ViewGroup<TLayoutParams = MarginLayoutParams>` uses a template parameter so custom ViewGroups (e.g., FrameLayout) can provide their own LayoutParams subclass. The type is known at compile time, enabling static dispatch.

4. **Tag storage**: `std::any` for setTag/getTag (FR-25). Allows arbitrary type storage without virtual dispatch or type erasure overhead beyond std::any's small-object optimization.

5. **Single-threaded model**: No mutex protection. Debug assert on non-UI thread (configurable via macro).

---

## Service / Business Logic Layer

### View Class

The View class implements the core UI element with:

- **Property system**: All animated and static properties (visibility, alpha, rotation, scale, translation, padding, minWidth/minHeight, layoutDirection, flags) stored as member fields with defaults matching Java View.
- **Measure logic**: measure() calls onMeasure(). Default onMeasure() uses MeasureSpec size. resolve_size() static helper for WRAP_CONTENT resolution.
- **Layout logic**: layout() sets left/top/right/bottom and calls onLayout(). Default onLayout() is a no-op.
- **Draw logic**: draw() calls background draw, onDraw(), dispatchDraw(). Returns early if GONE.
- **Touch dispatch**: dispatchTouchEvent() calls onTouchEvent(). Returns true if consumed.
- **Parent chain**: Via ViewParentMixin<View>, provides requestLayout() propagation, invalidate propagation, focus management.
- **Manager interface**: Via ViewManagerMixin<View>, provides addView/updateViewLayout/removeView (delegated to parent).

### ViewGroup Class

The ViewGroup class extends View with hierarchical composition:

- **Child management**: Ordered vector of children with per-child LayoutParams. addView() handles parent reassignment (removes from old parent first).
- **Measure propagation**: measureChildren() iterates non-GONE children, computes child MeasureSpec from LayoutParams, calls child->measure().
- **Layout propagation**: layoutChildren() computes child positions from LayoutParams + margins, calls child->layout().
- **Draw propagation**: dispatchDraw() draws background, iterates children in z-order (respecting clip flags), draws foreground.
- **Touch routing**: dispatchTouchEvent() checks onInterceptTouchEvent(), iterates children in reverse z-order (front-to-back), falls back to onTouchEvent().
- **Touch target**: Single View* tracking the ACTION_DOWN owner.
- **Disallow intercept**: View can call requestDisallowInterceptTouchEvent() to prevent parent interception.

### ViewParentMixin<Derived> (CRTP)

Header-only mixin providing:

- requestLayout() -- propagates upward
- isLayoutRequested() -- returns derived's layoutRequested_ flag
- onDescendantInvalidated(child, target) -- propagates upward
- getParent() -- returns parent ViewParent pointer
- requestChildFocus(child, focused) -- propagates focus request upward
- clearChildFocus(child) -- clears focus and propagates upward
- focusSearch(v, direction) -- searches for nearest focusable view

### ViewManagerMixin<Derived> (CRTP)

Header-only mixin providing:

- addView(view, params) -- delegates to derived's implementation
- updateViewLayout(view, params) -- delegates to derived's implementation
- removeView(view) -- delegates to derived's implementation

---

## API Layer

The "API layer" in this context is the C++ public header interface. There is no network API -- this is a library.

### Public Headers

All public headers go under `core/cpp/include/android/view/`. Every public method is documented with Doxygen-style comments.

### Internal Headers

CRTP mixins are defined in headers (not .cpp files) because they are templates. Internal helper methods (setMeasuredDimension, generateDefaultLayoutParams) are protected or internal.

### Error Handling

- Out-of-bounds child access returns nullptr (not exception).
- Removing a non-child is a no-op (not exception).
- Adding a view with an existing parent removes it from the old parent first (mirrors Java behavior).
- Thread violations: debug assert, release ignore.

---

## UI Layer

This is a framework-level library, not an application UI. The "UI layer" here is the drawing infrastructure:

- `draw(canvas)` on View executes: background -> onDraw() -> dispatchDraw()
- `dispatchDraw(canvas)` on ViewGroup executes: background -> child draw loop -> foreground
- Child draw respects clipChildren and clipToPadding flags
- GONE views are skipped entirely in measure, layout, and draw

The Canvas interface (from the existing graphics module) must support: drawColor, drawRect, save, restore, clipRect, translate.

---

## Security Model

- **No network exposure**: This is a local C++ library. No network API.
- **Input validation**: MotionEvent coordinates validated against view bounds before dispatch.
- **Thread safety**: Single-threaded assumption. Debug assert on cross-thread calls.
- **Bounds safety**: std::span and bounds-checked access. Out-of-bounds returns nullptr.

---

## Testing Strategy

| Layer | Test Type | Coverage Target | Key Scenarios |
|-------|-----------|-----------------|---------------|
| View Properties | Unit | 90%+ | Default values, setter/getter round-trip, clamping (alpha), GONE visibility, layoutDirection/LTR/RTL, padding start/end |
| View Measure | Unit | 90%+ | EXACTLY/AT_MOST/UNSPECIFIED modes, WRAP_CONTENT fallback to minWidth/minHeight, custom onMeasure override |
| View Layout | Unit | 90%+ | layout() sets coordinates, getWidth/Height correct, translation offset in effective position |
| View Draw | Unit | 85%+ | draw() sequence, GONE early return, onDraw() override, dispatchDraw() override |
| View Touch | Unit | 85%+ | dispatchTouchEvent -> onTouchEvent, consumption return value |
| View Focus | Unit | 85%+ | requestFocus, clearFocus, isFocusable flag |
| ViewGroup Children | Unit | 90%+ | addView, removeView, getChildAt, child count, parent reference, re-parenting |
| ViewGroup Measure | Unit | 90%+ | measureChildren with various LayoutParams (MATCH_PARENT, WRAP_CONTENT, exact), GONE child skipping |
| ViewGroup Layout | Unit | 90%+ | layoutChildren with margins, child positioning relative to parent bounds |
| ViewGroup Draw | Unit | 85%+ | dispatchDraw order, clipChildren, clipToPadding, foreground drawing |
| ViewGroup Touch | Unit | 85%+ | dispatchTouchEvent intercept, child hit testing, touch target tracking, disallowIntercept |
| ViewParent CRTP | Unit | 90%+ | requestLayout propagation chain, invalidate propagation chain, focus propagation |
| ViewManager CRTP | Unit | 90%+ | addView triggers layout, updateViewLayout triggers layout, removeView clears parent |
| LayoutParams | Unit | 90%+ | width/height constants, MarginLayoutParams margins, template ViewGroup |

**Total FR coverage:** Every FR maps to at least one test case. See traceability table below.

---

## Environment & Configuration

| Variable | Purpose | Example |
|----------|---------|---------|
| CMAKE_CXX_STANDARD | C++ standard for build | 23 |
| ANDROID_NDK_HOME | NDK path for device builds | /path/to/ndk-r29 |
| GTEST_ENABLE | Enable GoogleTest | ON (default) |

No runtime environment variables needed. The View system is a pure C++ library.

---

## Deployment & Rollout

1. **Header changes**: Add View.h, ViewGroup.h, ViewParentMixin.h, ViewManagerMixin.h to public include directory. Update LayoutParams.h if needed.
2. **Source changes**: Add View.cpp, ViewGroup.cpp to CMakeLists.txt sources.
3. **Test changes**: Add test files to core/cpp/tests/CMakeLists.txt.
4. **Migration**: No database or schema migration. This is a C++ library.
5. **Rollback**: Revert git commit. No data migration to undo.
6. **Integration**: The Choreographer (already implemented) will integrate with View via requestLayout() and invalidate() hooks during the TRAVERSAL stage.

---

## FR Traceability

| FR | Implementation | Test File |
|----|---------------|-----------|
| FR-01 | View(Context) constructor | View_foundational_test.cpp |
| FR-02 | Default values in View constructor | View_foundational_test.cpp |
| FR-03 | View::measure() | View_foundational_test.cpp |
| FR-04 | View::onMeasure() virtual | View_foundational_test.cpp |
| FR-05 | getMeasuredWidth/Height | View_foundational_test.cpp |
| FR-06 | MeasureSpec enum class + make/get helpers | View_foundational_test.cpp |
| FR-07 | View::layout() | View_foundational_test.cpp |
| FR-08 | View::onLayout() virtual (no-op) | View_foundational_test.cpp |
| FR-09 | getLeft/Top/Right/Bottom/Width/Height | View_foundational_test.cpp |
| FR-10 | ViewParentMixin::requestLayout() propagation | ViewParentMixin_test.cpp |
| FR-11 | ViewParentMixin::isLayoutRequested() | ViewParentMixin_test.cpp |
| FR-12 | View::draw() sequence | View_foundational_test.cpp |
| FR-13 | View::onDraw() virtual | View_foundational_test.cpp |
| FR-14 | View::invalidate() propagation | ViewParentMixin_test.cpp |
| FR-14a | Canvas interface (6 methods) | Referenced in draw tests |
| FR-15 | Visibility enum class + getter/setter | View_foundational_test.cpp |
| FR-16 | Visibility change triggers layout | View_foundational_test.cpp |
| FR-17 | Alpha getter/setter | View_foundational_test.cpp |
| FR-18 | Rotation X/Y/Z getter/setter | View_foundational_test.cpp |
| FR-19 | Scale X/Y getter/setter | View_foundational_test.cpp |
| FR-20 | Translation X/Y getter/setter | View_foundational_test.cpp |
| FR-21 | MinWidth/MinHeight getter/setter | View_foundational_test.cpp |
| FR-22 | Padding getters/setter | View_foundational_test.cpp |
| FR-23 | LayoutDirection getter/setter | View_foundational_test.cpp |
| FR-24 | ID getter/setter | View_foundational_test.cpp |
| FR-25 | Tag getter/setter (std::any) | View_foundational_test.cpp |
| FR-26 | Focusable/Clickable flags | View_foundational_test.cpp |
| FR-27 | ViewParent::requestLayout() | ViewParentMixin_test.cpp |
| FR-28 | ViewParent::isLayoutRequested() | ViewParentMixin_test.cpp |
| FR-29 | ViewParent::onDescendantInvalidated() | ViewParentMixin_test.cpp |
| FR-30 | ViewParent::getParent() | ViewParentMixin_test.cpp |
| FR-31 | ViewParent::requestChildFocus/clearChildFocus | ViewParentMixin_test.cpp |
| FR-32 | ViewParent::focusSearch() | ViewParentMixin_test.cpp |
| FR-33 | ViewGroup inheritance model | ViewGroup_foundational_test.cpp |
| FR-34 | getChildCount() | ViewGroup_foundational_test.cpp |
| FR-35 | getChildAt() | ViewGroup_foundational_test.cpp |
| FR-36 | measureChildren() | ViewGroup_foundational_test.cpp |
| FR-37 | layoutChildren() | ViewGroup_foundational_test.cpp |
| FR-38 | dispatchDraw() | ViewGroup_foundational_test.cpp |
| FR-39 | LayoutParams hierarchy + ViewGroup template | LayoutParams_test.cpp |
| FR-40 | MarginLayoutParams fields | LayoutParams_test.cpp |
| FR-41 | FLAG_CLIP_CHILDREN | ViewGroup_foundational_test.cpp |
| FR-42 | FLAG_CLIP_TO_PADDING | ViewGroup_foundational_test.cpp |
| FR-43 | DescendantFocusability modes | ViewGroup_foundational_test.cpp |
| FR-44 | dispatchTouchEvent() | View_foundational_test.cpp, ViewGroup_foundational_test.cpp |
| FR-45 | onInterceptTouchEvent() | ViewGroup_foundational_test.cpp |
| FR-46 | onTouchEvent() | View_foundational_test.cpp |
| FR-47 | requestDisallowInterceptTouchEvent() | ViewGroup_foundational_test.cpp |
| FR-48 | touchTarget (single View*) | ViewGroup_foundational_test.cpp |
| FR-49 | addView() | ViewGroup_foundational_test.cpp |
| FR-50 | updateViewLayout() | ViewGroup_foundational_test.cpp |
| FR-51 | removeView() | ViewGroup_foundational_test.cpp |
| FR-52 | Set parent reference on addView | ViewGroup_foundational_test.cpp |
| FR-53 | Trigger layout pass after add/update/remove | ViewGroup_foundational_test.cpp |

---

## Open Questions

- [ ] **Context type**: The exact Context type/constructor signature depends on what exists in the repo. Need to verify the existing Context interface before implementation.
- [ ] **Canvas completeness**: The existing android::graphics::Canvas must have all 6 methods from FR-14a. If any are missing, they need to be added to the graphics module first.
- [ ] **Layout pass trigger**: The spec says "trigger a layout pass" after addView/updateViewLayout/removeView. In the full framework, this goes through ViewRootImpl -> Choreographer. For this feature, should we call requestLayout() directly (which propagates up the parent chain) or integrate with the Choreographer TRAVERSAL stage? The existing ViewRootImpl already integrates with Choreographer, so calling requestLayout() directly should be sufficient -- it marks the hierarchy and the Choreographer traversal picks it up.
- [ ] **focusSearch() implementation**: The spec requires focusSearch() but does not define the search algorithm. The Java implementation is complex (BFS with direction constraints). For this feature, should focusSearch() be a stub that returns nullptr, or should a basic implementation be provided? Recommended: stub returning nullptr, to be implemented in a follow-up feature.
