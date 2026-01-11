# ScrollBarDrawable - Reverse Engineering Documentation

## Executive Summary
`ScrollBarDrawable` is a composite `Drawable` implementation primarily used by `android.view.View` to render scrollbars. It manages four distinct visual components: vertical track, vertical thumb, horizontal track, and horizontal thumb. It determines which components to draw and calculates their dimensions and positions based on scroll parameters (range, offset, extent) provided by the host View.

## Architecture Overview
- **Inheritance**: Inherits from `android.graphics.drawable.Drawable`.
- **Interfaces**: Implements `android.graphics.drawable.Drawable.Callback`.
- **Role**: Composite Drawable / Decorator. It holds references to other Drawables and delegates drawing and state management to them.
- **Key Relationships**:
  - Used by `android.view.View`.
  - Delegates geometric calculations to `com.android.internal.widget.ScrollBarUtils`.
  - Manages child Drawables (`Track` and `Thumb` for both axes).

## Detailed Functionality

### Drawing Logic (`draw`)
**Purpose**: Renders the scrollbar track and thumb onto the provided Canvas.
**Algorithm**:
1.  **State Evaluation**:
    - Retreives `vertical`, `extent`, and `range` state.
    - Determines if the track and thumb should be drawn.
    - **Rule**: If `extent <= 0` or `range <= extent` (content fits in view), the thumb is *not* drawn. The track is drawn only if `mAlwaysDrawVerticalTrack` (or Horizontal equivalent) is true.
2.  **Clipping Optimization**:
    - calls `canvas.quickReject` with the drawable's bounds. Returns immediately if the scrollbar is outside the clipping region.
3.  **Draw Track**:
    - Selects the appropriate drawable (`mVerticalTrack` or `mHorizontalTrack`).
    - If `mBoundsChanged` is true, updates the track's bounds to match the `ScrollBarDrawable`'s bounds.
    - Calls `track.draw(canvas)`.
4.  **Draw Thumb**:
    - Selects the appropriate drawable (`mVerticalThumb` or `mHorizontalThumb`).
    - Calculates geometry:
        - `scrollBarLength`: Height of bounds (vertical) or Width of bounds (horizontal).
        - `thickness`: Width of bounds (vertical) or Height of bounds (horizontal).
    - **Math Delegation**: Calls `ScrollBarUtils.getThumbLength` and `ScrollBarUtils.getThumbOffset` to compute the thumb's dimension and position relative to the track.
    - Updates the thumb's bounds:
        - **Vertical**: `Rect(left, top + offset, right, top + offset + length)`
        - **Horizontal**: `Rect(left + offset, top, left + offset + length, bottom)`
    - Calls `thumb.draw(canvas)`.

### State & Parameter Management
- **`setParameters`**: The core update mechanism. Accepts `range`, `offset`, `extent`, and `vertical` (orientation).
    - Detects changes to `vertical` -> sets `mBoundsChanged`.
    - Detects changes to scroll metrics -> sets `mRangeChanged`.
- **`onBoundsChange`**: Overridden to set `mBoundsChanged = true`. This ensures child drawables are re-laid out when the parent bounds change.
- **`mutate`**: Implements deep copy semantics. If `mutate()` is called, it calls `mutate()` on all valid child drawables.

### Property Propagation
The class acts as a proxy for standard Drawable properties, propagating them to all four children:
- **State**: `onStateChange` propagates `int[] state` (e.g., pressed, focused).
- **Alpha**: `setAlpha` applies the alpha value to all children.
- **ColorFilter**: `setColorFilter` applies the filter to all children.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mVerticalTrack` | `Drawable` | Background for vertical scrollbar. Nullable. |
| `mHorizontalTrack` | `Drawable` | Background for horizontal scrollbar. Nullable. |
| `mVerticalThumb` | `Drawable` | Moving indicator for vertical scrollbar. Nullable. |
| `mHorizontalThumb` | `Drawable` | Moving indicator for horizontal scrollbar. Nullable. |
| `mRange` | `int` | Total scrollable content range. |
| `mOffset` | `int` | Current scroll position. |
| `mExtent` | `int` | Visible viewport size. |
| `mVertical` | `boolean` | `true` for vertical mode, `false` for horizontal. |
| `mBoundsChanged` | `boolean` | Dirty flag for track bounds layout. |
| `mRangeChanged` | `boolean` | Dirty flag for thumb geometry calculation. |

## API Reference

### Configuration
- `setParameters(int range, int offset, int extent, boolean vertical)`: Updates scroll state.
- `setAlwaysDrawHorizontalTrack(boolean)`: Forces horizontal track visibility even when not scrolling.
- `setAlwaysDrawVerticalTrack(boolean)`: Forces vertical track visibility even when not scrolling.

### Child Management
- `setVerticalThumbDrawable(Drawable)`, `setVerticalTrackDrawable(Drawable)`, etc.
    - **Behavior**:
        1.  Unsets callback on the old drawable.
        2.  Calls `propagateCurrentState` on the new drawable (mutates if needed, sets state, callback, alpha, color filter).
        3.  Stores the new drawable.

### Geometry
- `getSize(boolean vertical)`: Returns the intrinsic width (if vertical) or height (if horizontal) of the track or thumb. This is used by the View to determine how much space to reserve for the scrollbar.

## Java-to-C++ Translation Guide

### Memory Management
- **Smart Pointers**: Use `std::unique_ptr<Drawable>` (or the project's equivalent RefBase/sp) for `mVerticalTrack`, `mHorizontalTrack`, etc.
- **Callbacks**: The C++ implementation needs a `WeakReference` or equivalent mechanism if mimicking the Java `Drawable.Callback` pattern to avoid reference cycles, although `ScrollBarDrawable` seems to own these children strictly.

### Helper Implementation
- **ScrollBarUtils**: The method calls `ScrollBarUtils.getThumbLength` and `getThumbOffset` are critical.
    - *Requirement*: Ensure the logic from `com.android.internal.widget.ScrollBarUtils` is ported or available.
    - *Logic approximation*:
        - `ThumbLength = ScrollBarLength * Extent / Range` (typically with a minimum length constraint).
        - `ThumbOffset = (ScrollBarLength - ThumbLength) * Offset / (Range - Extent)`.

### Drawing Translation
- `Canvas.quickReject`: Map to `SkCanvas::quickReject` or equivalent.
- `Drawable.setBounds`: Map to setting the geometry on the C++ RenderNode or Drawable object.

### Dirty Flags
- The usage of `mBoundsChanged` and `mRangeChanged` allows for lazy re-computation of bounds during the `draw` phase. This pattern should be preserved to avoid unnecessary recalculations during layout passes if the scrollbar isn't visible.

## Implementation Risks
- **Null Checks**: Java code heavily relies on `!= null` checks for the tracks and thumbs. The C++ code must enforce this strictly to avoid segfaults.
- **Integer Arithmetic**: Watch out for integer division behavior and potential overflows if `range` is extremely large, though `int` in Java is 32-bit signed, same as `int32_t`.
- **State Synchronization**: When a new Drawable is set (e.g., `setVerticalThumbDrawable`), it *must* inherit the current state (Alpha, ColorFilter, StateSet) of the `ScrollBarDrawable`. Failing to do this will result in visual bugs where the scrollbar looks correct initially but doesn't react to changes until the next full update.