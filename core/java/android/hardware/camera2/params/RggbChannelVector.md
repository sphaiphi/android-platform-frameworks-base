# RggbChannelVector - Reverse Engineering Documentation

## Executive Summary
`RggbChannelVector` is an immutable container for four floating-point values representing the components of a 2x2 Bayer RAW pixel block. It is typically used for specifying or reporting gains and offsets applied to the four color channels (Red, Green-Even, Green-Odd, Blue).

## Architecture Overview
- **Storage**: Four `float` members.
- **Order**: Always follows the RGGB pattern: `[Red, Green_Even, Green_Odd, Blue]`.
- **Normalization**: Values are typically normalized to `[0.0, 1.0]`.

## Detailed Functionality

### Channel Mapping
**Purpose**: To provide a consistent interface for Bayer-domain operations.
**Indices**:
- `RED` (0): Red channel.
- `GREEN_EVEN` (1): Green channel in even sensor rows.
- `GREEN_ODD` (2): Green channel in odd sensor rows.
- `BLUE` (3): Blue channel.

### Operations
**Java-Specific Notes**: The class provides a `copyTo(float[] destination, int offset)` method for efficient flat-array extraction, common in JNI and HAL interactions.

## Data Model

### Members
- `mRed`, `mGreenEven`, `mGreenOdd`, `mBlue` (`float`): The channel values.

## API Reference

### Public Methods
- `float getRed()`, `getGreenEven()`, `getGreenOdd()`, `getBlue()`: Individual accessors.
- `float getComponent(int colorChannel)`: Index-based accessor.
- `void copyTo(float[] destination, int offset)`: Bulk export.

## Java-to-C++ Translation Guide

### Layout
- **Java**: Four separate float fields.
- **C++**: Use a `std::array<float, 4>` or a struct with an overloaded `operator[]` for both named and indexed access. Ensure `sizeof(RggbChannelVector) == 16` for potential SIMD optimizations or direct memory mapping.

### Validation
- **Java**: Checks `checkArgumentFinite` to ensure no NaN or Infinity.
- **C++**: Use `std::isfinite()` in the constructor.

## Test Cases & Validation
1. **Index Consistency**: Verify `getComponent(0)` returns the same value as `getRed()`.
2. **Equality**: Ensure two vectors with the same floats are considered equal.
3. **Array Export**: Verify `copyTo` produces the correct sequence `[R, Ge, Go, B]`.
