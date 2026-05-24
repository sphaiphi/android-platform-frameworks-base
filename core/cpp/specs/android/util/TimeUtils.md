# TimeUtils - Reverse Engineering Documentation

## Executive Summary
Utilities for time zones and time formatting.

## Key Functionality
*   **`getTimeZone`**: Resolves specific time zones based on country, offset, and DST status using `TimeZoneFinder` and `CountryTimeZones`.
*   **`formatDuration`**: Formats elapsed time into human readable strings (e.g., "+1d2h30m").
*   **`logTimeOfDay`**: Formats timestamps for logging.

## Java-to-C++ Translation Guide
*   **Time Zones**: Relies heavily on `android.icu` and internal `com.android.i18n.timezone`. C++ needs `ICU4C`.
*   **Formatting**: String formatting logic is manual and can be ported directly.

## Implementation Risks
*   **Dependencies**: High dependency on Android's timezone data infrastructure (`ZoneInfoDb`).
