# CinematicEffectResponse - Reverse Engineering Documentation

## Executive Summary
`CinematicEffectResponse` is the result object returned by the effects generation service. It contains the status of the operation, classification of the image content, and the generated 3D assets (meshes) and animation keyframes (camera attributes) if successful.

## Architecture Overview
- **Package**: `android.app.wallpapereffectsgeneration`
- **Implements**: `Parcelable`
- **Role**: Response DTO.
- **Dependencies**: `TexturedMesh`, `CameraAttributes`.

## Detailed Functionality

### Status Codes
Defines a set of `int` constants (`CINEMATIC_EFFECT_STATUS_*`) indicating success, failure, or specific errors (too flat, not supported, pending, etc.).

### Image Content Types
Defines constants (`IMAGE_CONTENT_TYPE_*`) to classify the image (People, Landscape, Other).

### Data Storage
- **Meshes**: A list of `TexturedMesh` objects representing the 3D geometry of the effect.
- **Animation**: `StartKeyFrame` and `EndKeyFrame` (`CameraAttributes`) defining the camera movement.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mStatusCode` | `int` | Result status (see constants). |
| `mTaskId` | `String` | Correlates with Request ID. |
| `mImageContentType` | `int` | Content classification. |
| `mTexturedMeshes` | `List<TexturedMesh>` | generated 3D geometry. |
| `mStartKeyFrame` | `CameraAttributes` | Animation start state. |
| `mEndKeyFrame` | `CameraAttributes` | Animation end state. |

## Java-to-C++ Translation Guide

- **Enums**: Convert `IntDef` constants to C++ `enum class` or `static const int`.
- **Lists**: `List<TexturedMesh>` -> `std::vector<TexturedMesh>`.
- **Parceling**:
  - `readTypedList` is used in Java. In C++, this implies a loop reading Parcelable objects.

## Implementation Risks
- **Large Data**: The response can contain multiple meshes with bitmaps. The Parcel size can be significant. The individual `TexturedMesh` objects handle their own large-data parceling (via Blobs), but the list itself adds overhead.

## Questions for C++ Team
- How are large lists of parcelables handled in the specific C++ binder implementation being used?
