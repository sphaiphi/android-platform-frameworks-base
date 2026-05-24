# FaceEnrollFrame - Reverse Engineering Documentation

## Executive Summary
`FaceEnrollFrame` is a container for data captured during a specific frame of face enrollment. It includes the `FaceEnrollCell` (if applicable), the current stage of enrollment, and the `FaceDataFrame` containing sensor data.

## Architecture Overview
- **Type**: Data Class / Parcelable.
- **Dependencies**: `FaceEnrollCell`, `FaceDataFrame`, `FaceEnrollStages`.

## Detailed Functionality
- **Fields**:
    - `mCell` (`FaceEnrollCell`): Nullable.
    - `mStage` (`int`): `FaceEnrollStage` constant.
    - `mData` (`FaceDataFrame`): Non-null.

## Java-to-C++ Translation Guide
- **Struct**:
  ```cpp
  struct FaceEnrollFrame {
      std::optional<FaceEnrollCell> cell;
      int32_t stage;
      FaceDataFrame data;
  };
  ```
- **Parcelable**:
    - `mCell`: `writeParcelable`. In C++, handle the nullable object (likely a presence flag or similar Parcel convention).
    - `mStage`: `writeInt`.
    - `mData`: `writeParcelable`.

## API Reference
- `getCell()`, `getStage()`, `getData()`.

