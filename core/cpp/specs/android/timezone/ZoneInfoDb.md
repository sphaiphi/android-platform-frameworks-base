# ZoneInfoDb - Reverse Engineering Documentation

## Executive Summary
`ZoneInfoDb` acts as a factory/container for time zone data, effectively representing the `tzdb` (Time Zone Database). It wraps `com.android.i18n.timezone.ZoneInfoDb`.

## Architecture Overview
*   **Singleton**: Provides global access.
*   **Wrapper**: Delegates to i18n implementation.

## Data Model
*   **`sInstance`**: Singleton.
*   **`mDelegate`**: Underlying implementation.

## API Reference
*   **`getInstance()`**: Returns the singleton.
*   **`getVersion()`**: Returns the version string of the database.

## Java-to-C++ Translation Guide
*   **Native Mapping**: This class is the Java wrapper for what is essentially a memory-mapped `tzdata` file. The C++ equivalent interacts directly with the `tzdata` file structure (header, index, data entries).

## Implementation Risks
*   **Performance**: The underlying implementation typically uses `mmap` to load the potentially large `tzdata` file efficiently.
