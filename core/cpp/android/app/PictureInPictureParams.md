# PictureInPictureParams - Reverse Engineering Documentation

## Executive Summary
`PictureInPictureParams` is a data container used to configure an `Activity` for Picture-in-Picture (PiP) mode. It allows apps to specify attributes like aspect ratio, custom user actions (buttons in the PiP window), source bounds for transitions, and whether the activity should automatically enter PiP.

## Architecture Overview
- **Structure**:
    - `mAspectRatio`: Desired width/height ratio.
    - `mExpandedAspectRatio`: Ratio for expanded PiP mode.
    - `mUserActions`: List of `RemoteAction` buttons (e.g., play/pause).
    - `mCloseAction`: Custom action to replace the system close button.
    - `mSourceRectHint`: Rect indicating the area of the activity to remain visible during transition.
    - `mAutoEnterEnabled`: Boolean flag for automatic PiP transition on home press.
    - `mSeamlessResizeEnabled`: Flag for smooth window resizing.
    - `mTitle`, `mSubtitle`: Informational text for the PiP window.
- **Inheritance**: Implements `Parcelable`.
- **Builder Pattern**: Uses an internal `Builder` class for configuration.

## Detailed Functionality

### Aspect Ratio Validation
**Purpose**: Ensures the PiP window stays within reasonable limits.
**Logic**: Aspect ratios must typically be between 2.39:1 and 1:2.39. The `isSameAspectRatio` method allows for slight rounding errors during comparison.

### Action Truncation
**Purpose**: Fits buttons within the limited PiP UI space.
**Logic**: `truncateActions(int size)` limits the number of `mUserActions` to the system-allowed maximum (usually 3).

### Merging and Copying
**Purpose**: Efficiently updating parameters.
**Mechanism**: `copyOnlySet(PictureInPictureParams other)` merges fields from another instance only if they were explicitly set, allowing for partial updates to the PiP configuration.

## API Reference
- `public Rational getAspectRatio()`: Returns current ratio.
- `public List<RemoteAction> getActions()`: Returns custom buttons.
- `public boolean isAutoEnterEnabled()`: Returns auto-PiP flag.
- `public Rect getSourceRectHint()`: Returns transition area hint.

## Java-to-C++ Translation Guide
- **Rational Mapping**: Use `android::util::Rational` in C++.
- **Rect Mapping**: Use `android::graphics::Rect`.
- **RemoteAction**: Map to `android::app::RemoteAction`.
- **Optional Fields**: Use `std::optional` or pointers to represent fields that might not be set (like `mAspectRatio`).

## Implementation Risks
- **Transition Smoothness**: `mSourceRectHint` is critical for avoiding "jumpy" transitions. C++ implementation must ensure these coordinates are relative to the window bounds correctly.
- **IPC Payload**: Including many `RemoteAction` objects can increase the size of the parcel. C++ marshalling should be efficient.
