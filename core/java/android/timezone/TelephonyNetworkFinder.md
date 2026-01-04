# TelephonyNetworkFinder - Reverse Engineering Documentation

## Executive Summary
`TelephonyNetworkFinder` provides functionality to lookup `TelephonyNetwork` information using MCC and MNC, or `MobileCountries` using just MCC. It wraps `com.android.i18n.timezone.TelephonyNetworkFinder`.

## Architecture Overview
A service-like class obtained via `TelephonyLookup`. It delegates search logic to the i18n module.

## Data Model
*   **`mDelegate`**: `com.android.i18n.timezone.TelephonyNetworkFinder`.

## API Reference
*   **`findNetworkByMccMnc(String mcc, String mnc)`**: Searches for a network matching the given MCC/MNC. Returns `TelephonyNetwork` or `null`.
*   **`findCountriesByMcc(String mcc)`**: Searches for countries associated with a given MCC. Returns `MobileCountries` or `null`. This method is guarded by a feature flag (`Flags.telephonyLookupMccExtension()`).

## Java-to-C++ Translation Guide
*   **Lookup Logic**: The actual lookup algorithms (likely based on `telephonylookup.xml` or similar) reside in the delegate. C++ implementation should access the parsed data structures directly.
*   **Flag check**: The `Flags.telephonyLookupMccExtension()` check needs to be replicated or the configuration passed down.

## Implementation Risks
*   **Feature Flags**: Behavior changes based on `com.android.icu.Flags`.
