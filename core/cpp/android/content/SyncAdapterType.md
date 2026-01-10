# SyncAdapterType - Reverse Engineering Documentation

## Executive Summary
`SyncAdapterType` describes the characteristics of a SyncAdapter (authority, account type, user visibility, etc.). It acts as a key/descriptor.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Usage:** Used by `SyncAdaptersCache` and `ContentResolver.getSyncAdapterTypes()`.

## Data Model
- `authority`: `String`.
- `accountType`: `String`.
- `isKey`: `boolean` (If true, only authority and accountType are relevant - used for lookups).
- `userVisible`: `boolean`.
- `supportsUploading`: `boolean`.
- `isAlwaysSyncable`: `boolean`.
- `allowParallelSyncs`: `boolean`.
- `settingsActivity`: `String`.
- `packageName`: `String`.

## API Reference
- `public static SyncAdapterType newKey(String authority, String accountType)`
- `public boolean supportsUploading()`
- `public boolean isUserVisible()`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.

## Implementation Risks
- None.