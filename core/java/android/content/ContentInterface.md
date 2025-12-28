# ContentInterface - Reverse Engineering Documentation

## Executive Summary
`ContentInterface` is a general interface representing the standard read/write operations available on a Content Provider. It abstracts the underlying implementation, allowing clients to interact with `ContentProvider`, `ContentResolver`, or `ContentProviderClient` uniformly.

## Architecture Overview
- **Type:** Interface.
- **Implementers:** `ContentProvider`, `ContentResolver`, `ContentProviderClient`.

## Detailed Functionality
Defines the standard CRUD methods:
- `query`, `insert`, `bulkInsert`, `delete`, `update`.
- File access: `openFile`, `openAssetFile`, `openTypedAssetFile`.
- Other: `getType`, `getStreamTypes`, `canonicalize`, `uncanonicalize`, `refresh`, `checkUriPermission`, `call`, `applyBatch`.

## Data Model
- No state.

## API Reference
- `Cursor query(...)`
- `Uri insert(...)`
- `int delete(...)`
- `int update(...)`
- ... (Standard ContentProvider API)

## Java-to-C++ Translation Guide
- **Interface**: Pure virtual abstract class in C++.
- **Binder**: This interface closely mirrors the `IContentProvider` AIDL but is used for local process abstractions as well.

## Implementation Risks
- None. Pure interface.
