# RuntimePermissionUsageInfo - Reverse Engineering Documentation

## Executive Summary
`RuntimePermissionUsageInfo` is a simple Parcelable class that encapsulates statistics about how many apps are using a specific permission. It is typically used for dashboard summaries (e.g., "5 apps accessed Location").

## Architecture Overview
- **Type**: Data Transfer Object (DTO) / Parcelable.
- **Usage**: Returned by `PermissionControllerManager.getPermissionUsages`.

## Data Model
-   **Name**: `String` - The permission or permission group name.
-   **AppAccessCount**: `int` - Number of apps holding/using the permission.

## API Reference
-   `getName()`: Returns `String`.
-   `getAppAccessCount()`: Returns `int`.

## Java-to-C++ Translation Guide
-   **Fields**: `std::string mName`, `int mNumUsers`.
-   **Serialization**: Standard Parcel read/write.

## Implementation Risks
-   None. Simple DTO.
