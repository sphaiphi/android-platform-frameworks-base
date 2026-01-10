# DisplayAreaAppearedInfo - Reverse Engineering Documentation

## Executive Summary
`DisplayAreaAppearedInfo` is a simple Parcelable data class sent to a `DisplayAreaOrganizer` when a display area it controls becomes available (appears). It contains the metadata (`DisplayAreaInfo`) and the control surface (`SurfaceControl`).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: DTO for organizer callback.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mDisplayAreaInfo` | `DisplayAreaInfo` | Metadata about the DisplayArea (token, config, featureId). |
| `mLeash` | `SurfaceControl` | The surface control (leash) for manipulating the DA. |

## Java-to-C++ Translation Guide

### Data Types
*   `DisplayAreaInfo` -> C++ Parcelable (needs implementation).
*   `SurfaceControl` -> `android::view::SurfaceControl` (ASurfaceControl in NDK, or internal C++ object).

### Parceling
*   **Write**:
    1.  `mDisplayAreaInfo` (TypedObject)
    2.  `mLeash` (TypedObject)

## Implementation Risks
*   **SurfaceControl Ownership**: Receiving a `SurfaceControl` via Binder implies ownership transfer (or at least a valid handle creation). Ensure the C++ side correctly manages the lifecycle (release) of the received surface.
