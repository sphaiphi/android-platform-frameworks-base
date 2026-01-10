# FaceDataFrame - Reverse Engineering Documentation

## Executive Summary
`FaceDataFrame` is a data class containing detailed information about a captured face frame, including acquisition info, vendor codes, and 3D positioning (pan, tilt, distance). It is shared between Authentication and Enrollment frames.

## Architecture Overview
- **Type**: Data Class / Parcelable.
- **Usage**: Payload for `FaceAuthenticationFrame` and `FaceEnrollFrame`.

## Detailed Functionality
- **Fields**:
    - `mAcquiredInfo` (`int`): `FACE_ACQUIRED_*` constant.
    - `mVendorCode` (`int`): Vendor specific code if acquired info is `FACE_ACQUIRED_VENDOR`.
    - `mPan`, `mTilt`, `mDistance` (`float`): Position data. Range [-1, 1] for good capture.
    - `mIsCancellable` (`boolean`): If the operation can be cancelled.

## Data Model
- **Primitives**: `int`, `float`, `boolean`.

## Java-to-C++ Translation Guide
- **Struct**:
  ```cpp
  struct FaceDataFrame {
      int32_t acquiredInfo;
      int32_t vendorCode;
      float pan;
      float tilt;
      float distance;
      bool isCancellable;
  };
  ```
- **Parcelable**: Standard read/write of primitives.

## API Reference
- `getAcquiredInfo()`, `getVendorCode()`, `getPan()`, `getTilt()`, `getDistance()`, `isCancellable()`.

