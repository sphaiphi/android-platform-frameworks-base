# Keyboard - Reverse Engineering Documentation

## Executive Summary
`Keyboard` represents the data model of a virtual keyboard layout. It parses an XML file to build a structure of Rows and Keys. It handles grid-based proximity calculations for touch hit testing. **Deprecated**.

## Architecture Overview
*   **Components**:
    *   `Row`: Horizontal container of keys.
    *   `Key`: Individual key properties (code, label, icon, geometry).

## Detailed Functionality

### Parsing (`loadKeyboard`)
*   Parses XML tags: `Keyboard`, `Row`, `Key`.
*   Calculates `x`, `y`, `width`, `height` based on display metrics and percentages.
*   Handles attributes like `horizontalGap`, `verticalGap`, `keyWidth`.

### Proximity (`computeNearestNeighbors`)
*   **Grid**: Divides keyboard into a grid (default 10x5).
*   **Mapping**: Maps each grid cell to a list of keys overlapping or close to it.
*   **`getNearestKeys(x, y)`**: Returns indices of keys near the point. Used by `KeyboardView` for touch processing.

## Data Model
*   `mKeys`: List of all `Key` objects.
*   `mTotalWidth`, `mTotalHeight`: Calculated dimensions.
*   `mModifierKeys`: Shift, Alt keys.

## Java-to-C++ Translation Guide
*   **XML Parsing**: Need an XML parser (e.g., `libxml2` or Android's `XmlPullParser` equivalent in native).
*   **Geometry**: Simple 2D geometry calculations.

## Implementation Risks
*   **Legacy**: This class is deprecated. Reimplementing it might be unnecessary if the goal is modern Android (which recommends custom views), but if legacy support is needed, the grid logic is the most complex part.
