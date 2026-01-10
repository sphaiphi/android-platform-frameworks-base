# Light - Reverse Engineering Documentation

## Executive Summary
`Light` represents a logical light fixture on the device, such as the microphone light, camera light, or keyboard backlight. It is a `Parcelable` value object that holds immutable metadata about the light, including its ID, name, ordinal position, type, capabilities (brightness, RGB), and preferred brightness levels.

## Architecture Overview
- **Pattern**: Data Transfer Object (DTO) / Value Object.
- **Inheritance**: Implements `android.os.Parcelable`.
- **Role**: Describes the physical or logical properties of a light source, used by `LightsManager` to enumerate available lights.

## Detailed Functionality

### Core Properties
- **ID (`mId`)**: Unique integer identifier (opaque).
- **Name (`mName`)**: Human-readable name (e.g., "Light").
- **Ordinal (`mOrdinal`)**: Sort key for physical ordering (e.g., multiple LEDs in a row).
- **Type (`mType`)**: Categorization constant (e.g., Microphone, Camera, Input).
- **Capabilities (`mCapabilities`)**: Bitmask defining features (Brightness, RGB color).
- **Preferred Brightness Levels (`mPreferredBrightnessLevels`)**: Array of integers [0-255] for stepped controls (e.g., keyboard backlight keys).

### Constants (Light Types)
- `LIGHT_TYPE_MICROPHONE` (8)
- `LIGHT_TYPE_CAMERA` (9)
- `LIGHT_TYPE_INPUT` (10001)
- `LIGHT_TYPE_PLAYER_ID` (10002)
- `LIGHT_TYPE_KEYBOARD_BACKLIGHT` (10003)
- `LIGHT_TYPE_KEYBOARD_MIC_MUTE` (10004)
- `LIGHT_TYPE_KEYBOARD_VOLUME_MUTE` (10005)

### Constants (Capabilities)
- `LIGHT_CAPABILITY_BRIGHTNESS` (1)
- `LIGHT_CAPABILITY_COLOR_RGB` (2)

## Data Model
| Field | Type | Description |
|---|---|---|
| `mId` | `int` | Unique identifier. |
| `mName` | `String` | Descriptive name. |
| `mOrdinal` | `int` | Physical position sort key. |
| `mType` | `int` | Enum value (LightType). |
| `mCapabilities` | `int` | Bitmask (LightCapability). |
| `mPreferredBrightnessLevels` | `int[]` | Optional predefined brightness steps. |

## API Reference
- `getId()`: Returns ID.
- `getName()`: Returns Name.
- `getOrdinal()`: Returns Ordinal.
- `getType()`: Returns Type.
- `getCapabilities()`: Returns Capabilities bitmask.
- `hasBrightnessControl()`: Checks `LIGHT_CAPABILITY_BRIGHTNESS`.
- `hasRgbControl()`: Checks `LIGHT_CAPABILITY_COLOR_RGB`.
- `getPreferredBrightnessLevels()`: Returns `int[]` or null.

## Java-to-C++ Translation Guide

### Data Structure
Map directly to a C++ struct or class.
```cpp
struct Light {
    int32_t id;
    std::string name;
    int32_t ordinal;
    int32_t type;
    int32_t capabilities;
    std::vector<int32_t> preferredBrightnessLevels;
};
```

### Serialization
- This class is `Parcelable`. In C++, this corresponds to writing/reading from `android::Parcel`.
- **Write**: `writeInt32`, `writeString16` (UTF-16 usually in Binder), `writeInt32Array`.
- **Read**: `readInt32`, `readString16`, `readInt32Array`.

### Key Considerations
- `mPreferredBrightnessLevels` is nullable in Java, so `std::optional` or checking for empty vector is needed.
- `writeString` in Java writes UTF-16; C++ `Parcel::writeString16` should be used, or `writeUtf8AsUtf16`.

## Questions for C++ Team
- Should we use `std::string` (UTF-8) or `android::String16` for the name? (Standard practice is usually `String16` for Binder interoperability, converting to `std::string` for internal use).
