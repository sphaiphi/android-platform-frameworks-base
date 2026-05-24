# SyncStatusObserver - Reverse Engineering Documentation

## Executive Summary
`SyncStatusObserver` is a callback interface for the `SyncManager` to notify clients about status changes (pending, active, settings).

## Architecture Overview
- **Type:** Interface.
- **Implementers:** Clients using `ContentResolver.addStatusChangeListener`.

## API Reference
- `void onStatusChanged(int which)`

## Java-to-C++ Translation Guide
- **Interface**: Abstract class or `std::function`.

## Implementation Risks
- None.