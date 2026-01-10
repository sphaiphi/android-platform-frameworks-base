# PointerIcon - Reverse Engineering Documentation

## Executive Summary
`PointerIcon` represents the visual appearance of a mouse or stylus pointer. It supports standard system types (Arrow, Hand, Crosshair), custom bitmaps, and vector-based icons. It also handles animated icons by maintaining an array of bitmaps and a frame duration.

## Architecture Overview
*   **Role**: Mouse/Stylus cursor descriptor.
*   **Types**: Defines a wide range of standard types like `TYPE_ARROW`, `TYPE_TEXT`, `TYPE_HAND`, and `TYPE_HANDWRITING`.
*   **JNI Centric**: Custom icons are marshalled to native code for rendering by the hardware compositor.

## Detailed Functionality

### 1. System Icons
*   **`getSystemIcon()`**: Returns a shared instance of a standard system pointer.
*   **`getLoadedSystemIcon()`**: Resolves the system type into a theme-specific resource.

### 2. Custom Icons
*   **`create(Bitmap, x, y)`**: Creates an icon from a bitmap with a defined "hotspot" (the active pixel coordinate).
*   **`load(Resources, resId)`**: Parses an XML-based `<pointer-icon>` resource.

### 3. Vector and Animation
*   Supports `AnimationDrawable` for cursors that change over time (e.g., the 'Wait' spinner).
*   Can generate bitmaps from `VectorDrawable` at different scales.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `android::PointerIcon`.
*   **Parceling**: Serialization must match the native implementation in `frameworks/native/libs/input/`.
*   **Bitmap Handling**: C++ implementation must correctly extract raw pixel data from `android::Bitmap`.

## Implementation Risks
*   **Hotspot Validation**: The hotspot coordinates must be within the bitmap bounds to avoid native-side clipping or crashes.
*   **Resource Management**: Caching system icons is essential to prevent repeated theme lookups and resource loading on every input event.
