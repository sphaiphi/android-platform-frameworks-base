# android.graphics.Rect - Reverse Engineering Documentation

## Executive Summary
`Rect` represents a rectangle with four integer coordinates: `left`, `top`, `right`, and `bottom`.

## Architecture Overview
- **Structure**: Simple data holder with four public integer fields.
- **Fields**:
    - `left`: int
    - `top`: int
    - `right`: int
    - `bottom`: int

## Detailed Functionality

### Basic Metrics
- `width()`: `right - left`
- `height()`: `bottom - top`
- `centerX()`: `(left + right) >> 1`
- `centerY()`: `(top + bottom) >> 1`
- `isEmpty()`: `left >= right || top >= bottom`

### Operations
- `set(left, top, right, bottom)`: Sets coordinates.
- `setEmpty()`: Sets all to 0.
- `offset(dx, dy)`: Moves the rectangle.
- `offsetTo(x, y)`: Moves the rectangle to a new top-left.
- `inset(dx, dy)`: Shrinks or expands the rectangle.
- `intersect(left, top, right, bottom)`: Sets the rectangle to the intersection of itself and the provided coordinates. Returns true if they intersect.
- `union(left, top, right, bottom)`: Expands the rectangle to include the provided coordinates.

### Equality
- `equals()`: Compares all four fields.

## Data Model
- `left`: `int32_t`
- `top`: `int32_t`
- `right`: `int32_t`
- `bottom`: `int32_t`

## API Reference
- Standard getters/setters and manipulation methods described above.

## Java-to-C++ Translation Guide
- **Data Types**: Use `int32_t`.
- **Parceling**:
    - `writeToParcel`: Writes `left`, `top`, `right`, `bottom` in that order.
    - `readFromParcel`: Reads them in the same order.
- **Memory**: Simple value type, no special management needed.

## Test Cases & Validation
- Standard arithmetic for width/height.
- Intersection/Union edge cases (empty rects).
- Parcel round-trip.

## Implementation Risks
- Precision: Ensure integer types are consistent with Java (32-bit signed).
- Empty Rect logic: Rigorously follow Java's `left >= right || top >= bottom` definition.
