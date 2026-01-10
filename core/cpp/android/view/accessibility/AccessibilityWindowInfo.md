# AccessibilityWindowInfo - Reverse Engineering Documentation

## Executive Summary
Describes a window in the accessibility window hierarchy. It is a snapshot of the window's state (bounds, type, layering).

## Data Model
*   **Type**: `TYPE_APPLICATION`, `TYPE_SYSTEM`, `TYPE_ACCESSIBILITY_OVERLAY`, etc.
*   **Hierarchy**: `mParentId`, `mChildIds`.
*   **Bounds**: `mRegionInScreen`.
*   **Properties**: `active`, `focused`, `pictureInPicture`.

## Key Algorithms
*   **`differenceFrom`**: Compares two instances to detect changes (used for generating events).

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **Object Pooling**: Uses `SynchronizedPool`.
