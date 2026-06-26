# Data Model: Foundational View Classes

**Feature ID:** 001-view-foundational

---

## Entities

### View

| Field | Type | Constraints | Description |
|-------|------|-------------|-------------|
| id_ | int32_t | not null, default -1 | View identifier. NO_ID = -1. |
| tag_ | std::any | nullable, default empty | Arbitrary object associated with this view. |
| visibility_ | enum class Visibility : int | not null, default Visible | VISIBLE=0, INVISIBLE=4, GONE=8. Implicit int conversion for ABI. |
| alpha_ | float | not null, default 1.0f | Transparency, range [0.0, 1.0]. |
| rotationX_ | float | not null, default 0.0f | Rotation around X axis in degrees. |
| rotationY_ | float | not null, default 0.0f | Rotation around Y axis in degrees. |
| rotationZ_ | float | not null, default 0.0f | Rotation around Z axis in degrees. |
| scaleX_ | float | not null, default 1.0f | Scale factor on X axis. |
| scaleY_ | float | not null, default 1.0f | Scale factor on Y axis. |
| translationX_ | float | not null, default 0.0f | Offset from layout position in pixels (X). |
| translationY_ | float | not null, default 0.0f | Offset from layout position in pixels (Y). |
| paddingLeft_ | int32_t | not null, default 0 | Left padding in pixels. |
| paddingTop_ | int32_t | not null, default 0 | Top padding in pixels. |
| paddingRight_ | int32_t | not null, default 0 | Right padding in pixels. |
| paddingBottom_ | int32_t | not null, default 0 | Bottom padding in pixels. |
| minWidth_ | int32_t | not null, default 0 | Minimum width in pixels. |
| minHeight_ | int32_t | not null, default 0 | Minimum height in pixels. |
| measuredWidth_ | int32_t | not null, default 0 | Measured width from last measure pass. |
| measuredHeight_ | int32_t | not null, default 0 | Measured height from last measure pass. |
| left_ | int32_t | not null, default 0 | Left coordinate after last layout pass. |
| top_ | int32_t | not null, default 0 | Top coordinate after last layout pass. |
| right_ | int32_t | not null, default 0 | Right coordinate after last layout pass. |
| bottom_ | int32_t | not null, default 0 | Bottom coordinate after last layout pass. |
| layoutDirection_ | enum class LayoutDirection : int | not null, default Ltr | LTR or RTL layout direction. |
| flags_ | enum class ViewFlags : uint32_t | not null, default ViewFlags::NONE | Bit flags (FOCUSABLE, CLICKABLE, LONG_CLICKABLE, ENABLED). |
| focused_ | bool | not null, default false | Whether this view currently has focus. |
| measured_ | bool | not null, default false | Whether measure() has been called. |
| layoutRequested_ | bool | not null, default false | Whether layout has been requested but not completed. |

**Indexes:** N/A (single View instance, no database).

**State machine:**
```
[unmeasured] --measure()--> [measured]
[unlaid-out] --layout()-->  [laid-out]
[not-drawn]  --draw()-->    [drawn]
[visible] --setVisibility(GONE)--> [gone]
[gone] --setVisibility(VISIBLE/INVISIBLE)--> [visible]
```

### ViewGroup (extends View)

| Field | Type | Constraints | Description |
|-------|------|-------------|-------------|
| children_ | std::vector<std::shared_ptr<View>> | not null, default empty | Ordered list of direct child views (z-order: back-to-front). |
| childParams_ | std::vector<std::shared_ptr<TLayoutParams>> | not null, default empty | Per-child LayoutParams, aligned 1:1 with children_. |
| touchTarget_ | View* | nullable, default nullptr | The view that received the current ACTION_DOWN gesture. |
| groupFlags_ | enum class ViewGroupFlags : uint32_t | not null, default all set | FLAG_CLIP_CHILDREN (bit 0), FLAG_CLIP_TO_PADDING (bit 1). |
| descendantFocusability_ | enum class DescendantFocusability : int | not null, default FOCUS_BEFORE_DESCENDANTS | How ViewGroup handles focus vs. descendants. |
| disallowIntercept_ | bool | not null, default false | Whether children have requested no touch intercept. |
| touchIntercepted_ | bool | not null, default false | Whether the ViewGroup has intercepted the current gesture. |

**Indexes:** N/A.

### LayoutParams

| Field | Type | Constraints | Description |
|-------|------|-------------|-------------|
| width | int32_t | not null | Layout width: exact px value, MATCH_PARENT (-1), or WRAP_CONTENT (-2). |
| height | int32_t | not null | Layout height: exact px value, MATCH_PARENT (-1), or WRAP_CONTENT (-2). |

**Indexes:** N/A.

### MarginLayoutParams (extends LayoutParams)

| Field | Type | Constraints | Description |
|-------|------|-------------|-------------|
| left_margin | int32_t | not null, default 0 | Left margin in pixels. |
| top_margin | int32_t | not null, default 0 | Top margin in pixels. |
| right_margin | int32_t | not null, default 0 | Right margin in pixels. |
| bottom_margin | int32_t | not null, default 0 | Bottom margin in pixels. |

**Indexes:** N/A.

### MeasureSpec

| Field | Type | Constraints | Description |
|-------|------|-------------|-------------|
| packed | uint32_t | not null | Packed mode + size. Mode occupies top 2 bits, size occupies bottom 30 bits. |

**Decomposition:**
- Mode: `packed & 0xC0000000` (top 2 bits)
- Size: `packed & 0x3FFFFFFF` (bottom 30 bits)

**Modes:**
- UNSPECIFIED = `0x00000000`
- EXACTLY = `0x40000000`
- AT_MOST = `0x80000000`

**Indexes:** N/A.

### ViewParentMixin<Derived> (CRTP base)

No state. Provides methods for parent-child communication. See plan.md for method signatures.

### ViewManagerMixin<Derived> (CRTP base)

No state. Provides methods for view container operations. See plan.md for method signatures.

---

## Relationships

- **ViewGroup** has many **View** via `children_` (owned, shared_ptr).
- **ViewGroup** has many **TLayoutParams** via `childParams_` (owned, shared_ptr, 1:1 with children_).
- **View** belongs to **ViewGroup** (or other ViewParent) via CRTP parent chain.
- **MarginLayoutParams** extends **LayoutParams** via public inheritance.
- **ViewGroup** publicly inherits **View** and privately inherits **ViewParentMixin<ViewGroup>** and **ViewManagerMixin<ViewGroup>** via CRTP.
- **View** privately inherits **ViewParentMixin<View>** and **ViewManagerMixin<View>** via CRTP.

---

## Enumerations

### Visibility

```cpp
enum class Visibility : int {
    Visible = 0,
    Invisible = 4,
    Gone = 8
};
```
Implicit conversion to int for ABI compatibility with Java View constants.

### LayoutDirection

```cpp
enum class LayoutDirection : int {
    Ltr = 0,
    Rtl = 1
};
```

### ViewFlags (bit flags)

```cpp
enum class ViewFlags : uint32_t {
    NONE        = 0x00000000,
    FOCUSABLE   = 0x00000001,
    CLICKABLE   = 0x00000002,
    LONG_CLICKABLE = 0x00000004,
    ENABLED     = 0x00000008
};
```
Uses `enum class` with underlying type `uint32_t`. Bitwise operations via `std::underlying_type_t`.

### ViewGroupFlags (bit flags)

```cpp
enum class ViewGroupFlags : uint32_t {
    CLIP_CHILDREN    = 0x00000001,
    CLIP_TO_PADDING  = 0x00000002
};
```

### DescendantFocusability

```cpp
enum class DescendantFocusability : int {
    FOCUS_BEFORE_DESCENDANTS  = 0,
    FOCUS_AFTER_DESCENDANTS   = 1,
    FOCUS_BLOCK_DESCENDANTS   = 2
};
```

---

## Data Flow

```
Context --> View (construction)
Context --> ViewGroup (construction)

ViewGroup::addView(View, LayoutParams)
    --> assigns LayoutParams to child
    --> sets child's parent via CRTP
    --> triggers requestLayout()

ViewGroup::measure()
    --> iterates children_
    --> computes MeasureSpec per child from childParams_
    --> calls child->measure(spec)

ViewGroup::layout()
    --> computes left/top/right/bottom per child from LayoutParams + margins
    --> calls child->layout(l, t, r, b)

ViewGroup::draw()
    --> draws background
    --> iterates children_ in z-order
    --> calls child->draw(canvas) for each visible child
    --> draws foreground
```
