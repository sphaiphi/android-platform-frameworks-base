# ContentCaptureContext - Reverse Engineering Documentation

## Executive Summary
Context associated with a `ContentCaptureSession`. It contains information like the associated activity component, display ID, window token, and optional extras/LocusId provided by the app.

## Data Model
*   **Identity**: `mComponentName`, `mActivityId`, `mDisplayId`, `mWindowToken`.
*   **Client Data**: `mExtras`, `mId` (LocusId).
*   **Hierarchy**: `mParentSessionId`.
*   **Flags**: `FLAG_DISABLED_BY_APP`, `FLAG_DISABLED_BY_FLAG_SECURE`, etc.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **Builder**: Implements the Builder pattern.
