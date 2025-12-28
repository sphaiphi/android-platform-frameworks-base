# SyncAdaptersCache - Reverse Engineering Documentation

## Executive Summary
`SyncAdaptersCache` is a cache of registered SyncAdapters. It parses `AndroidManifest.xml` files to find services declaring `android.content.SyncAdapter` and caches their metadata (`SyncAdapterType`).

## Architecture Overview
- **Inheritance:** Extends `RegisteredServicesCache<SyncAdapterType>`.
- **Data:** Maps user IDs and authorities to lists of SyncAdapters.

## Detailed Functionality
- **`parseServiceAttributes`**: Parses the `<sync-adapter>` XML tag to create a `SyncAdapterType`.
- **`getSyncAdapterPackagesForAuthority`**: Returns the packages that handle a specific authority.

## Data Model
- `mAuthorityToSyncAdapters`: `SparseArray<ArrayMap<String, String[]>>` - Cache structure.

## API Reference
- `public String[] getSyncAdapterPackagesForAuthority(String authority, int userId)`

## Java-to-C++ Translation Guide
- **PackageManager**: Depends heavily on `PackageManager` to query services.
- **XML Parsing**: Needs an XML parser.

## Implementation Risks
- **Cache Invalidation**: Must handle package updates/removals correctly (handled by superclass `RegisteredServicesCache`).