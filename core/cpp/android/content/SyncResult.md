# SyncResult - Reverse Engineering Documentation

## Executive Summary
`SyncResult` conveys the outcome of a sync operation from the SyncAdapter to the SyncManager. It tracks statistics (inserts, updates, deletes) and error states (hard errors, soft errors, retry requests).

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.

## Detailed Functionality
- **Error Classification**:
    - `hasHardError()`: Fatal errors (auth, parse, too many deletions).
    - `hasSoftError()`: Retryable errors (IO).
- **Clearing**: `clear()` resets stats.

## Data Model
- `syncAlreadyInProgress`: `boolean`.
- `tooManyDeletions`: `boolean`.
- `tooManyRetries`: `boolean`.
- `databaseError`: `boolean`.
- `fullSyncRequested`: `boolean`.
- `partialSyncUnavailable`: `boolean`.
- `moreRecordsToGet`: `boolean`.
- `delayUntil`: `long`.
- `stats`: `SyncStats`.

## API Reference
- `public boolean hasHardError()`
- `public boolean hasSoftError()`
- `public boolean madeSomeProgress()`
- `public void clear()`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.

## Implementation Risks
- None.