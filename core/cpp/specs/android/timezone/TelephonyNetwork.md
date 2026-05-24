# TelephonyNetwork - Reverse Engineering Documentation

## Executive Summary
`TelephonyNetwork` represents specific identification information for a telephony network, including its MCC, MNC, and the country ISO code where it operates. It is a wrapper around `com.android.i18n.timezone.TelephonyNetwork`.

## Architecture Overview
Simple data carrier class wrapper.

## Data Model
*   **`mDelegate`**: `com.android.i18n.timezone.TelephonyNetwork`.

## API Reference
*   **`getMcc()`**: Returns the Mobile Country Code (String).
*   **`getMnc()`**: Returns the Mobile Network Code (String).
*   **`getCountryIsoCode()`**: Returns the ISO 3166 alpha-2 country code (String).
*   **`equals(Object)`** / **`hashCode()`**: Delegated to the underlying object.

## Java-to-C++ Translation Guide
*   **Struct**: Can be represented as a simple struct or class with accessors in C++.
*   **Comparison**: Implement `operator==`.

## Implementation Risks
None specific to the wrapper logic itself.
