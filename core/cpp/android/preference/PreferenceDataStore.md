# PreferenceDataStore - Reverse Engineering Documentation

## Executive Summary
`PreferenceDataStore` is an interface that allows applications to customize where preference data is stored (replacing default `SharedPreferences`).

**Note:** This class is deprecated.

## Architecture Overview
- **Interface**: Defines `put*` and `get*` methods for primitives (String, Set, int, long, float, boolean).

## Detailed Functionality
-   **Storage Abstraction**: Allows preferences to be backed by a database, cloud, or other storage.
-   **Default Implementation**: Methods throw `UnsupportedOperationException` (for puts) or return defaults (for gets), requiring subclasses to implement supported types.

## API Reference
-   `putString`, `getString`
-   `putInt`, `getInt`
-   (etc.)

## Java-to-C++ Translation Guide
-   **Interface**: Pure virtual class in C++.
-   **Role**: Strategy pattern for storage.
