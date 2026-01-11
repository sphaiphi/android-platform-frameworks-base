# CountryTimeZones - Reverse Engineering Documentation

## Executive Summary
`CountryTimeZones` provides information about a country's time zones. It is a wrapper class that delegates all functionality to `com.android.i18n.timezone.CountryTimeZones`. It represents the mapping associated with a specific country code, allowing lookups of time zones based on offset, DST status, and bias.

## Architecture Overview
This class is part of the `android.timezone` package, which serves as a stable internal API surface for the Android framework to access time zone data. It strictly follows the Proxy pattern, holding a reference to a delegate object from the `com.android.i18n.timezone` package and forwarding method calls to it.

## Data Model

### Inner Classes
1.  **`TimeZoneMapping`**
    *   **Purpose**: Represents a specific time zone ID (e.g., "America/Los_Angeles") associated with the country.
    *   **Delegate**: Wraps `com.android.i18n.timezone.CountryTimeZones.TimeZoneMapping`.
    *   **Key Fields**: None visible directly; acts as a proxy.

2.  **`OffsetResult`**
    *   **Purpose**: The result of looking up a time zone by offset. Contains the matching time zone and a boolean indicating if it was the only match.
    *   **Delegate**: Does not wrap a delegate directly but constructs instances based on the result from the underlying i18n delegate.
    *   **Key Fields**:
        *   `mTimeZone`: `android.icu.util.TimeZone`
        *   `mIsOnlyMatch`: `boolean`

### Main Class
*   **`mDelegate`**: `com.android.i18n.timezone.CountryTimeZones`. The underlying implementation object.

## API Reference

### `CountryTimeZones` (Main Class)
*   **`matchesCountryCode(String countryIso)`**: Checks if the ISO code matches the country this object represents.
*   **`getDefaultTimeZoneId()`**: Returns the default time zone ID for the country.
*   **`getDefaultTimeZone()`**: Returns the default `TimeZone` object.
*   **`isDefaultTimeZoneBoosted()`**: Returns true if the default time zone is a "good" choice generally (e.g., covers a large majority of the population).
*   **`hasUtcZone(long whenMillis)`**: Checks if the country has a zone that uses UTC at the given time.
*   **`lookupByOffsetWithBias(long whenMillis, TimeZone bias, int totalOffsetMillis, boolean isDst)`**: Looks up a time zone matching the offset and DST state, optionally preferring the `bias` zone.
*   **`lookupByOffsetWithBias(long whenMillis, TimeZone bias, int totalOffsetMillis)`**: Overload without explicit DST state.
*   **`getEffectiveTimeZoneMappingsAt(long whenMillis)`**: Returns a list of `TimeZoneMapping` objects effective at the given time.

### `TimeZoneMapping`
*   **`getTimeZoneId()`**: Returns the ID string.
*   **`getTimeZone()`**: Returns the `TimeZone` object.

### `OffsetResult`
*   **`getTimeZone()`**: Returns the matching `TimeZone`.
*   **`isOnlyMatch()`**: Returns true if this was the unique match for the criteria.

## Java-to-C++ Translation Guide
Since this class is a wrapper around `com.android.i18n.timezone`, the C++ implementation should likely interact with the underlying data source directly, or through a similar abstraction layer if one exists in the native codebase.

*   **Delegation**: The C++ implementation should likely skip this wrapper layer and interface with the native equivalent of `com.android.i18n.timezone` (likely in `libcore` or `art` module).
*   **Types**:
    *   `android.icu.util.TimeZone` -> `icu::TimeZone` (ICU4C).
    *   `String` -> `std::string`.
    *   `List<TimeZoneMapping>` -> `std::vector<TimeZoneMapping>`.

## Implementation Risks
*   **Dependency on i18n**: Any changes in `com.android.i18n.timezone` API will break this wrapper.
*   **Hidden API**: This class is `@hide`, meaning it's not a public Android API, but changes here can affect system components relying on it.
