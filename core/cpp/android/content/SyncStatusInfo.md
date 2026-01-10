# SyncStatusInfo - Reverse Engineering Documentation

## Executive Summary
`SyncStatusInfo` persists the status of sync operations for a specific authority. It tracks success/failure times, history of events, and aggregate statistics. This is an internal class used by `SyncStorageEngine`.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Usage:** Persisted to disk (XML/Binary) by `SyncManager`.

## Data Model
- `authorityId`: `int`.
- `lastSuccessTime`: `long`.
- `lastFailureTime`: `long`.
- `lastFailureMesg`: `String`.
- `totalStats`: `Stats` (Inner class).
- `periodicSyncTimes`: `ArrayList<Long>`.
- `mLastEventTimes`, `mLastEvents`: History logs.

## API Reference
- `public void addEvent(String message)`
- `public void setLastSuccess(int source, long lastSyncTime)`
- `public void setLastFailure(int source, long lastSyncTime, String failureMessage)`

## Java-to-C++ Translation Guide
- **Serialization**: This class is heavily involved in the persistence of sync state. The binary format (Parcel) must be exact.
- **ArrayList**: `std::vector`.

## Implementation Risks
- **Versioning**: The class handles multiple versions (`VERSION`) for backward compatibility during deserialization.