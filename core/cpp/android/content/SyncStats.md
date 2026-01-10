# SyncStats - Reverse Engineering Documentation

## Executive Summary
`SyncStats` holds detailed statistics for a sync operation (inserts, updates, deletes, exceptions). It is a component of `SyncResult`.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.

## Data Model
- `numAuthExceptions`: `long`.
- `numIoExceptions`: `long`.
- `numParseExceptions`: `long`.
- `numConflictDetectedExceptions`: `long`.
- `numInserts`: `long`.
- `numUpdates`: `long`.
- `numDeletes`: `long`.
- `numEntries`: `long`.
- `numSkippedEntries`: `long`.

## API Reference
- `public void clear()`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.

## Implementation Risks
- None.