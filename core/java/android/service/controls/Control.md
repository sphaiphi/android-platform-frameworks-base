# Control - Reverse Engineering Documentation

## Executive Summary
`Control` is a data class (Parcelable) that represents a physical or logical device controllable via the System UI. It contains metadata (title, icon, zone) and state information (status text, template).

## Data Model

### Core Fields
*   `mControlId`: `String` (NonNull) - Unique persistent identifier.
*   `mDeviceType`: `int` - Type of device (determines icon/color, see `DeviceTypes`).
*   `mTitle`: `CharSequence` - Display name.
*   `mSubtitle`: `CharSequence` - Extra info.
*   `mStructure`: `CharSequence` - Top-level group (e.g., "Home").
*   `mZone`: `CharSequence` - Specific area (e.g., "Kitchen").
*   `mAppIntent`: `PendingIntent` - Links to the provider app for advanced control.
*   `mStatus`: `int` - Current status (OK, NOT_FOUND, ERROR, DISABLED, UNKNOWN).
*   `mControlTemplate`: `ControlTemplate` - Defines the interactive UI (Toggle, Range, etc.).
*   `mStatusText`: `CharSequence` - User-facing description of state (e.g., "Locked", "72 degrees").
*   `mAuthRequired`: `boolean` - If true, requires device unlock to interact.

### Builders
*   **`StatelessBuilder`**: Used for discovery. Fixes status to `UNKNOWN` and template to `NO_TEMPLATE`.
*   **`StatefulBuilder`**: Used for active updates. Allows setting status and template.

## API Reference

### Status Codes
*   `STATUS_OK`: 1
*   `STATUS_NOT_FOUND`: 2
*   `STATUS_ERROR`: 3
*   `STATUS_DISABLED`: 4
*   `STATUS_UNKNOWN`: 0

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Custom serialization. Writes strings, ints, char sequences, and nested parcelables (`PendingIntent`, `Icon`, `ColorStateList`, `ControlTemplate`).
*   **C++**: `android::Parcelable`.
    *   `ControlTemplate` is a polymorphic object; requires a wrapper or ID-based factory for deserialization.

### Dependencies
*   `ControlTemplate` (and its subclasses in `android.service.controls.templates`).
*   `DeviceTypes`.

## Implementation Notes
*   **Immutability**: The class is effectively immutable once built.
*   **Templates**: The behavior of the control in the UI is entirely determined by the `ControlTemplate`.
