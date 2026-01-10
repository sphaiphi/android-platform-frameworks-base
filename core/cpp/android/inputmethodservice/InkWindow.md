# InkWindow - Reverse Engineering Documentation

## Executive Summary
`InkWindow` is a transparent, overlay window (`TYPE_INPUT_METHOD`) used to draw stylus handwriting ink trails. It ensures the user sees their writing immediately before the text is recognized and committed to the editor.

## Architecture Overview
*   **Inheritance**: `PhoneWindow` -> `InkWindow`.
*   **Role**: Presentation layer for Handwriting.

## Detailed Functionality

### Setup
*   **Window Type**: `TYPE_INPUT_METHOD`.
*   **Flags**: `FLAG_LAYOUT_IN_SCREEN`, `FLAG_LAYOUT_NO_LIMITS`, `FLAG_NOT_TOUCHABLE`, `FLAG_NOT_FOCUSABLE`. It acts as a visual overlay that lets touches pass through (mostly, see below).
*   **Token**: Must attach to the IME window token.

### Visibility
*   `show()` / `hide()`: Manages `DecorView` visibility and adding/removing from `WindowManager`.
*   `initOnly()`: Adds window but keeps invisible.

### Ink View Management
*   **`setContentView`**: Sets the `mInkView` (the view responsible for drawing strokes).
*   **Visibility Listener**: Uses `ViewTreeObserver.OnGlobalLayoutListener` to detect when the ink view actually becomes visible to synchronize events.

### Input Dispatch
*   **`dispatchHandwritingEvent`**: Enqueues motion events directly into the `ViewRootImpl` of the InkWindow to drive the drawing.

## Data Model
*   `mWindowManager`: System service.
*   `mInkView`: The drawing view.
*   `mIsViewAdded`: Track `addView` status.

## Java-to-C++ Translation Guide
*   **Windowing**: In native code, this involves creating a `SurfaceControl` or using `WindowManager` via JNI/Binder. `PhoneWindow` is a high-level Java abstraction. Native equivalent is likely direct Surface manipulation or using a native windowing library.
*   **Input**: Injecting events into a window's input channel is key.

## Implementation Risks
*   **Surface Z-Ordering**: Must be correctly layered relative to the IME and the app.
*   **Latency**: The entire purpose is low-latency inking. Overhead must be minimized.
