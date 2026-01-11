# StorageStatsManager - Reverse Engineering Documentation

## Executive Summary
`StorageStatsManager` is the client-side system service wrapper for accessing storage statistics. It provides APIs to query usage for packages, UIDs, and users, and to check quota support.

## Architecture Overview
- **Service**: `Context.STORAGE_STATS_SERVICE`.
- **IPC**: Wraps `IStorageStatsManager` (Binder proxy).
- **Permissions**: Enforces `PACKAGE_USAGE_STATS` for cross-app queries.

## Detailed Functionality

### Core Methods
- **`isQuotaSupported(UUID)`**: Checks if the filesystem supports quotas.
- **`getTotalBytes(UUID)`**: Returns physical media size.
- **`getFreeBytes(UUID)`**: Returns free space (usable).
- **`getCacheBytes(UUID)`**: Returns reclaimable cache size.
- **`queryStatsForPackage(UUID, String, UserHandle)`**: Returns `StorageStats` for a package.
- **`queryStatsForUid(UUID, int)`**: Returns `StorageStats` for a UID.
- **`queryStatsForUser(UUID, UserHandle)`**: Returns `StorageStats` for a user.
- **`queryExternalStatsForUser`**: Returns `ExternalStorageStats`.
- **`queryCratesFor*`**: Returns `CrateInfo` (Opaque Binary Blobs/crates).

### Error Handling
- Wraps `RemoteException` into `RuntimeException`.
- Converts `ParcelableException` into `IOException` or `NameNotFoundException`.

## Java-to-C++ Translation Guide
- **Client Wrapper**: This is a client-side wrapper. In C++, you would typically use the `IStorageStatsManager` Bp (Binder Proxy) directly or wrap it similarly.
- **Exception Conversion**: Java checked exceptions (`IOException`) need to be handled via `Status` objects or `std::expected`/`Result` types in C++.

## Implementation Risks
- **UUID Handling**: The API uses `java.util.UUID`. C++ has generic 128-bit UUID handling; ensure endianness matches when converting to/from the `String` or MSB/LSB format used by Binder.
