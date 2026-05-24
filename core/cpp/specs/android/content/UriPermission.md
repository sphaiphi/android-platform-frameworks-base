# UriPermission - Reverse Engineering Documentation

## Executive Summary
`UriPermission` represents a specific grant of read/write access to a URI.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.

## Data Model
- `mUri`: `Uri`.
- `mModeFlags`: `int` (Read/Write bits).
- `mPersistedTime`: `long`.

## API Reference
- `public Uri getUri()`
- `public boolean isReadPermission()`
- `public boolean isWritePermission()`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.

## Implementation Risks
- None.