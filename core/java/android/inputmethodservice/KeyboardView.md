# KeyboardView - Reverse Engineering Documentation

## Executive Summary
`KeyboardView` is a View that renders a `Keyboard` object and handles touch events. It draws keys, labels, icons, and handles key press logic (detection, repeat, popup preview, mini-keyboard). **Deprecated**.

## Architecture Overview
*   **Inheritance**: `View` -> `KeyboardView`.
*   **Input**: `Keyboard` object.
*   **Output**: `OnKeyboardActionListener` callbacks.

## Detailed Functionality

### Rendering (`onDraw`)
*   **Buffering**: Draws to an offscreen `Bitmap` (`mBuffer`) for performance.
*   **Logic**:
    *   Iterates all keys.
    *   Sets state (pressed/normal) on `mKeyBackground` drawable.
    *   Draws background.
    *   Draws label (text) or icon.
    *   Handles shadow.

### Touch Handling (`onTouchEvent`)
*   **Multi-touch**: rudimentary support (tracks pointer count).
*   **Hit Testing**: Uses `Keyboard.getNearestKeys` and distance calculation (`squaredDistanceFrom`).
*   **Actions**:
    *   `ACTION_DOWN`: Detect key, show preview, start repeat timer, start long-press timer.
    *   `ACTION_MOVE`: Update key focus, update preview. Swipe detection (`SwipeTracker`).
    *   `ACTION_UP`: Fire `onKey`, hide preview.

### Popup Preview
*   **`showKey`**: Uses a `PopupWindow` to show a magnified key image above the finger.

## Data Model
*   `mKeyboard`: The model.
*   `mCurrentKey`: Currently pressed key index.
*   `mHandler`: For repeat/long-press timing.

## Java-to-C++ Translation Guide
*   **Rendering**: `Canvas` operations map to 2D graphics API (Skia).
*   **Events**: Standard touch event loop.
*   **Timers**: Need a mechanism for delayed tasks (repeat key).

## Implementation Risks
*   **Performance**: Drawing all keys on every invalidate is slow. The bitmap buffer strategy is essential.
