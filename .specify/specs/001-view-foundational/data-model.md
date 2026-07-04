# Data Model: Foundational View Classes

**Feature ID:** 001-view-foundational

---

## Entities

### View

| Field | Type | Constraints | Description |
|-------|------|-------------|-------------|
| id_ | int32_t | not null, default -1 | View identifier. NO_ID = -1. |
| tag_ | an arbitrary object | nullable, default empty | Arbitrary object associated with this view. |
| visibility_ | an enumerated type | not null, default Visible | VISIBLE=0, INVISIBLE=4, GONE=8. |
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
| flags_ | a bitmask | not null, default NONE | Bit flags (FOCUSABLE, CLICKABLE, LONG_CLICKABLE, ENABLED). |
| focused_ | bool | not null, default false | Whether this view currently has focus. |
| measured_ | bool | not null, default false | Whether measure() has been called. |
| layoutRequested_ | bool | not null, default false | Whether layout has been requested but not completed. |

**Indexes:** N/A (single View instance, no database).

**State machine:**


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
(Reclassified as a value type)

| Field | Type | Constraints | Description |
|-------|------|-------------|-------------|
| packed | uint32_t | not null | Packed mode + size. Mode occupies top 2 bits, size occupies bottom 30 bits. |

**Decomposition:**
- Mode:  (top 2 bits)
- Size:  (bottom 30 bits)

**Modes:**
- UNSPECIFIED = 
- EXACTLY = 
- AT_MOST = 

**Indexes:** N/A.

### ViewParentMixin (Mixin)

Provides methods for parent-child communication. See plan.md for method signatures.

### ViewManagerMixin (Mixin)

Provides methods for view container operations. See plan.md for method signatures.

---

## Relationships

- **ViewGroup** has many **View** via  (owned, shared_ptr).
- **ViewGroup** has many **TLayoutParams** via  (owned, shared_ptr, 1:1 with children_).
- **View** belongs to its parent via the CRTP parent chain (parent reference: non-owning pointer).
- **MarginLayoutParams** extends **LayoutParams** via public inheritance.
- **ViewGroup** publicly inherits **View** and privately inherits **ViewParentMixin<ViewGroup>** and **ViewManagerMixin<ViewGroup>** via CRTP.
- **View** privately inherits **ViewParentMixin<View>** and **ViewManagerMixin<View>** via CRTP.

---

## Enumerations

### Visibility

# 0 "<stdin>"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "<stdin>"
Implicit conversion to int for ABI compatibility with Java View constants.

### LayoutDirection

# 0 "<stdin>"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "<stdin>"

### ViewFlags (bit flags)

# 0 "<stdin>"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "<stdin>"
Uses  with underlying type . Bitwise operations via .

### ViewGroupFlags (bit flags)

# 0 "<stdin>"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "<stdin>"

### DescendantFocusability

# 0 "<stdin>"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "<stdin>"

---

## Data Flow


