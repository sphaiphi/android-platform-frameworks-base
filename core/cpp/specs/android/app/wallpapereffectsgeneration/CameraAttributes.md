# CameraAttributes - Reverse Engineering Documentation

## Executive Summary
`CameraAttributes` is a data class representing the parameters of a virtual camera in a 3D scene. It is used in the context of wallpaper effects generation (cinematic wallpapers) to define viewpoints for keyframes (start/end) of an animation.

## Architecture Overview
- **Package**: `android.app.wallpapereffectsgeneration`
- **Implements**: `Parcelable`
- **Role**: 3D Math / Graphics Data Structure.
- **Usage**: Used inside `CinematicEffectResponse`.

## Detailed Functionality

### 3D Coordinate Representation
**Purpose**: Store camera positioning and frustum data.
**Data**:
- **Anchor Point**: Point in 3D world space (x, y, z).
- **Anchor Point UV**: Projected point in 2D image space (u, v).
- **Orbit**: Yaw and Pitch degrees around the anchor.
- **Dolly**: Distance from anchor.
- **FOV**: Vertical field of view.
- **Frustum**: Near and Far plane distances.

## Data Model

| Field | Type | Java Type | Description |
|-------|------|-----------|-------------|
| `mAnchorPointInWorldSpace` | Vector3 | `float[]` (size 3) | Target point in 3D. |
| `mAnchorPointInOutputUvSpace` | Vector2 | `float[]` (size 2) | Target point in 2D texture. |
| `mCameraOrbitYawDegrees` | Float | `float` | Orbit rotation. |
| `mCameraOrbitPitchDegrees` | Float | `float` | Orbit rotation. |
| `mDollyDistanceInWorldSpace` | Float | `float` | Distance to target. |
| `mVerticalFovDegrees` | Float | `float` | Lens FOV. |
| `mFrustumNearInWorldSpace` | Float | `float` | Clipping plane. |
| `mFrustumFarInWorldSpace` | Float | `float` | Clipping plane. |

## Java-to-C++ Translation Guide

- **Arrays**: Java uses `float[]` for vectors. C++ should use `std::array<float, 3>` or a dedicated `vec3` struct for `mAnchorPointInWorldSpace`, and `std::array<float, 2>` / `vec2` for `mAnchorPointInOutputUvSpace`.
- **Parcelable**:
  - `readFloatArray`/`createFloatArray` corresponds to reading length then raw floats.
- **Validation**: Java uses `@FloatRange` annotations. C++ setters should ideally assert or clamp these values if safety is required, though standard behavior is usually just storage.

## Test Cases & Validation
- **Serialization**: Ensure a `CameraAttributes` object written to a Parcel in C++ can be read by Java and vice-versa, preserving the exact float values.

## Implementation Risks
- **Array Sizes**: Java explicitly expects size 3 for WorldSpace and size 2 for UVSpace. C++ implementation must enforce these sizes to prevent memory corruption or deserialization errors.
