# ExternalStorageStats - Reverse Engineering Documentation

## Executive Summary
`ExternalStorageStats` is a Parcelable class providing storage usage statistics for a user on an external storage volume. It breaks down usage by category (audio, video, image, app, obb).

## Architecture Overview
- **Implements**: `Parcelable`.
- **Usage**: Returned by `StorageStatsManager.queryExternalStatsForUser`.

## Detailed Functionality

### Metrics
- `totalBytes`: Total usage.
- `audioBytes`, `videoBytes`, `imageBytes`: Media usage.
- `appBytes`: App-specific files on external storage.
- `obbBytes`: OBB (Opaque Binary Blobs) expansion files.

### Parceling
- Reads/Writes 6 `long` values.

## Data Model

| Field | Type | Note |
| :--- | :--- | :--- |
| `totalBytes` | long | |
| `audioBytes` | long | |
| `videoBytes` | long | |
| `imageBytes` | long | |
| `appBytes` | long | |
| `obbBytes` | long | |

## API Reference
- Getters for all fields.
- `@hide` fields are public in the class but hidden from SDK.

## Java-to-C++ Translation Guide
- Simple struct with 6 `int64_t` fields.

## Test Cases & Validation
- Standard serialization test.
