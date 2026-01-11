# LightState - Reverse Engineering Documentation

## Executive Summary
`LightState` represents the visual state of a light, specifically its color (ARGB) and optionally a Player ID (for game controllers). It is immutable and `Parcelable`.

## Architecture Overview
- **Pattern**: Value Object / DTO.
- **Inheritance**: Implements `android.os.Parcelable`.

## Detailed Functionality
- **Color**: Stored as an `int` (ARGB). Alpha channel is ignored by some implementations but stored.
- **Player ID**: Integer, only relevant if the light type is `LIGHT_TYPE_PLAYER_ID`.

## Data Model
| Field | Type | Description |
|---|---|---|
| `mColor` | `int` | ARGB color value. |
| `mPlayerId` | `int` | Player ID index (if applicable). |

## API Reference
- `getColor()`
- `getPlayerId()`
- Builder class provided for construction.

## Java-to-C++ Translation Guide

### Data Structure
```cpp
struct LightState {
    int32_t color;
    int32_t playerId;
};
```

### Serialization
- **Parceling**: Writes/Reads two integers.
  - `dest.writeInt(mColor)`
  - `dest.writeInt(mPlayerId)`

### Notes
- "Color" handling: Ensure C++ code understands the ARGB packing (0xAARRGGBB).

## Questions for C++ Team
- None.
