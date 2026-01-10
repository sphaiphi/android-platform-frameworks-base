# MobileCountries - Reverse Engineering Documentation

## Executive Summary
`MobileCountries` encapsulates information about countries associated with a telephony network, specifically mapping Mobile Country Codes (MCC) to ISO country codes. It acts as a wrapper around `com.android.i18n.timezone.MobileCountries`.

## Architecture Overview
This class sits in the `android.timezone` package and serves as a facade for the implementation located in the `com.android.i18n.timezone` package. It provides read-only access to telephony country data.

## Data Model
*   **`mDelegate`**: `com.android.i18n.timezone.MobileCountries`. The delegate object that holds the actual data logic.

## API Reference
*   **`getMcc()`**: Returns the Mobile Country Code (MCC) as a String.
*   **`getCountryIsoCodes()`**: Returns a `Set<String>` of ISO 3166 alpha-2 country codes associated with the MCC.
*   **`getDefaultCountryIsoCode()`**: Returns the default ISO country code for the network.

## Java-to-C++ Translation Guide
This class is a thin wrapper.
*   **Delegate**: In C++, interact with the native provider of mobile country data.
*   **Types**:
    *   `String` -> `std::string`
    *   `Set<String>` -> `std::unordered_set<std::string>` or `std::vector<std::string>` depending on usage requirements.

## Implementation Risks
*   **Delegate Availability**: Depends on `com.android.i18n.timezone` classes being available at runtime.
