# ApnService - Reverse Engineering Documentation

## Executive Summary
`ApnService` allows a carrier to provide a custom list of Access Point Names (APNs) to restore default settings, bypassing the built-in XML configuration.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IApnSourceService.Stub`.
*   **Configuration**: Defined via `apn_source_service` resource in TelephonyProvider.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Returns the `IApnSourceService` binder.

### `onRestoreApns` (Abstract)
**Purpose**: Returns the list of `ContentValues` representing the APNs for a given subscription ID.
**Threading**: Called on a worker thread.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IApnSourceService.Stub`.
*   **C++**: `BnApnSourceService`.

### Data Structures
*   **Java**: `ContentValues`.
*   **C++**: Typically maps to `PersistableBundle` or a specific map type in AIDL. Need to check `IApnSourceService.aidl` definition. If it's literally `ContentValues`, it might be complex as `ContentValues` is Parcelable but tied to ContentProvider.

## Implementation Notes
*   **Worker Thread**: The stub implementation invokes `onRestoreApns` directly, so it blocks the binder thread (Java docs say `@WorkerThread` but the implementation in `ApnService.java` calls it directly from the binder stub, meaning it runs on the binder thread pool).
