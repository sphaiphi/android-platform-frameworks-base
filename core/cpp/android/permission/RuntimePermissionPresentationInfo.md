# RuntimePermissionPresentationInfo - Reverse Engineering Documentation

## Executive Summary
`RuntimePermissionPresentationInfo` is a lightweight Parcelable class used to transport UI-related information about a runtime permission. It tells the UI (like Settings or Permission Controller) whether a permission is granted and if it is a standard platform permission.

## Architecture Overview
- **Type**: Data Transfer Object (DTO) / Parcelable.
- **Usage**: Returned by `PermissionControllerManager.getAppPermissions`.

## Data Model
-   **Label**: `CharSequence` - The user-visible name of the permission.
-   **Flags**:
    -   `FLAG_GRANTED` (1 << 0): Is it currently granted?
    -   `FLAG_STANDARD` (1 << 1): Is it a standard platform permission (vs. custom)?

## API Reference
-   `getLabel()`: Returns `CharSequence`.
-   `isGranted()`: Returns `boolean`.
-   `isStandard()`: Returns `boolean`.

## Java-to-C++ Translation Guide
This is a simple struct.
-   **Fields**: `std::string label` (or `String16`), `int flags`.
-   **Serialization**: Standard Parcel read/write.

## Implementation Risks
-   None. It's a simple container.
