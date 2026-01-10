# AutoGrowArray - Reverse Engineering Documentation

## Executive Summary
`AutoGrowArray` provides helper classes (`ByteArray`, `IntArray`, `FloatArray`) implementing dynamically growing arrays for primitive types. They are optimized for performance and are NOT thread-safe.

## Components

### `ByteArray`
- **Backing**: `byte[] mValues`.
- **Methods**: `append(byte)`, `resize(int)`, `clear()`, `get(int)`, `set(int, byte)`, `size()`, `getRawArray()`.

### `IntArray`
- **Backing**: `int[] mValues`.
- **Methods**: Similar to `ByteArray`.

### `FloatArray`
- **Backing**: `float[] mValues`.
- **Methods**: Similar to `ByteArray`.

## Algorithm
- **Growth Strategy**: `computeNewCapacity` calculates new size. Often `current + (current < 6 ? 12 : current >> 1)` (approx 1.5x growth).

## Java-to-C++ Translation Guide
- **Standard Library**: These maps directly to `std::vector<uint8_t>`, `std::vector<int32_t>`, `std::vector<float>`.
- **Optimization**: `std::vector` handles growth efficiently. `getRawArray` maps to `data()`.
