# TimeZoneFinder - Reverse Engineering Documentation

## Executive Summary
`TimeZoneFinder` is the main entry point for finding time zones based on country information (location). It wraps `com.android.i18n.timezone.TimeZoneFinder` (often backed by `tzlookup.xml`).

## Architecture Overview
*   **Singleton**: Singleton access pattern.
*   **Delegation**: Wraps `com.android.i18n.timezone.TimeZoneFinder`.

## Data Model
*   **`sInstance`**: Singleton instance.
*   **`mDelegate`**: Underlying implementation.

## API Reference
*   **`getInstance()`**: Returns the singleton.
*   **`getIanaVersion()`**: Returns the IANA rules version (e.g., "2020a") associated with the data. Returns `null` on error.
*   **`lookupCountryTimeZones(String countryIso)`**: Returns `CountryTimeZones` for the specified ISO country code.

## Java-to-C++ Translation Guide
*   **Data Source**: This corresponds to reading the `tzlookup.xml` file in Android's timezone data module.
*   **Functionality**: Implement lookup of country-specific time zone data.

## Implementation Risks
*   **Data Integrity**: Relies on the valid state of timezone data files on the device.
