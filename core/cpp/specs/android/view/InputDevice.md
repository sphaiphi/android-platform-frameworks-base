# InputDevice - Reverse Engineering Documentation

## Executive Summary
`InputDevice` describes the capabilities, sources, and characteristics of a physical or virtual input peripheral (Keyboard, Mouse, Touchscreen, Joystick, etc.). It provides metadata like the device name, vendor/product IDs, and the specific "Motion Ranges" (axes) it supports.

## Data Model

### 1. Device Identity
*   **`id`**: `int` - A unique ID assigned at runtime.
*   **`descriptor`**: `String` - A persistent, stable identifier across reboots.
*   **`vendorId` / `productId`**: Hardware-specific identifiers.

### 2. Input Sources
*   **`SOURCE_CLASS_*`**: Broad categories (Button, Pointer, Joystick).
*   **`SOURCE_*`**: Specific types (Keyboard, Touchscreen, Rotary Encoder).

### 3. Motion Ranges
*   Defines the min, max, resolution, and fuzz for various axes (X, Y, Pressure, Tilt).

## Detailed Functionality

### 1. Service Integration
*   **`getVibratorManager()`**: Accesses the vibration hardware on the device.
*   **`getSensorManager()`**: Accesses specialized sensors (like accelerometers) built into the input device.

### 2. Keyboard Support
*   **`getKeyCharacterMap()`**: Provides the mapping between key codes and Unicode characters.

## Java-to-C++ Translation Guide
*   **Mapping**: Map to a C++ `class InputDevice` wrapping the native `InputDeviceInfo`.
*   **Parceling**: Serialization must match `frameworks/native/libs/input/Input.cpp`.

## Implementation Risks
*   **Stale Data**: Devices can be reconfigured or disconnected. Apps should listen for `InputManager` callbacks rather than caching `InputDevice` objects long-term.
*   **Virtual Devices**: IDs less than 0 represent virtual devices; logic should handle these as special cases (e.g., the virtual keyboard).
