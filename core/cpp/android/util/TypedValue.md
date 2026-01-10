# TypedValue - Reverse Engineering Documentation

## Executive Summary
Container for a dynamically typed data value, primarily used for Resource values (dimensions, floats, colors, strings).

## Data Model
*   **`type`**: Integer constant (TYPE_STRING, TYPE_FLOAT, TYPE_DIMENSION, etc.).
*   **`data`**: Raw integer data. Interpretation depends on type.
    *   Float: `Float.floatToIntBits`.
    *   Color: ARGB.
    *   Dimension/Fraction: Complex encoding (unit + mantissa + radix).
*   **`string`**: CharSequence value.
*   **`resourceId`**: Originating resource ID.

## Key Algorithms
*   **Complex Dimension Encoding**:
    *   Format: `(mantissa << 8) | (radix << 4) | unit`.
    *   `applyDimension`: Converts complex unit (dp, sp, pt, in, mm) to pixels using `DisplayMetrics`.
    *   `complexToFloat`: Decodes the fixed-point mantissa/radix to a float.

## Java-to-C++ Translation Guide
*   **Struct**: This is essentially a `tagged union` or `std::variant`.
*   **Units**: Logic for unit conversion (dp to px) is essential for UI layout.

## Implementation Risks
*   **Precision**: The custom fixed-point encoding for dimensions has limited precision.
