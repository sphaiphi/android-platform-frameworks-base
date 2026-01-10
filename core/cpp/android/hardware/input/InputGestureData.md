# InputGestureData - Reverse Engineering Documentation

## Executive Summary
`InputGestureData` is a high-level wrapper around `AidlInputGestureData`, representing a gesture configuration. It defines a "Trigger" (Key or Touchpad) and an "Action" (System Key Gesture or App Launch).

## Architecture Overview
- **Wrapper**: Wraps the AIDL generated class `AidlInputGestureData`.
- **Immutable**: Intended to be used as a value object.
- **Builder Pattern**: Uses a static `Builder` class for construction.

## Detailed Functionality

### Triggers
- **KeyTrigger**: Keycode + Modifier state.
- **TouchpadTrigger**: Gesture Type (e.g., 3-finger tap).
- **Factory**: Static `createKeyTrigger`, `createTouchpadTrigger`.

### Actions
- **System Action**: Defined by `mKeyGestureType` (int).
- **App Launch**: Defined by `AppLaunchData` (Category, Role, or Component).

### Validation
- Ensures triggers are present.
- Ensures actions are valid (either system action or app launch data).

## Data Model
- `AidlInputGestureData mInputGestureData`: The underlying data storage.

## API Reference
- `Trigger getTrigger()`
- `Action getAction()`
- `AidlInputGestureData getAidlData()` (internal use).

## Java-to-C++ Translation Guide
- **Union/Variant**: The `Trigger` concept maps well to `std::variant<KeyTrigger, TouchpadTrigger>`.
- **AIDL**: C++ AIDL backend will generate `AidlInputGestureData`. This class might be a convenience wrapper in C++ too, or C++ code might use the AIDL struct directly.

## Test Cases & Validation
- Build with missing trigger -> Exception.
- Build with Launch App action but no App Data -> Exception.
- Verify `AidlInputGestureData` is populated correctly from Builder.

## Implementation Risks
- `mInputGestureData` is mutable in AIDL; this wrapper tries to present an immutable view. Ensure C++ implementation respects immutability if desired.
