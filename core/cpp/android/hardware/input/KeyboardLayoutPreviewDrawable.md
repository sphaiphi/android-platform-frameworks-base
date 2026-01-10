# KeyboardLayoutPreviewDrawable - Reverse Engineering Documentation

## Executive Summary
`KeyboardLayoutPreviewDrawable` is a UI class that dynamically draws a visual representation of a physical keyboard layout based on a provided `PhysicalKeyLayout`.

## Architecture Overview
- **Extends Drawable**: Custom drawing logic on `Canvas`.
- **Dynamic Layout**: Calculates key positions and sizes based on `PhysicalKeyLayout` data (rows, weights).
- **ResourceProvider**: Inner class to manage Paints, Colors, and Dimensions based on Context/Theme.

## Detailed Functionality

### Layout Calculation (`onBoundsChange`)
- Iterates rows and keys from `PhysicalKeyLayout`.
- Calculates `keyWidth` based on total weight of the row.
- Handles "ISO Enter Key" specifically (shapes it as a polygon).
- Creates `KeyDrawable` objects (rectangles/shapes) for each key.

### Drawing (`draw`)
- Draws background (rounded rect).
- Iterates `mKeyDrawables` and calls `draw()`.
- Draws glyphs (text) on keys:
  - Base text (bottom-left).
  - Shift text (top-left).
  - AltGr text (bottom-right).

### Key Types
- **TypingKey**: Standard key.
- **UnsureTypingKey**: Standard key but greyed out (e.g., localized keys that might vary).
- **IsoEnterKey**: Custom path for the L-shaped Enter key.

## Data Model
- `List<KeyDrawable> mKeyDrawables`
- `PhysicalKeyLayout mKeyLayout`

## Java-to-C++ Translation Guide
- **UI Logic**: This is purely a UI class using Android Graphics (`Canvas`, `Paint`, `Path`). Direct C++ translation is only relevant if using a native UI toolkit (like Skia directly). Usually, this remains in Java/Kotlin.

## Implementation Risks
- Complex text measuring and positioning logic.
- RTL layout handling (though physical keyboards are LTR).
