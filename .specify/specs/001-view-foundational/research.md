# Research: Foundational View Classes

**Feature:** 001-view-foundational
**Date:** 2026-06-13

---

## 1. C++23 Compiler Support (NDK r29)

NDK r29d (latest stable as of 2026-05) ships with Clang 18, which has near-complete C++23 support. Key C++23 features used in this plan:

- `std::expected<T, E>` -- stable in Clang 17+ (NDK r27+). Confirmed available in NDK r29.
- `std::span<T>` -- stable in Clang 14+ (NDK r24+). Confirmed available.
- `std::bit_cast`, `std::to_underlying` -- Clang 14+. Available.
- `std::format` -- Clang 15+ (NDK r26+). Available but may have limited locale support in NDK. For this feature, we do not use `std::format`.
- `std::source_location` -- Clang 14+. Available.
- `consteval`, `constexpr` lambdas -- Clang 14+. Available.

**Decision:** Use C++23 as specified. No fallback needed for NDK r29.

**Caveat:** `std::expected` is not yet in the LLVM standard library shipped with NDK r29 by default -- it requires the C++23 mode flag (`-std=c++2b` or `-std=c++23`) and may need the `expected_shim.h` already present in this repo. The existing repo has `core/cpp/include/expected_shim.h`, confirming this dependency is already managed.

---

## 2. GoogleTest Version

The existing CMakeLists.txt (core/cpp/tests/CMakeLists.txt) fetches GoogleTest v1.15.2 from GitHub. This is the latest stable release as of early 2026. No breaking changes expected for our use case.

**Decision:** Continue using GoogleTest v1.15.2 via FetchContent.

---

## 3. CRTP for ViewParent/ViewManager (Zero-Cost Abstraction)

The constitution mandates zero-cost abstractions (Principle II). CRTP is the standard C++ idiom for this:

```cpp
template <typename Derived>
class ViewParentMixin {
public:
    auto derived() -> Derived& { return static_cast<Derived&>(*this); }
    auto derived() const -> const Derived& { return static_cast<const Derived&>(*this); }

    void request_layout() {
        // Calls derived()->on_request_layout()
        auto* parent = derived().on_get_parent();
        if (parent) parent->request_layout();
    }
};
```

This pattern is well-established in the C++ ecosystem (e.g., Boost, Eigen, Loki). The existing codebase already uses `std::enable_shared_from_this<View>` in View.h, confirming this pattern is accepted.

**Decision:** Use CRTP for ViewParentMixin and ViewManagerMixin. The existing View.h already uses `std::enable_shared_from_this`, so this is consistent.

---

## 4. LayoutParams Concrete Class Hierarchy

The spec defines LayoutParams as a concrete class hierarchy (FR-39). The existing codebase already has:

```cpp
class LayoutParams {
    int32_t width;
    int32_t height;
    LayoutParams(int32_t w, int32_t h);
    virtual ~LayoutParams() = default;
};

class MarginLayoutParams : public LayoutParams {
    int32_t left_margin, top_margin, right_margin, bottom_margin;
};
```

This uses virtual dispatch on the destructor only (required for polymorphic base). The spec's FR-40 states "static polymorphism with no virtual dispatch on LayoutParams." This is a tension: the existing code has a virtual destructor but no other virtual methods.

**Decision:** Keep the existing LayoutParams/MarginLayoutParams as concrete classes. ViewGroup is templated on LayoutParams type (`ViewGroup<TLayoutParams>`), so child LayoutParams are accessed statically. The virtual destructor is the only vtable usage, which is required for safe polymorphic deletion and has negligible overhead.

**Caveat:** The existing ViewGroup does NOT use a template parameter for LayoutParams. It uses a type alias `using LayoutParams = android::view::LayoutParams`. This plan upgrades ViewGroup to `ViewGroup<TLayoutParams = MarginLayoutParams>` to satisfy FR-39's template-based custom LayoutParams requirement.

---

## 5. Canvas Interface

The spec defines a minimal Canvas interface (FR-14a) with 6 methods. The existing repo has:

- `core/cpp/include/android/graphics/Canvas.h` (referenced in tests/Canvas_test.cpp)
- `core/cpp/src/android/graphics/Canvas.cpp` (implied by Drawable_test.cpp including Canvas)

The existing Canvas already exposes the methods needed for the minimal interface. We will reference the existing Canvas interface rather than defining a new one.

**Decision:** Use the existing `android::graphics::Canvas` interface. Document its required methods in the API contract. If the existing Canvas lacks any of the 6 methods, add them.

---

## 6. MotionEvent

The spec states MotionEvent is provided by a separate input module. The existing repo has:

- `core/cpp/include/android/view/MotionEvent.h`
- `core/cpp/src/android/view/MotionEvent.cpp`

MotionEvent already has `get_x()`, `get_y()`, and `offset_location()` (used in existing ViewGroup.cpp). The existing tests include `input_event_test.cpp` and `mock_input_channel.h`.

**Decision:** Use the existing MotionEvent. No new type needed.

---

## 7. Context

The spec states Context is a minimal interface. The existing repo has `ContextThemeWrapper.h` and `ContextImpl_test.cpp`, suggesting a Context hierarchy exists. The View constructor in the spec takes a Context argument.

**Decision:** The View constructor takes `std::shared_ptr<Context>` or a Context-like type. Since the existing View.h has a default constructor `View() = default` with no Context parameter, the plan must add a Context-taking constructor. The exact Context type depends on what exists in the repo.

---

## 8. Build System

The existing repo uses CMake for host builds. The CMakeLists.txt at `core/cpp/CMakeLists.txt` builds the main library. Tests are at `core/cpp/tests/CMakeLists.txt`.

**Decision:** Continue using CMake. New source files go under `core/cpp/src/android/view/`. New headers go under `core/cpp/include/android/view/`. New tests go under `core/cpp/tests/`.

---

## 9. Existing Implementation Gaps

Comparing the spec's FR list against the existing implementation:

| Area | Existing | Missing / Needs Rewrite |
|------|----------|------------------------|
| Visibility | enum with int constants | `enum class Visibility : int` (Principle I) |
| Alpha/Rotation/Scale/Translation | Present (float fields) | rotationZ, rotationX/Y getters/setters missing |
| Padding | Missing | getPaddingLeft/Top/Right/Bottom, setPadding, getPaddingStart/End, layoutDirection |
| minWidth/minHeight | Missing | FR-21 |
| Focusable/Clickable | isFocusable/setFocusable present | isClickable/setClickable missing |
| requestLayout() propagation | Missing | FR-10, FR-11 |
| isLayoutRequested() | Missing | FR-11 |
| onDescendantInvalidated() | Missing | FR-29 |
| getParent() | Present (returns View*) | Needs to return ViewParent* via CRTP |
| requestChildFocus/clearChildFocus | Missing | FR-31 |
| focusSearch | Missing | FR-32 |
| measureChildren() | Missing | FR-36 |
| layoutChildren() | Missing | FR-37 |
| dispatchDraw() hierarchy | Basic (VISIBLE check only) | Missing clip children/padding, GONE handling, foreground |
| onInterceptTouchEvent | Present (returns false) | Missing touch target tracking, disallow intercept |
| requestDisallowInterceptTouchEvent | Missing | FR-47 |
| touchTarget | Missing | FR-48 |
| ViewManager integration | addView present but no layout pass trigger | FR-49 through FR-53 |
| GONE visibility triggers layout | Missing | FR-16 |
| Tag (arbitrary object) | Missing | FR-25 |
| LayoutParams template | Not templated | FR-39 |

---

## 10. Thread Safety

The spec and clarifications confirm single-threaded UI model (Q9). No mutex protection needed. Debug assert on non-UI thread calls.

**Decision:** Add `#ifdef DEBUG` thread-checking macro. No runtime overhead in release builds.
