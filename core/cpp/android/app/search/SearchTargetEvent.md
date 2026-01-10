# SearchTargetEvent - Reverse Engineering Documentation

## Executive Summary
`SearchTargetEvent` captures user interactions (taps, drags, etc.) or lifecycle events related to search targets or the search surface.

## Architecture Overview
-   **Package**: `android.app.search`
-   **Type**: `Parcelable` class, `final`

## Data Model

| Field Name | Type | Description |
| :--- | :--- | :--- |
| `mTargetIds` | `List<String>` | IDs of affected targets. Non-null. |
| `mLocation` | `String` | Launch location/context. Nullable. |
| `mAction` | `int` | Event type constant (e.g., `ACTION_TAP`). |
| `mFlags` | `int` | Context flags (e.g., `FLAG_IME_SHOWN`). |

## Java-to-C++ Translation Guide

### Serialization (Parcelable)
1.  `mTargetIds` (List<String>):
    -   Java: `dest.writeStringList(mTargetIds)`
    -   Read: `parcel.readStringList(mTargetIds)` (into new ArrayList)
    -   C++: `parcel->writeString16Vector` (or equivalent for List<String>)
2.  `mLocation` (String): `writeString`
3.  `mAction` (int): `writeInt`
4.  `mFlags` (int): `writeInt`

## Questions for C++ Team
-   None.
