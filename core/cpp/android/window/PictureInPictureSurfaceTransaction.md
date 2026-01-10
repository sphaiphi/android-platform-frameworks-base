# PictureInPictureSurfaceTransaction - Reverse Engineering Documentation

## Executive Summary
`PictureInPictureSurfaceTransaction` is a Parcelable class encapsulating a set of visual operations (transform, alpha, crop, corner radius) to be applied to a Picture-in-Picture (PiP) surface. It acts as a lightweight, specialized transaction object.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Visual state descriptor.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mAlpha` | `float` | Surface alpha. |
| `mPosition` | `PointF` | X, Y position. |
| `mFloat9` | `float[]` | 3x3 Matrix values. |
| `mRotation` | `float` | Rotation in degrees. |
| `mCornerRadius` | `float` | Corner radius. |
| `mShadowRadius` | `float` | Shadow radius. |
| `mWindowCrop` | `Rect` | Crop rectangle. |
| `mShouldDisableCanAffectSystemUiFlags` | `boolean` | Flag. |

## Detailed Functionality

### `apply(...)`
**Static Method**: Takes a `PictureInPictureSurfaceTransaction`, a `SurfaceControl`, and a `SurfaceControl.Transaction`.
**Logic**: Applies all the fields from the object to the transaction for the given surface.

## Java-to-C++ Translation Guide

### Data Types
*   `PointF` -> `android::graphics::PointF` (or struct {float x, y}).
*   `Matrix` (float[9]) -> `float[9]` or `android::graphics::Matrix`.

### Transaction
*   Maps to `SurfaceComposerClient::Transaction` calls in C++.
    *   `tx.setMatrix(...)`
    *   `tx.setPosition(...)`
    *   `tx.setCornerRadius(...)`

## Implementation Risks
*   None.
