# ContentUris - Reverse Engineering Documentation

## Executive Summary
`ContentUris` is a utility class for handling content URIs, specifically for parsing and appending IDs (which is a common pattern in Android `content://` URIs).

## Architecture Overview
- **Type:** Utility class (Static methods).

## Detailed Functionality

### `parseId(Uri contentUri)`
**Purpose**: Extracts the ID from the end of the path.
**Algorithm**: Gets the last path segment and parses it as a `long`.

### `withAppendedId(Uri contentUri, long id)`
**Purpose**: Creates a new URI with the ID appended.
**Algorithm**: `uri.buildUpon().appendEncodedPath(String.valueOf(id)).build()`.

### `removeId(Uri contentUri)`
**Purpose**: Removes the last segment (the ID).

## API Reference
- `public static long parseId(Uri contentUri)`
- `public static Uri withAppendedId(Uri contentUri, long id)`

## Java-to-C++ Translation Guide
- **URI Parsing**: C++ needs a robust URI parser/builder compatible with `android.net.Uri`.

## Implementation Risks
- **NumberFormat**: `parseId` throws if the last segment isn't a number.
