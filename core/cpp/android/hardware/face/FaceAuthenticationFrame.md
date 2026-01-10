# FaceAuthenticationFrame - Reverse Engineering Documentation

## Executive Summary
`FaceAuthenticationFrame` is a wrapper class that holds a `FaceDataFrame`. It represents a single frame of data captured during face authentication. It is Parcelable.

## Architecture Overview
- **Type**: Wrapper Data Class / Parcelable.
- **Content**: Contains a single `FaceDataFrame` object.

## Detailed Functionality
- **Constructor**: `FaceAuthenticationFrame(@NonNull FaceDataFrame data)`
- **Getter**: `getData()` returns the `FaceDataFrame`.
- **Parcelable**: Delegates marshalling to `FaceDataFrame`.

## Data Model
- `mData`: `FaceDataFrame` (Non-null).

## Java-to-C++ Translation Guide
- **Structure**: C++ struct/class containing a `FaceDataFrame`.
- **Parceling**: Read/Write the `FaceDataFrame`.

## API Reference
- `getData()`

