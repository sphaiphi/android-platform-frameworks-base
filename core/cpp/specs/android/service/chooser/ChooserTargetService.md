# ChooserTargetService - Reverse Engineering Documentation

## Executive Summary
`ChooserTargetService` is an **abstract** and **deprecated** service that allowed apps to expose deep-link targets (Direct Share) to the system chooser (sharesheet). It has been replaced by the Sharing Shortcuts API.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IChooserTargetService.Stub` via an inner wrapper.
*   **Manifest**: Requires `android.permission.BIND_CHOOSER_TARGET_SERVICE` and `SERVICE_INTERFACE`.
*   **Mechanism**: The system binds to this service when the user invokes `ACTION_CHOOSER`, queries for targets, and displays them.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `IChooserTargetService` binder.

### `onGetChooserTargets` (Abstract)
**Purpose**: Called by the system to retrieve specific targets for an intent.
**Parameters**:
*   `targetActivityName`: The component name of the activity that matched the intent filter.
*   `matchedFilter`: The intent filter that matched.
**Returns**: A list of `ChooserTarget` objects.
**Threading**: Called on a binder thread.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IChooserTargetService.Stub` wrapper.
*   **C++**: `BnChooserTargetService`.

### Data Model
*   `ChooserTarget` (Parcelable).

## Implementation Notes
*   **Deprecated**: New implementations should not use this. The C++ implementation likely exists for legacy support if the framework still supports it internally.
