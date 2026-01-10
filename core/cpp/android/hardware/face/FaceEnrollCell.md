# FaceEnrollCell - Reverse Engineering Documentation

## Executive Summary
`FaceEnrollCell` represents a specific cell in a matrix (X, Y, Z coordinates) corresponding to a desired face angle/position during enrollment. It is used to guide the user to capture different angles of their face.

## Architecture Overview
- **Type**: Data Class / Parcelable.
- **Usage**: Part of `FaceEnrollFrame` to indicate which cell was captured or needs capturing.

## Data Model
- `mX`, `mY`, `mZ`: `int` coordinates.

## Java-to-C++ Translation Guide
- **Struct**:
  ```cpp
  struct FaceEnrollCell {
      int32_t x;
      int32_t y;
      int32_t z;
  };
  ```
- **Parcelable**: Standard read/write of 3 integers.

## API Reference
- `getX()`, `getY()`, `getZ()`.

