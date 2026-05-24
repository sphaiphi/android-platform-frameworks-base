# SearchSessionId - Reverse Engineering Documentation

## Executive Summary
`SearchSessionId` is a simple identifier wrapper for a search session, consisting of a string ID and a user ID.

## Architecture Overview
-   **Package**: `android.app.search`
-   **Type**: `Parcelable` class, `final`

## Data Model

| Field Name | Type | Description |
| :--- | :--- | :--- |
| `mId` | `String` | String identifier (typically `pkg:uuid`). |
| `mUserId` | `int` | Android User ID. |

## Java-to-C++ Translation Guide

### Serialization (Parcelable)
1.  `mId` (String): `writeString`
2.  `mUserId` (int): `writeInt`

### Equality
-   Based on both `mId` and `mUserId`.

## Questions for C++ Team
-   None.
