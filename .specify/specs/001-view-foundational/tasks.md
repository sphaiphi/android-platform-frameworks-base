# Tasks: Foundational View Classes

**Feature ID:** 001-view-foundational  
**Plan:** .specify/specs/001-view-foundational/plan.md  
**Spec:** .specify/specs/001-view-foundational/spec.md  
**Generated:** 2026-06-13  
**Status:** Ready for Implementation

---

## Summary

**Total tasks:** 12  
**Estimated phases:** 5  
**Parallelisable tasks:** 4 (T-00, T-01, T-02, T-03)  
**Checkpoints:** 4

User stories covered:
- US-01: View Construction -- covered by T-04
- US-02: View Measure -- covered by T-04, T-06
- US-03: View Layout -- covered by T-04, T-06
- US-04: View Draw -- covered by T-04, T-06
- US-05: View Properties -- covered by T-04, T-06
- US-06: View Padding -- covered by T-04, T-06
- US-07: View ID -- covered by T-04, T-06
- US-08: View Tag -- covered by T-04, T-06
- US-09: ViewParent requestLayout -- covered by T-02, T-04
- US-10: ViewParent invalidate -- covered by T-02, T-04
- US-11: ViewParent focus -- covered by T-02, T-04
- US-12: ViewGroup Children -- covered by T-03, T-05
- US-13: ViewGroup Measure/Layout propagation -- covered by T-05
- US-14: ViewGroup Draw -- covered by T-05
- US-15: ViewGroup LayoutParams -- covered by T-01, T-05
- US-16: Touch Event Dispatch -- covered by T-04, T-05
- US-17: ViewManager addView -- covered by T-03, T-05
- US-18: ViewManager updateViewLayout -- covered by T-03, T-05
- US-19: ViewManager removeView -- covered by T-03, T-05

---

## Phase 1: Foundation Types

### T-00 · Verify/Define Canvas interface for drawing
**Phase:** Foundation Types  
**Depends on:** --  
**Parallel:** [P]  
**User story:** All  
**Description:**  
Create a task to verify that the existing `android::graphics::Canvas` interface provides the minimal set of methods required by FR-14a: `drawColor`, `drawRect`, `save`, `restore`, `clipRect`, and `translate`. If any are missing, they must be added to the graphics module.
**Acceptance criteria:**
- [ ] The `android::graphics::Canvas` interface is verified to contain all 6 required methods.
- [ ] If methods are missing, they are added and tested.
- [ ] A small test case verifies the interface usage in a mock context.

---

### T-01 · Create enum classes and standalone MeasureSpec header

**Phase:** Foundation Types  
**Depends on:** T-00  
**Parallel:** [P]  
**User story:** All  

**Description:**  
Create `core/cpp/include/android/view/ViewTypes.h` with all enum classes and the standalone MeasureSpec type. This header is the foundation that all other View headers depend on.

Create the following in namespace `android::view`:

1. **enum class Visibility : int** -- with values:
   - `Visible = 0`
   - `Invisible = 4`
   - `Gone = 8`
   - Implicit conversion to int via `operator int() const { return static_cast<int>(value); }`

2. **enum class LayoutDirection : int** -- with values:
   - `Ltr = 0`
   - `Rtl = 1`

3. **enum class ViewFlags : uint32_t** -- bitflags:
   - `NONE = 0x00000000`
   - `FOCUSABLE = 0x00000001`
   - `CLICKABLE = 0x00000002`
   - `LONG_CLICKABLE = 0x00000004`
   - `ENABLED = 0x00000008`

4. **enum class ViewGroupFlags : uint32_t** -- bitflags:
   - `CLIP_CHILDREN = 0x00000001`
   - `CLIP_TO_PADDING = 0x00000002`

5. **enum class DescendantFocusability : int** -- with values:
   - `FOCUS_BEFORE_DESCENDANTS = 0`
   - `FOCUS_AFTER_DESCENDANTS = 1`
   - `FOCUS_BLOCK_DESCENDANTS = 2`

6. **struct MeasureSpec** -- standalone (no longer nested in View):
   ```cpp
   struct MeasureSpec {
       static constexpr uint32_t MODE_SHIFT = 30;
       static constexpr uint32_t MODE_MASK = 0xC0000000;
       static constexpr uint32_t SIZE_MASK = 0x3FFFFFFF;

       static constexpr uint32_t UNSPECIFIED = 0x00000000;
       static constexpr uint32_t EXACTLY = 0x40000000;
       static constexpr uint32_t AT_MOST = 0x80000000;

       static auto make(uint32_t size, uint32_t mode) -> uint32_t {
           return (size & SIZE_MASK) | (mode & MODE_MASK);
       }
       static auto get_mode(uint32_t spec) -> uint32_t {
           return spec & MODE_MASK;
       }
       static auto get_size(uint32_t spec) -> uint32_t {
           return spec & SIZE_MASK;
       }
   };
   ```

**Acceptance criteria:**
- [ ] `core/cpp/include/android/view/ViewTypes.h` exists with all six enum classes/structs
- [ ] All enum values match the data-model.md specification exactly
- [ ] `MeasureSpec::make`, `MeasureSpec::get_mode`, `MeasureSpec::get_size` produce correct results: `MeasureSpec::make(100, MeasureSpec::EXACTLY)` returns `0x00000064 | 0x40000000 = 0x40000064`
- [ ] Header is self-contained (includes only `<cstdint>`)
- [ ] No compilation errors when included

---

### T-02 · Create ViewParentMixin CRTP header

**Phase:** Foundation Types  
**Depends on:** T-00, T-01  
**Parallel:** [P]  
**User story:** US-09, US-10, US-11  

**Description:**  
Create `core/cpp/include/android/view/ViewParentMixin.h`. This is a header-only CRTP template providing the ViewParent interface.

```cpp
#pragma once
#include <cstdint>
#include <android/view/ViewTypes.h>

namespace android::view {

class View;

template <typename Derived>
class ViewParentMixin {
public:
    void request_layout();
    [[nodiscard]] bool is_layout_requested() const;
    void on_descendant_invalidated(View* child, View* target);
    [[nodiscard]] ViewParentMixin<Derived>* on_get_parent() const;
    void request_child_focus(View* child, View* focused);
    void clear_child_focus(View* child);
    [[nodiscard]] View* focus_search(View* v, int direction);
};

} // namespace android::view
```

All methods are defined inline in the header (template resolution requires header-only). The `Derived` class must provide:
- `bool layoutRequested_` member
- `ViewParentMixin<Derived>* on_get_parent() const` method

**Acceptance criteria:**
- [ ] `core/cpp/include/android/view/ViewParentMixin.h` exists
- [ ] Template parameter is `typename Derived`
- [ ] All six methods are declared with correct signatures
- [ ] `request_layout()` sets `static_cast<const Derived*>(this)->layoutRequested_ = true` and propagates via `on_get_parent()`
- [ ] `is_layout_requested()` returns `static_cast<const Derived*>(this)->layoutRequested_`
- [ ] `focus_search()` returns nullptr (stub implementation per plan open question)
- [ ] Header compiles standalone (includes only `<cstdint>` and `ViewTypes.h`)

---

### T-03 · Create ViewManagerMixin CRTP header

**Phase:** Foundation Types  
**Depends on:** T-00, T-01  
**Parallel:** [P]  
**User story:** US-17, US-18, US-19  

**Description:**  
Create `core/cpp/include/android/view/ViewManagerMixin.h`. This is a header-only CRTP template providing the ViewManager interface.

```cpp
#pragma once
#include <memory>
#include <android/view/View.h>
#include <android/view/LayoutParams.h>

namespace android::view {

template <typename Derived>
class ViewManagerMixin {
public:
    void add_view(std::shared_ptr<View> view, std::shared_ptr<LayoutParams> params);
    void update_view_layout(std::shared_ptr<View> view, std::shared_ptr<LayoutParams> params);
    void remove_view(std::shared_ptr<View> view);
};

} // namespace android::view
```

All methods delegate to `static_cast<Derived*>(this)->add_view()`, etc. The `Derived` class must implement:
- `void add_view(std::shared_ptr<View>, std::shared_ptr<LayoutParams>)`
- `void update_view_layout(std::shared_ptr<View>, std::shared_ptr<LayoutParams>)`
- `void remove_view(std::shared_ptr<View>)`

**Acceptance criteria:**
- [ ] `core/cpp/include/android/view/ViewManagerMixin.h` exists
- [ ] Template parameter is `typename Derived`
- [ ] All three methods delegate to `static_cast<Derived*>(this)->method_name()`
- [ ] Header compiles standalone
- [ ] Does not pull in unnecessary dependencies

---

## Checkpoint 1: Foundation Types Ready

Before proceeding to Phase 2, verify:
- [ ] `ViewTypes.h` compiles and all enum/MeasureSpec values are correct
- [ ] `ViewParentMixin.h` compiles as a template header
- [ ] `ViewManagerMixin.h` compiles as a template header
- [ ] No circular include dependencies between the three headers

---

## Phase 2: View Refactoring

### T-04 · Refactor View to use enum classes, CRTP mixins, and add missing properties

**Phase:** View Refactoring  
**Depends on:** T-00, T-01, T-02, T-03  
**Parallel:** --  
**User story:** US-01, US-02, US-03, US-04, US-05, US-06, US-07, US-08, US-09, US-10, US-11, US-16  

**Description:**  
Refactor `core/cpp/include/android/view/View.h` and `core/cpp/src/android/view/View.cpp` to incorporate all new foundation types and CRTP mixins.

**Changes to View.h:**

1. **Add includes:** `<any>`, `<optional>`, `<android/view/ViewTypes.h>`, `<android/view/ViewParentMixin.h>`, `<android/view/ViewManagerMixin.h>`

2. **Change Visibility enum:** Replace the existing `enum Visibility { VISIBLE=0, INVISIBLE=4, GONE=8 }` with:
   ```cpp
   using Visibility = android::view::Visibility;
   ```
   Keep `static constexpr int32_t VISIBLE = 0;`, `INVISIBLE = 4;`, `GONE = 8;` as backward-compatible aliases for existing code.

3. **Change inheritance:** View now inherits from CRTP mixins:
   ```cpp
   class View : public std::enable_shared_from_this<View>,
                private ViewParentMixin<View>,
                private ViewManagerMixin<View>
   ```

4. **Remove nested MeasureSpec struct** -- use the standalone `MeasureSpec` from ViewTypes.h. Keep `View::MeasureSpec` as a `using` alias for backward compatibility:
   ```cpp
   using MeasureSpec = android::view::MeasureSpec;
   ```

5. **Add new member fields** (with default values in declaration):
   ```cpp
   std::optional<std::any> tag_;
   LayoutDirection layout_direction_{LayoutDirection::Ltr};
   int32_t padding_left_{0};
   int32_t padding_top_{0};
   int32_t padding_right_{0};
   int32_t padding_bottom_{0};
   ViewFlags flags_{ViewFlags::ENABLED};
   float mRotationX_{0.0f};
   float mRotationY_{0.0f};
   bool clickable_{false};
   bool measured_{false};
   bool layoutRequested_{false};
   ```

6. **Add new public methods:**
   ```cpp
   [[nodiscard]] std::optional<std::any> get_tag() const;
   void set_tag(std::any tag);
   [[nodiscard]] LayoutDirection get_layout_direction() const;
   void set_layout_direction(LayoutDirection direction);
   [[nodiscard]] int32_t get_padding_start() const;
   [[nodiscard]] int32_t get_padding_end() const;
   [[nodiscard]] bool is_clickable() const;
   void set_clickable(bool clickable);
   [[nodiscard]] bool is_measured() const;
   [[nodiscard]] float get_rotation_x() const;
   void set_rotation_x(float value);
   [[nodiscard]] float get_rotation_y() const;
   void set_rotation_y(float value);
   ```

7. **Update existing methods to use new types:**
   - `get_visibility()` returns `Visibility` (enum class)
   - `set_visibility(Visibility)` takes `Visibility` (enum class)

8. **Add protected method:**
   ```cpp
   [[nodiscard]] bool has_flag(ViewFlags flag) const;
   ```

**Changes to View.cpp:**

1. **Update visibility methods** to use enum class:
   ```cpp
   void View::set_visibility(Visibility visibility) {
       if (visibility_ != visibility) {
           visibility_ = visibility;
           if (visibility == Visibility::Gone || visibility_ == Visibility::Gone) {
               request_layout();
           }
       }
   }
   ```

2. **Implement new methods** for tag, layout direction, padding start/end, clickable, measured flag, rotationX/Y.

3. **Implement CRTP parent chain methods** (provided by ViewParentMixin<View>):
   - `request_layout()` -- sets `layoutRequested_ = true`, calls `on_get_parent()->request_layout()`
   - `is_layout_requested()` -- returns `layoutRequested_`
   - `invalidate()` -- calls `on_descendant_invalidated(this, this)` on parent
   - `request_focus()` -- existing plus parent propagation
   - `clear_focus()` -- existing plus parent propagation

4. **Update `measure()`** to set `measured_ = true`

5. **Update `layout()`** to clear `layoutRequested_ = false`

6. **Update `draw()`** to check `Visibility::Gone` (enum class comparison)

7. **Add `resolve_size()` static method** -- verify it uses MeasureSpec correctly

**Changes to existing tests:**

Update `core/cpp/tests/View_test.cpp` to work with enum class Visibility:
- Change `EXPECT_EQ(View::VISIBLE, view.get_visibility())` to `EXPECT_EQ(0, static_cast<int>(view.get_visibility()))`
- Change `view.set_visibility(View::INVISIBLE)` to `view.set_visibility(Visibility::Invisible)`
- Update all visibility comparisons to use enum class values

**Acceptance criteria:**
- [ ] View.h includes ViewTypes.h, ViewParentMixin.h, ViewManagerMixin.h
- [ ] View inherits from `ViewParentMixin<View>` and `ViewManagerMixin<View>` via private inheritance
- [ ] `Visibility` is `enum class Visibility : int` with values 0, 4, 8
- [ ] `MeasureSpec` is accessible as both `android::view::MeasureSpec` and `View::MeasureSpec` (alias)
- [ ] `get_tag()` returns `std::optional<std::any>`, `set_tag(std::any)` stores it
- [ ] `get_layout_direction()` / `set_layout_direction()` work with `LayoutDirection` enum class
- [ ] `get_padding_start()` returns left padding in LTR, right padding in RTL
- [ ] `get_padding_end()` returns right padding in LTR, left padding in RTL
- [ ] `is_clickable()` / `set_clickable()` work correctly
- [ ] `set_visibility(Visibility::Gone)` triggers `request_layout()` (FR-16)
- [ ] `request_layout()` propagates to parent via CRTP chain
- [ ] `invalidate()` propagates via `on_descendant_invalidated()`
- [ ] `measure()` sets `measured_ = true`
- [ ] `layout()` clears `layoutRequested_ = false`
- [ ] `draw()` returns early for `Visibility::Gone`
- [ ] `rotation_x()` / `rotation_y()` getters/setters work
- [ ] All existing tests in View_test.cpp pass after enum class updates
- [ ] `resolve_size()` correctly handles EXACTLY, AT_MOST, UNSPECIFIED modes

---

## Checkpoint 2: View Refactored

Before proceeding to Phase 3, verify:
- [ ] `core/cpp/include/android/view/View.h` compiles with all new types and CRTP inheritance
- [ ] `core/cpp/src/android/view/View.cpp` compiles with all new method implementations
- [ ] All existing View tests pass: `cd core/cpp/build_host && cmake --build . --target framework_tests && ./build_host/tests/framework_tests --gtest_filter="ViewTest*"`
- [ ] `enum class Visibility` values are correct (Visible=0, Invisible=4, Gone=8)
- [ ] `MeasureSpec` constants accessible from both `android::view::MeasureSpec` and `View::MeasureSpec`
- [ ] CRTP mixin methods (`request_layout`, `invalidate`) are callable on View instances
- [ ] Coverage >80% for View.cpp

---

## Phase 3: ViewGroup Refactoring

### T-05 · Refactor ViewGroup to use template LayoutParams, CRTP mixins, and add hierarchy management

**Phase:** ViewGroup Refactoring  
**Depends on:** T-00, T-01, T-02, T-03, T-04  
**Parallel:** --  
**User story:** US-12, US-13, US-14, US-15, US-16, US-17, US-18, US-19  

**Description:**  
Refactor `core/cpp/include/android/view/ViewGroup.h` and `core/cpp/src/android/view/ViewGroup.cpp` to incorporate template LayoutParams, CRTP mixins, and all ViewGroup-specific functionality.

**Changes to ViewGroup.h:**

1. **Convert to template class:**
   ```cpp
   template <typename TLayoutParams = MarginLayoutParams>
   class ViewGroup : public View,
                     private ViewParentMixin<ViewGroup<TLayoutParams>>,
                     private ViewManagerMixin<ViewGroup<TLayoutParams>>
   ```
   Where `TLayoutParams` must derive from `LayoutParams`.

2. **Update type aliases:**
   ```cpp
   using LayoutParamsType = TLayoutParams;
   using MarginLayoutParamsType = MarginLayoutParams;
   ```

3. **Add new member fields:**
   ```cpp
   std::vector<std::shared_ptr<View>> children_;
   std::vector<std::shared_ptr<TLayoutParams>> child_params_;
   View* touch_target_{nullptr};
   ViewGroupFlags group_flags_{ViewGroupFlags::CLIP_CHILDREN | ViewGroupFlags::CLIP_TO_PADDING};
   DescendantFocusability descendant_focusability_{DescendantFocusability::FOCUS_BEFORE_DESCENDANTS};
   bool disallow_intercept_{false};
   bool touch_intercepted_{false};
   ```

4. **Add new public methods:**
   ```cpp
   [[nodiscard]] int32_t get_child_count() const;
   [[nodiscard]] std::shared_ptr<View> get_child_at(int32_t index) const;
   [[nodiscard]] bool is_clip_children() const;
   void set_clip_children(bool clip);
   [[nodiscard]] bool is_clip_to_padding() const;
   void set_clip_to_padding(bool clip);
   [[nodiscard]] DescendantFocusability get_descendant_focusability() const;
   void set_descendant_focusability(DescendantFocusability focusability);
   void request_disallow_intercept_touch_event(bool disallow);
   void measure_children(int32_t width_spec, int32_t height_spec);
   void layout_children();
   bool dispatch_touch_event(const MotionEvent& event) override;
   [[nodiscard]] virtual bool on_intercept_touch_event(const MotionEvent& event);
   ```

5. **Add new protected methods:**
   ```cpp
   void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override;
   void on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) override;
   void dispatch_draw(android::graphics::Canvas& canvas) override;
   virtual auto generate_default_layout_params() -> std::shared_ptr<TLayoutParams>;
   ```

6. **Update add_view/remove_view/update_view_layout signatures** to accept `TLayoutParams` instead of `LayoutParams`.

**Changes to ViewGroup.cpp:**

1. **Update all method definitions** to use template syntax:
   ```cpp
   template <typename TLayoutParams>
   auto ViewGroup<TLayoutParams>::get_child_count() const -> int32_t { ... }
   ```

2. **Implement `measure_children()`:**
   - Iterate `children_`, skip GONE children
   - For each child, compute MeasureSpec from `child_params_[i]` and parent constraints
   - Call `child->measure(child_spec_width, child_spec_height)`

3. **Implement `layout_children()`:**
   - Iterate `children_`, skip GONE children
   - Compute child left/top/right/bottom from LayoutParams + margins + parent bounds
   - Call `child->layout(l, t, r, b)`

4. **Implement `dispatch_draw()`:**
   - Draw background
   - For each visible child in z-order (index 0 to N-1, back-to-front):
     - If `CLIP_CHILDREN` flag, clip canvas to ViewGroup bounds
     - Call `child->draw(canvas)`
   - Draw foreground

5. **Implement `dispatch_touch_event()`:**
   - Check `disallow_intercept_` -- if true, skip intercept check
   - Call `on_intercept_touch_event(event)` -- if true, set `touch_intercepted_ = true` and handle self
   - If not intercepted, iterate children in reverse z-order (front-to-back)
   - Fall back to `View::dispatch_touch_event(event)`

6. **Implement `add_view()`:**
   - If child has existing parent, remove from old parent first
   - Assign LayoutParams, add to `children_`, add params to `child_params_`
   - Set child's parent via `child->set_parent(this)`
   - Trigger `request_layout()`

7. **Implement `remove_view()`:**
   - Find child in `children_`, erase from both vectors
   - Clear child's parent
   - Trigger `request_layout()`

8. **Implement `update_view_layout()`:**
   - Find child in `children_`, replace LayoutParams in `child_params_`
   - Trigger `request_layout()`

9. **Add explicit template instantiations** at bottom of ViewGroup.cpp:
   ```cpp
   template class ViewGroup<MarginLayoutParams>;
   ```

**Changes to existing tests:**

Update `core/cpp/tests/ViewGroup_test.cpp`:
- `std::make_shared<ViewGroup>()` to `std::make_shared<ViewGroup<MarginLayoutParams>>()`
- `ViewGroup::LayoutParams::MATCH_PARENT` to `ViewGroup<MarginLayoutParams>::LayoutParams::MATCH_PARENT`

**Acceptance criteria:**
- [ ] ViewGroup is a template class with default `TLayoutParams = MarginLayoutParams`
- [ ] ViewGroup inherits from `View`, `ViewParentMixin<ViewGroup<T>>`, `ViewManagerMixin<ViewGroup<T>>`
- [ ] `children_` is `std::vector<std::shared_ptr<View>>`
- [ ] `child_params_` is `std::vector<std::shared_ptr<TLayoutParams>>` aligned 1:1 with children_
- [ ] `get_child_count()` returns correct count
- [ ] `get_child_at()` returns nullptr for out-of-bounds index
- [ ] `add_view()` assigns LayoutParams, sets parent, triggers layout
- [ ] `add_view()` removes child from old parent if it has one
- [ ] `remove_view()` clears child's parent and triggers layout
- [ ] `remove_view()` is a no-op if child is not a child of this ViewGroup
- [ ] `update_view_layout()` replaces LayoutParams and triggers layout
- [ ] `measure_children()` skips GONE children and computes correct MeasureSpec
- [ ] `layout_children()` positions children respecting LayoutParams and margins
- [ ] `dispatch_draw()` draws background, children in z-order, foreground
- [ ] `dispatch_draw()` respects `CLIP_CHILDREN` flag
- [ ] `dispatch_draw()` respects `CLIP_TO_PADDING` flag
- [ ] `dispatch_touch_event()` checks intercept, iterates children front-to-back
- [ ] `on_intercept_touch_event()` returns false by default
- [ ] `request_disallow_intercept_touch_event()` sets `disallow_intercept_` flag
- [ ] `touch_target_` tracks the ACTION_DOWN owner
- [ ] `is_clip_children()` / `set_clip_children()` work correctly
- [ ] `is_clip_to_padding()` / `set_clip_to_padding()` work correctly
- [ ] `get_descendant_focusability()` / `set_descendant_focusability()` work correctly
- [ ] All existing ViewGroup tests pass after template update
- [ ] Explicit template instantiation for `ViewGroup<MarginLayoutParams>` compiles

---

## Checkpoint 3: ViewGroup Refactored

Before proceeding to Phase 4, verify:
- [ ] `core/cpp/include/android/view/ViewGroup.h` compiles as a template header
- [ ] `core/cpp/src/android/view/ViewGroup.cpp` compiles with explicit template instantiation
- [ ] All existing ViewGroup tests pass: `--gtest_filter="ViewGroupTest*"`
- [ ] All existing LayoutParams tests pass
- [ ] `ViewGroup<MarginLayoutParams>` can be instantiated and used
- [ ] Template methods resolve correctly at compile time
- [ ] Coverage >80% for ViewGroup.cpp

---

## Phase 4: Tests

### T-06 · Create View_foundational_test.cpp

**Phase:** Tests  
**Depends on:** T-04  
**Parallel:** [P]  
**User story:** US-01 through US-08  

**Description:**  
Create `core/cpp/tests/View_foundational_test.cpp` with comprehensive tests for all new functionality introduced in T-04.

**Test cases:**

1. **VisibilityEnumClass** -- enum class values: Visible=0, Invisible=4, Gone=8, implicit int conversion
2. **MeasureSpecStandalone** -- `make(100, EXACTLY)` produces correct packed value, `get_mode`/`get_size` extract correctly
3. **ViewDefaultValues** -- all defaults per FR-02: visibility=VISIBLE, alpha=1.0, rotationX/Y/Z=0, scaleX/Y=1.0, translationX/Y=0, padding=(0,0,0,0), id=NO_ID, tag=nullopt, minWidth/minHeight=0, layoutDirection=LTR, focusable=false, clickable=false, enabled=true
4. **ViewPropertiesRoundTrip** -- alpha (clamped [0.0, 1.0]), rotation/rotationX/rotationY/rotationZ, scaleX/scaleY, translationX/translationY, minWidth/minHeight
5. **ViewPadding** -- setPadding(10,20,30,40), getPaddingLeft/Top/Right/Bottom, getPaddingStart/End respects layout direction
6. **ViewLayoutDirection** -- default LTR, set Rtl, get returns current
7. **ViewId** -- default NO_ID (-1), setId(100)/getId() returns 100
8. **ViewTag** -- default nullopt, setTag(std::any(42))/getTag() returns optional with 42, setTag(std::any(string)) stores string type
9. **ViewFlags** -- default ENABLED, setFocusable/isFocusable, setClickable/isClickable
10. **VisibilityTriggersLayout** -- GONE triggers requestLayout, VISIBLE/INVISIBLE does not
11. **MeasureSpecResolveSize** -- EXACTLY returns spec size, AT_MOST returns min, UNSPECIFIED returns input, WRAP_CONTENT fallback
12. **ViewMeasure** -- measure(EXACTLY_100, EXACTLY_200) sets measured dims, measured_ flag set
13. **ViewLayout** -- layout(10,20,110,120) sets coords, getWidth/Height correct, layoutRequested_ cleared
14. **ViewDraw** -- draw calls on_draw, GONE returns early, subclass can override on_draw
15. **ViewTouchDispatch** -- dispatchTouchEvent calls onTouchEvent, default returns false

**Acceptance criteria:**
- [ ] Test file exists at `core/cpp/tests/View_foundational_test.cpp`
- [ ] All 15 test groups compile and run
- [ ] Alpha clamping to [0.0, 1.0] is tested
- [ ] Padding start/end respects layout direction
- [ ] Tag stores and retrieves different types via std::any
- [ ] Visibility change to GONE triggers requestLayout
- [ ] MeasureSpec packing/unpacking is correct

---

### T-07 · Create ViewParentMixin_test.cpp and ViewManagerMixin_test.cpp

**Phase:** Tests  
**Depends on:** T-02, T-03, T-04, T-05  
**Parallel:** --  
**User story:** US-09, US-10, US-11, US-17, US-18, US-19  

**Description:**  
Create two test files for the CRTP mixin functionality.

**File: `core/cpp/tests/ViewParentMixin_test.cpp`**

1. **RequestLayoutPropagation** -- 3-level hierarchy (grandparent->parent->child), verify layoutRequested_ set on all and propagation chain
2. **IsLayoutRequested** -- default false, true after requestLayout, false after layout
3. **InvalidatePropagation** -- 3-level hierarchy, on_descendant_invalidated called on parent and grandparent, stops at root without crash
4. **FocusPropagation** -- request_child_focus propagates up, clear_child_focus propagates up, focus_search returns nullptr (stub)

**File: `core/cpp/tests/ViewManagerMixin_test.cpp`**

1. **AddViewTriggersLayout** -- add child with params, verify parent set, verify requestLayout triggered
2. **UpdateViewLayoutTriggersLayout** -- add child, update params, verify params replaced, verify requestLayout triggered
3. **RemoveViewClearsParent** -- add child, remove, verify not in list, verify parent nullptr, verify requestLayout triggered
4. **RemoveNonChildIsNoOp** -- remove_view on non-child, verify no crash, no state change

**Acceptance criteria:**
- [ ] Both test files exist at `core/cpp/tests/ViewParentMixin_test.cpp` and `core/cpp/tests/ViewManagerMixin_test.cpp`
- [ ] All 8 test groups compile and pass
- [ ] RequestLayout propagation chain verified (3-level hierarchy)
- [ ] Invalidate propagation stops at root without crash
- [ ] AddView sets parent reference and triggers layout
- [ ] RemoveView clears parent reference
- [ ] RemoveNonChild is a no-op

---

### T-08 · Create ViewGroup_foundational_test.cpp

**Phase:** Tests  
**Depends on:** T-05, T-06, T-07  
**Parallel:** --  
**User story:** US-12, US-13, US-14, US-15, US-16  

**Description:**  
Create `core/cpp/tests/ViewGroup_foundational_test.cpp` with tests for all ViewGroup-specific functionality.

**Test cases:**

1. **ChildManagement** -- initial count 0, add_view increases count, getChildAt returns correct child, out-of-bounds returns nullptr, insertion order = z-order
2. **Reparenting** -- add child A to parent1, add to parent2, verify removed from parent1, parent is parent2
3. **MeasureChildren** -- children with MATCH_PARENT, WRAP_CONTENT, exact params, verify correct MeasureSpec per child, GONE skipped
4. **LayoutChildren** -- children with LayoutParams and margins, verify left/top/right/bottom set correctly
5. **DispatchDraw** -- background first, children in z-order, foreground last, respects CLIP_CHILDREN, respects CLIP_TO_PADDING
6. **TouchDispatch** -- routes to topmost child, onInterceptTouchEvent intercepts, requestDisallowIntercept prevents intercept, ACTION_MOVE/UP go to touch target, touchTarget_ set on ACTION_DOWN
7. **ViewGroupFlags** -- isClipChildren/isClipToPadding default true, getDescendantFocusability default FOCUS_BEFORE_DESCENDANTS
8. **LayoutParamsTemplate** -- ViewGroup<MarginLayoutParams> and ViewGroup<LayoutParams> both instantiate, generateDefaultLayoutParams returns correct type

**Acceptance criteria:**
- [ ] Test file exists at `core/cpp/tests/ViewGroup_foundational_test.cpp`
- [ ] All 8 test groups compile and pass
- [ ] Reparenting correctly removes from old parent
- [ ] MeasureChildren computes correct specs for MATCH_PARENT, WRAP_CONTENT, exact
- [ ] GONE children skipped in measure and layout
- [ ] DispatchDraw respects z-order and clip flags
- [ ] Touch dispatch routes to correct child
- [ ] Touch target tracking works for gesture continuity
- [ ] Template ViewGroup instantiates correctly for different LayoutParams types

---

## Checkpoint 4: Tests Complete

Before marking the feature complete, verify:
- [ ] All test files compile and link
- [ ] All View tests pass: `--gtest_filter="ViewTest*:ViewFoundational*"`
- [ ] All ViewGroup tests pass: `--gtest_filter="ViewGroupTest*:ViewGroupFoundational*"`
- [ ] All Mixin tests pass: `--gtest_filter="ViewParentMixinTest*:ViewManagerMixinTest*"`
- [ ] All LayoutParams tests pass: `--gtest_filter="LayoutParamsTest*"`
- [ ] Overall coverage >80% for View.cpp and ViewGroup.cpp
- [ ] No new compiler warnings

---

## Phase 5: Integration

### T-09 · Update CMakeLists.txt to include new test files

**Phase:** Integration  
**Depends on:** T-06, T-07, T-08  
**Parallel:** --  
**User story:** All  

**Description:**  
Update `core/cpp/tests/CMakeLists.txt` to include the new test files in the test executable.

Add to the `add_executable(framework_tests ...)` target:
```
    View_foundational_test.cpp
    ViewParentMixin_test.cpp
    ViewManagerMixin_test.cpp
    ViewGroup_foundational_test.cpp
```

Add them near the existing View and ViewGroup test files for maintainability.

**Acceptance criteria:**
- [ ] `core/cpp/tests/CMakeLists.txt` includes all four new test files
- [ ] `cmake --build . --target framework_tests` succeeds
- [ ] All tests (including new ones) are discoverable by GoogleTest

---

### T-10 · Update existing tests for enum class and template compatibility

**Phase:** Integration  
**Depends on:** T-04, T-05  
**Parallel:** --  
**User story:** All  

**Description:**  
Update existing test files that reference the old API to work with the new enum class Visibility and template ViewGroup.

**Changes to `core/cpp/tests/View_test.cpp`:**
- `EXPECT_EQ(View::VISIBLE, view.get_visibility())` -> `EXPECT_EQ(0, static_cast<int>(view.get_visibility()))`
- `view.set_visibility(View::INVISIBLE)` -> `view.set_visibility(Visibility::Invisible)`
- `view.set_visibility(View::GONE)` -> `view.set_visibility(Visibility::Gone)`

**Changes to `core/cpp/tests/ViewGroup_test.cpp`:**
- `std::make_shared<ViewGroup>()` -> `std::make_shared<ViewGroup<MarginLayoutParams>>()`
- `ViewGroup::LayoutParams::MATCH_PARENT` -> `ViewGroup<MarginLayoutParams>::LayoutParams::MATCH_PARENT`

**Changes to `core/cpp/tests/LayoutParams_test.cpp`:**
- `ViewGroup::LayoutParams::MATCH_PARENT` -> `ViewGroup<MarginLayoutParams>::LayoutParams::MATCH_PARENT`
- `ViewGroup::MarginLayoutParams` -> `ViewGroup<MarginLayoutParams>::MarginLayoutParams`

**Acceptance criteria:**
- [ ] `core/cpp/tests/View_test.cpp` compiles and all tests pass
- [ ] `core/cpp/tests/ViewGroup_test.cpp` compiles and all tests pass
- [ ] `core/cpp/tests/LayoutParams_test.cpp` compiles and all tests pass
- [ ] No test uses the old plain enum Visibility

---

### T-11 · Verify end-to-end: build, test, coverage

**Phase:** Integration  
**Depends on:** T-09, T-10  
**Parallel:** --  
**User story:** All  

**Description:**  
Perform final verification of the complete feature implementation.

1. **Clean build:**
   ```bash
   cd core/cpp/build_host && cmake .. && cmake --build . --target framework_tests
   ```

2. **Run all tests:**
   ```bash
   ./tests/framework_tests
   ```

3. **Verify test list:**
   ```bash
   ./tests/framework_tests --gtest_list_tests
   ```
   Confirm presence of: `ViewFoundational.*`, `ViewParentMixinTest.*`, `ViewManagerMixinTest.*`, `ViewGroupFoundational.*`

4. **Verify coverage** (if gcov/lcov available):
   - Coverage >80% for View.cpp and ViewGroup.cpp

5. **Verify no regressions** -- all pre-existing tests still pass.

**Acceptance criteria:**
- [ ] Clean build succeeds with zero errors
- [ ] All tests pass
- [ ] All new test groups present in test list
- [ ] No pre-existing test failures
- [ ] Coverage >80% for View.cpp and ViewGroup.cpp

---

## Final Checkpoint: Feature Complete

Before marking the feature done, verify every acceptance criterion from the spec:

- [ ] **US-01:** View construction with Context -> tested by T-04, T-06
- [ ] **US-02:** View measure pass -> tested by T-04, T-06
- [ ] **US-03:** View layout pass -> tested by T-04, T-06
- [ ] **US-04:** View draw pass -> tested by T-04, T-06
- [ ] **US-05:** View properties (visibility, alpha, rotation, scale, translation) -> tested by T-04, T-06
- [ ] **US-06:** View padding (including start/end) -> tested by T-04, T-06
- [ ] **US-07:** View ID -> tested by T-04, T-06
- [ ] **US-08:** View Tag (std::any) -> tested by T-04, T-06
- [ ] **US-09:** ViewParent requestLayout propagation -> tested by T-02, T-07
- [ ] **US-10:** ViewParent invalidate propagation -> tested by T-02, T-07
- [ ] **US-11:** ViewParent focus management -> tested by T-02, T-07
- [ ] **US-12:** ViewGroup child management -> tested by T-05, T-08
- [ ] **US-13:** ViewGroup measure/layout propagation -> tested by T-05, T-08
- [ ] **US-14:** ViewGroup draw propagation -> tested by T-05, T-08
- [ ] **US-15:** ViewGroup LayoutParams -> tested by T-01, T-05, T-08
- [ ] **US-16:** Touch event dispatch -> tested by T-04, T-05, T-08
- [ ] **US-17:** ViewManager addView -> tested by T-03, T-05, T-07
- [ ] **US-18:** ViewManager updateViewLayout -> tested by T-03, T-05, T-07
- [ ] **US-19:** ViewManager removeView -> tested by T-03, T-05, T-07
- [ ] All FR-01 through FR-53 trace to at least one test
- [ ] All tests pass: `cd core/cpp/build_host && ./tests/framework_tests`
- [ ] No new compiler warnings
- [ ] Coverage >80% per Constitution Principle III

---

## Coverage Report

### Spec Coverage

| User Story | Acceptance Criteria | Covered By |
|---|---|---|
| US-01: View Construction | 3 criteria | T-04, T-06 |
| US-02: View Measure | 4 criteria | T-04, T-06 |
| US-03: View Layout | 3 criteria | T-04, T-06 |
| US-04: View Draw | 3 criteria | T-04, T-06 |
| US-05: View Properties | 9 criteria | T-04, T-06 |
| US-06: View Padding | 3 criteria | T-04, T-06 |
| US-07: View ID | 2 criteria | T-04, T-06 |
| US-08: View Tag | 2 criteria | T-04, T-06 |
| US-09: ViewParent requestLayout | 4 criteria | T-02, T-04, T-07 |
| US-10: ViewParent invalidate | 3 criteria | T-02, T-04, T-07 |
| US-11: ViewParent focus | 3 criteria | T-02, T-04, T-07 |
| US-12: ViewGroup Children | 4 criteria | T-05, T-08 |
| US-13: ViewGroup Measure/Layout | 4 criteria | T-05, T-08 |
| US-14: ViewGroup Draw | 3 criteria | T-05, T-08 |
| US-15: ViewGroup LayoutParams | 3 criteria | T-01, T-05, T-08 |
| US-16: Touch Event Dispatch | 5 criteria | T-04, T-05, T-08 |
| US-17: ViewManager addView | 3 criteria | T-03, T-05, T-07 |
| US-18: ViewManager updateViewLayout | 2 criteria | T-03, T-05, T-07 |
| US-19: ViewManager removeView | 3 criteria | T-03, T-05, T-07 |

### Plan Coverage

| Plan Section | Covered By |
|---|---|
| View.h (enum classes, CRTP, new fields) | T-04, T-06 |
| ViewGroup.h (template, CRTP, new fields) | T-05, T-08 |
| ViewParentMixin.h (CRTP header) | T-02, T-07 |
| ViewManagerMixin.h (CRTP header) | T-03, T-07 |
| View.cpp (new methods, refactored) | T-04, T-06 |
| ViewGroup.cpp (template impl, refactored) | T-05, T-08 |
| ViewTypes.h (enum classes, MeasureSpec) | T-01 |
| LayoutParams.h (no changes needed) | T-01 |
| View_foundational_test.cpp | T-06 |
| ViewGroup_foundational_test.cpp | T-08 |
| ViewParentMixin_test.cpp | T-07 |
| ViewManagerMixin_test.cpp | T-07 |
| Constitution Principle I (enum class, RAII, std::optional) | T-01, T-04, T-05 |
| Constitution Principle II (CRTP zero-cost) | T-02, T-03, T-04, T-05 |
| Constitution Principle III (TDD >80%) | T-06, T-07, T-08, T-09, T-10, T-11 |

### Coverage Gaps

**None identified.** All 53 functional requirements (FR-01 through FR-53) map to at least one task's acceptance criteria. All 19 user stories are covered.

**Note on focusSearch():** Per the plan's open question, `focusSearch()` is implemented as a stub returning nullptr. The test verifies the stub behavior. Full focus search algorithm is deferred to a follow-up feature.
