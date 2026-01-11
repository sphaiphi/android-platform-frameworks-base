# PrinterInfo - Reverse Engineering Documentation

## Executive Summary
`PrinterInfo` represents a discovered printer. It contains the `PrinterId`, display name, status, and optionally its `PrinterCapabilitiesInfo`.

## Architecture Overview
- **Type**: Parcelable Data Class (final).
- **Builder**: Uses `Builder` class.

## Detailed Functionality
-   **Status**: Idle, Busy, Unavailable.
-   **Icons**: Supports loading icons from resources or custom icons (via `PrintManager`).
-   **Info Intent**: Can hold a `PendingIntent` to launch a printer-specific info activity.

## Data Model
-   `mId`: PrinterId
-   `mName`: String
-   `mStatus`: int
-   `mCapabilities`: PrinterCapabilitiesInfo
-   `mDescription`: String

## Java-to-C++ Translation Guide
-   **PendingIntent**: Maps to a C++ representation of a PendingIntent (likely opaque or Binder token).
-   **Icons**: Icon loading logic is Android-specific (PackageManager); C++ layer likely just holds the resource ID or icon object.
