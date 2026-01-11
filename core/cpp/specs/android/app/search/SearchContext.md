# SearchContext - Reverse Engineering Documentation

## Executive Summary
`SearchContext` defines the environment and expectations for a search session, including expected result types, timeout constraints, and client package identification.

## Architecture Overview
-   **Package**: `android.app.search`
-   **Type**: `Parcelable` class, `final`
-   **Role**: Configuration object passed during `SearchSession` creation.

## Detailed Functionality

### State Management
-   **Immutability**: Fields are final, except `mPackageName` which has a package-private setter `setPackageName`.
-   **Result Types**: Bitmask integer (`mResultTypes`) combining flags like `RESULT_TYPE_APPLICATION`, `RESULT_TYPE_SHORTCUT`, etc. (Defined in `SearchTarget`).

## Data Model

| Field Name | Type | Description |
| :--- | :--- | :--- |
| `mResultTypes` | `int` | Bitmask of expected result types. |
| `mTimeoutMillis` | `int` | Timeout for the first result (ms). |
| `mPackageName` | `String` | Package name of the client. Nullable (initially), set by `SearchSession`. |
| `mExtras` | `Bundle` | Additional configuration. Non-null. |

## Java-to-C++ Translation Guide

### Serialization (Parcelable)
Order of serialization:
1.  `mResultTypes` (int): `writeInt`
2.  `mTimeoutMillis` (int): `writeInt`
3.  `mPackageName` (String): `writeString`
4.  `mExtras` (Bundle): `writeBundle`

### Reading from Parcel
Matches write order.

## Implementation Risks
-   **Package Name Injection**: In Java, `SearchSession` sets the package name after construction but before IPC. C++ clients must ensure this field is populated correctly before sending to the service to allow for server-side validation/allowlisting.

## Questions for C++ Team
-   None.
