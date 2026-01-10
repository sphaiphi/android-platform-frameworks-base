# View - Reverse Engineering Documentation

## Executive Summary
`View` is the fundamental building block of the Android UI. It occupies a rectangular area on the screen and is responsible for drawing itself and handling events (touch, key, focus). All UI components (widgets) and containers (layouts) inherit from this class.

## Architecture Overview
*   **Base Class**: Root of the UI hierarchy (except for `ViewParent` which is an interface).
*   **Coordinate System**: Uses a pixel-based coordinate system relative to the parent.
*   **Threading**: Must be accessed only from the UI thread (Main Thread).
*   **Key Dependencies**:
    *   `Context`: Provides access to resources and system services.
    *   `AttachInfo`: Shared state among all views in a window (managed by `ViewRootImpl`).
    *   `RenderNode`: Hardware-accelerated rendering component.
    *   `LayoutParams`: Metadata used by the parent `ViewGroup` to decide size and position.

## Detailed Functionality

### 1. Life Cycle
*   **Attachment**: `onAttachedToWindow()` and `onDetachedFromWindow()`.
*   **Visibility**: `onVisibilityChanged()`, `onWindowVisibilityChanged()`.
*   **Focus**: `onFocusChanged()`, `onWindowFocusChanged()`.

### 2. Measurement (The "Measure" Pass)
*   **Method**: `measure(int widthMeasureSpec, int heightMeasureSpec)` -> `onMeasure()`.
*   **Contract**: Subclasses must call `setMeasuredDimension()`.
*   **MeasureSpec**: A 32-bit integer combining mode (EXACTLY, AT_MOST, UNSPECIFIED) and size.
*   **Suggested Min Size**: `getSuggestedMinimumWidth/Height()` (max of `minWidth/Height` and background size).

### 3. Layout (The "Layout" Pass)
*   **Method**: `layout(int l, int t, int r, int b)` -> `onLayout()`.
*   **Frame Assignment**: `setFrame()` sets the actual coordinates (`mLeft`, `mTop`, `mRight`, `mBottom`) and updates the `RenderNode`.

### 4. Drawing (The "Draw" Pass)
*   **Method**: `draw(Canvas)` -> `onDraw(Canvas)`.
*   **Steps**:
    1.  Draw background.
    2.  Save layers (for fading edges).
    3.  `onDraw()`: Draw view content.
    4.  `dispatchDraw()`: Draw children (if `ViewGroup`).
    5.  Draw fading edges and restore layers.
    6.  Draw decorations (scrollbars, foreground).
*   **Invalidation**: `invalidate()` marks the view as "dirty" and schedules a new traversal.

### 5. Event Handling
*   **Touch**: `onTouchEvent(MotionEvent)`, `dispatchTouchEvent()`.
*   **Keys**: `onKeyDown()`, `onKeyUp()`, `dispatchKeyEvent()`.
*   **Focus**: `requestFocus()`, `clearFocus()`.

## Data Model (Internal State)
*   `mPrivateFlags`: Bitmask for internal state (DIRTY, MEASURED, LAYOUT_REQUIRED).
*   `mViewFlags`: Bitmask for public flags (VISIBILITY, FOCUSABLE, CLICKABLE).
*   `mRenderNode`: The native rendering object used by the hardware-accelerated pipeline.

## Java-to-C++ Translation Guide
*   **Threading**: Use a single-threaded message loop for the UI thread.
*   **Rendering**: Map `Canvas` operations to a C++ rendering library (e.g., Skia or a custom OpenGL/Vulkan wrapper).
*   **Bitmasks**: Heavy use of `mPrivateFlags` should be mapped to `std::bitset` or clear enum-based flags for type safety.
*   **Object Lifecycle**: Use `std::shared_ptr` for view hierarchies, but be careful of circular references (Views hold parents, parents hold children).

## Implementation Risks
*   **Performance**: Deep view hierarchies lead to exponential complexity in measurement and layout.
*   **Memory**: Each view is a heavy object. Custom views with large bitmaps or complex `RenderNode` structures can cause OOM.
*   **Recursive Loops**: `requestLayout()` inside `onLayout()` or `onMeasure()` will cause an infinite loop or crash.