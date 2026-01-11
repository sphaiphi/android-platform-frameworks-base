# ColorSpaceTransform - Reverse Engineering Documentation

## Executive Summary
`ColorSpaceTransform` represents a 3x3 matrix used for color conversion between different color spaces (e.g., from CIE XYZ to the camera's native sensor space). It uses `Rational` values for each matrix element to maintain high precision and avoid rounding errors during color calculations.

## Architecture Overview
- **Storage**: Immutable 3x3 matrix.
- **Precision**: Uses `android.util.Rational` (numerator/denominator pairs) instead of floats.
- **Layout**: Stored in row-major order.
- **Usage**: Used in manual color correction (`COLOR_CORRECTION_TRANSFORM`) and reported in `SENSOR_COLOR_TRANSFORM`.

## Detailed Functionality

### Matrix Transformation
**Purpose**: To perform linear color space remapping.
**Algorithm**:
The transform is applied to a 3-element color vector (e.g., RGB):
`V_out = Matrix * V_in`
Where `Matrix` is the 3x3 `ColorSpaceTransform`.

### High-Precision Storage
**Java-Specific Notes**: The internal representation uses an `int[]` of 18 elements (9 rationals * 2 ints per rational). This allows for perfect integer precision for fractional values, which is critical for consistent color science.

## Data Model

### Members
- `mElements` (`int[]`): Flattened array of rationals `[N11, D11, N12, D12, ..., N33, D33]`.

## API Reference

### Public Methods
- `Rational getElement(int column, int row)`: Individual element accessor.
- `void copyElements(Rational[] destination, int offset)`: Export as `Rational` objects.
- `void copyElements(int[] destination, int offset)`: Export as raw int pairs.

## Java-to-C++ Translation Guide

### Rational Representation
- **Java**: Uses `android.util.Rational`.
- **C++**: Use a `struct Rational { int32_t num; int32_t den; }`. 

### Matrix Layout
- **Java**: Flattened `int` array.
- **C++**: Use `std::array<Rational, 9>` or a `3x3` matrix class template.

### Performance
- **Java**: Creating many `Rational` objects can be slow.
- **C++**: Use raw integer math or fixed-point arithmetic if the target hardware doesn't have a fast FPU, but the `Rational` structure should be preserved for API compatibility.

## Test Cases & Validation
1. **Identity Transform**: Verify that a matrix with `1/1` on the diagonal and `0/1` elsewhere does not modify color values.
2. **Precision Test**: Ensure that values like `1/3` are maintained accurately and don't drift compared to float equivalents.
3. **Equality**: Verify that `ColorSpaceTransform(new int[]{1,1, ...})` equals another constructed with `Rational(1,1)`.
