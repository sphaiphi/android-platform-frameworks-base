# KeyGlyphMap - Reverse Engineering Documentation

## Executive Summary
`KeyGlyphMap` maps physical keys (keycodes) and modifiers to graphical glyphs (drawables) and hardware shortcuts. It allows the system to display accurate on-screen hints for specific physical keyboards.

## Architecture Overview
- **Parcelable**: Transferred from system service to clients.
- **Resource Loading**: Uses `PackageManager` and `Resources` to load Drawables based on resource IDs stored in `SparseIntArray`.

## Detailed Functionality

### Data Storage
- `mComponentName`: The app/service providing the map.
- `mKeyGlyphs`: Mapping KeyCode -> Resource ID.
- `mModifierGlyphs`: Mapping ModifierState -> Resource ID.
- `mHardwareShortcuts`: Mapping `KeyCombination` -> KeyCode (Remapping).

### Glyph Retrieval
- **getDrawableForKeycode**: Looks up resource ID and loads Drawable.
- **getDrawableForModifier**: Logic to map modifier keys to specific "ON" states and fetch drawable.

## Data Model
- `SparseIntArray` for efficient int->int mapping.
- `Map<KeyCombination, Integer>` for shortcuts.

## API Reference
- `Drawable getDrawableForKeycode(Context, int)`
- `Drawable getDrawableForModifier(Context, int)`

## Java-to-C++ Translation Guide
- **Drawables**: C++ layer cannot easily load Android Drawables. This class is primarily for the UI layer (Java). If C++ needs this, it would likely just handle the Resource IDs, not the Drawable objects.
- **Parceling**: `SparseIntArray` -> `std::map<int, int>` or vector of pairs.

## Implementation Risks
- Resource ID validity across processes (requires same package context).
