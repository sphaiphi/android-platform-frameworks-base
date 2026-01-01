# PhysicalKeyLayout - Reverse Engineering Documentation

## Executive Summary
`PhysicalKeyLayout` models the physical arrangement of keys on a keyboard. It acts as a data provider for `KeyboardLayoutPreviewDrawable`, mapping abstract Scan Codes to Key Codes and Glyphs based on a `KeyCharacterMap`.

## Architecture Overview
- **Mapping**: Static mapping of `SCANCODE` constants to `KeyEvent.KEYCODE_*`.
- **Layout Definitions**: Hardcoded layouts for `ANSI`, `ISO`, and `JIS`.
- **Key Objects**: `LayoutKey` record (keycode, scancode, weight, glyph).

## Detailed Functionality

### Scancodes
- Defines constants for USB HID Usage IDs (approximated as ScanCodes) for standard keys.

### Layout Creation (`initLayoutKeys`)
- Uses `KeyboardLayout` properties (`isAnsi`, `isJis`) to decide structure.
- **ANSI**: Standard US layout (Horizontal Enter).
- **ISO**: European style (Vertical/L-shaped Enter, extra key next to Left Shift).
- **JIS**: Japanese layout (Big Enter, small Space, extra keys).

### Key Population
- Iterates the hardcoded 2D array structure.
- Queries `KeyCharacterMap` to see what character is produced by each key.
- Creates `KeyGlyph` objects containing the printed characters (Base, Shift, AltGr states).

## Data Model
- `LayoutKey[][] mKeys`: Rows of keys.
- `EnterKey mEnterKey`: Metadata for special Enter key shaping.

## Java-to-C++ Translation Guide
- **Logic**: The logic for building the 2D array of keys is procedural and can be translated to C++.
- **KeyCharacterMap**: C++ has access to `KeyCharacterMap` (native).
- **UI Data**: This class primarily prepares data for UI rendering.

## Implementation Risks
- Hardcoded layouts might need updates for new physical form factors.
