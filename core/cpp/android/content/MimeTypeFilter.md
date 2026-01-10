# MimeTypeFilter - Reverse Engineering Documentation

## Executive Summary
`MimeTypeFilter` provides utility methods for matching MIME types against filters. It supports wildcards (`*`).

## Architecture Overview
- **Type:** Utility class (Static methods).

## Detailed Functionality
- **`matches(String mimeType, String filter)`**: Checks if a single type matches a filter.
- **`matches(String mimeType, String[] filters)`**: Checks if a type matches any filter in an array.
- **`matchesMany`**: Filters an array of types against a filter.

## Logic
- Splits types by `/`.
- Matches type and subtype.
- `*` acts as a wildcard for type or subtype.

## API Reference
- `public static boolean matches(...)`

## Java-to-C++ Translation Guide
- **String Parsing**: String splitting and comparison.

## Implementation Risks
- **Invalid MIME Types**: Handling of malformed types (missing `/`, empty parts).
