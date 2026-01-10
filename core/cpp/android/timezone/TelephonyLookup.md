# TelephonyLookup - Reverse Engineering Documentation

## Executive Summary
`TelephonyLookup` is a singleton class used to find time zone-related information regarding telephony networks. It acts as an entry point to retrieve a `TelephonyNetworkFinder`. It wraps `com.android.i18n.timezone.TelephonyLookup`.

## Architecture Overview
*   **Singleton Pattern**: Uses a static `sInstance` and `sLock` to ensure a single instance.
*   **Delegation**: Forwards calls to `com.android.i18n.timezone.TelephonyLookup`.

## Data Model
*   **`sInstance`**: Static singleton instance of `TelephonyLookup`.
*   **`mDelegate`**: The underlying `com.android.i18n.timezone.TelephonyLookup` implementation.

## API Reference
*   **`getInstance()`**: Static method to get the singleton instance.
*   **`getTelephonyNetworkFinder()`**: Returns a `TelephonyNetworkFinder` object. May return `null` if there is an error reading underlying data files.

## Java-to-C++ Translation Guide
*   **Singleton**: Implement using standard C++ singleton patterns (e.g., `static` local variable or `std::call_once`).
*   **Delegation**: Access the native equivalent of the timezone data lookup directly.

## Implementation Risks
*   **Data File Access**: The underlying delegate likely performs I/O to read timezone data files. This process can fail, resulting in `null` returns which must be handled.
