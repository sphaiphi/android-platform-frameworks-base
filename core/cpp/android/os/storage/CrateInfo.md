# CrateInfo - Reverse Engineering Documentation

## Executive Summary
`CrateInfo` encapsulates metadata about a "crate," which is a managed storage directory. It includes identifiers (crate ID, package name, UID), user-facing labels, and expiration policies. This structure is used by the system (StorageStatsManager, installd) to manage and query storage usage per crate.

## Architecture Overview
-   **Pattern**: Value Object / Data Transfer Object (DTO).
-   **Implements**: `Parcelable`.
-   **Role**: Bridges information between `StorageStatsManager`, `installd` (native daemon), and `system_server`.

## Data Model
-   **Identifiers**:
    -   `mId`: Directory name of the crate.
    -   `mUid`: UID of the owning app (set by system).
    -   `mPackageName`: Package name of the owner (set by system).
-   **Metadata**:
    -   `mLabel`: User-visible display name.
    -   `mExpiration`: Timestamp (millis) after which the crate is considered expired/deletable.

## API Reference
-   `getLabel()`: Returns the label or ID if label is empty.
-   `getExpirationMillis()`: Returns expiration timestamp.
-   `copyFrom(int uid, String packageName, String id)`: Static factory for system use.

## Java-to-C++ Translation Guide
-   **Parceling**: Standard Int, String, Long serialization.
-   **Equivalent**: Likely maps to a struct in `installd` or `StorageStatsService` logic.
-   **Validation**: `Preconditions` checks (non-null ID/Label, non-negative expiration) should be replicated.
