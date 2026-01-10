# TaskSnapshot - Reverse Engineering Documentation

## Executive Summary
`TaskSnapshot` is a Parcelable class representing a static capture of a Task's visual state. It includes the `HardwareBuffer` (bitmap), color space, orientation, rotation, and inset information. It is primarily used for the "Recents" view and for displaying a preview while an app is launching.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Visual state snapshot.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mId` | `long` | Unique identifier. |
| `mCaptureTime` | `long` | Timestamp (nanoseconds). |
| `mTopActivityComponent` | `ComponentName` | Name of the top activity. |
| `mSnapshot` | `HardwareBuffer` | The raw graphic buffer. |
| `mOrientation` | `int` | Orientation (Portrait/Landscape). |
| `mRotation` | `int` | Surface rotation. |
| `mTaskSize` | `Point` | Size before scaling. |
| `mContentInsets` | `Rect` | System bar insets. |
| `mLetterboxInsets` | `Rect` | Letterbox regions. |
| `mIsLowResolution` | `boolean` | Flag for down-sampled snapshots. |
| `mIsRealSnapshot` | `boolean` | True if real (not app-theme placeholder). |
| `mWindowingMode` | `int` | Mode at time of capture. |
| `mAppearance` | `int` | System UI appearance flags. |
| `mIsTranslucent` | `boolean` | Window translucency. |
| `mHasImeSurface` | `boolean` | True if IME was captured. |
| `mUiMode` | `int` | UI mode (Night/Day). |
| `mColorSpace` | `ColorSpace` | Buffer color space. |

## Detailed Functionality

### Reference Counting
*   `addReference(int usage)` / `removeReference(int usage)`: Manual reference counting for internal use within the core framework to manage the lifecycle of the `HardwareBuffer`.
*   `mSafeSnapshotReleaser`: Optional callback to delegate buffer closing to the system server.

## Java-to-C++ Translation Guide

### Data Types
*   `HardwareBuffer` -> `AHardwareBuffer` or `android::GraphicBuffer`.
*   `ColorSpace` -> Map to `android::dataspace`.

### Memory Management
*   The C++ implementation must ensure `AHardwareBuffer_release` is called exactly when references drop to zero.

## Implementation Risks
*   **Buffer Lifecycle**: Multiple processes might hold references to the same buffer. Native side must use proper AIDL handling for `HardwareBuffer` which handles cross-process ref-counting via file descriptors.
