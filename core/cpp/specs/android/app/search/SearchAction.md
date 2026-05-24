# SearchAction - Reverse Engineering Documentation

## Executive Summary
`SearchAction` is a complex Parcelable object representing a searchable action that can be executed. It contains metadata (ID, title, icon) and execution targets (Intent or PendingIntent).

## Architecture Overview
-   **Package**: `android.app.search`
-   **Type**: `Parcelable` class, `final`
-   **Role**: Represents an actionable result or suggestion.

## Detailed Functionality

### Constructors & Builder
-   **Constructor**: Private, used by Builder.
    -   **Validation**:
        -   `mId` and `mTitle` must be non-null.
        -   **Exclusive Intent Rule**: Checks that **either** `mPendingIntent` **or** `mIntent` is present, but **not both**, and **not neither**.
        -   Throws `IllegalStateException` if the intent rule is violated.
-   **Builder**: `SearchAction.Builder`
    -   Accumulates fields.
    -   `build()` calls the private constructor.

## Data Model

| Field Name | Type | Notes |
| :--- | :--- | :--- |
| `mId` | `String` | Unique ID. Non-null. |
| `mTitle` | `CharSequence` | Title text. Non-null. |
| `mIcon` | `Icon` | Graphic icon. Nullable. |
| `mSubtitle` | `CharSequence` | Subtitle text. Nullable. |
| `mContentDescription` | `CharSequence` | Accessibility description. Nullable. |
| `mPendingIntent` | `PendingIntent` | Action via PendingIntent. Nullable (mutually exclusive with mIntent). |
| `mIntent` | `Intent` | Action via Intent. Nullable (mutually exclusive with mPendingIntent). |
| `mUserHandle` | `UserHandle` | User associated with action. Nullable. |
| `mExtras` | `Bundle` | Extra data. Nullable. |

## Java-to-C++ Translation Guide

### Serialization (Parcelable)
Order of serialization in `writeToParcel`:

1.  `mId` (String): `writeString`
2.  `mTitle` (CharSequence): `TextUtils.writeToParcel` -> **C++ Note**: This usually serializes as a CharSequence token. If it's just a string, it might be `writeString16`. If it contains spans, it's complex. C++ implementation often assumes simple strings for these unless full CharSequence support is implemented.
3.  `mIcon` (Icon): `writeTypedObject` -> `parcel->writeParcelable(mIcon)`
4.  `mSubtitle` (CharSequence): `TextUtils.writeToParcel`
5.  `mContentDescription` (CharSequence): `TextUtils.writeToParcel`
6.  `mPendingIntent` (PendingIntent): `writeTypedObject`
7.  `mIntent` (Intent): `writeTypedObject`
8.  `mUserHandle` (UserHandle): `writeTypedObject`
9.  `mExtras` (Bundle): `writeTypedObject` (Note: Java uses `writeTypedObject` for Bundle here, not `writeBundle`. Check if this makes a difference in wire format. `writeTypedObject` writes a 1/0 flag then the object. `writeBundle` usually writes the bundle directly or null. Actually `writeTypedObject` for Bundle works because Bundle is Parcelable).

### Reading from Parcel
Matches write order.
-   `TextUtils.CHAR_SEQUENCE_CREATOR.createFromParcel(in)` is used for CharSequences.

## Implementation Risks
-   **TextUtils.writeToParcel**: This is a specific Android serialization format for CharSequences (handling SpannedStrings). C++ implementations often simplify this to reading a String, but if the sender sends a SpannedString, the wire format is different (Int token, then string, then span data).
    -   *Mitigation*: Check if the usage strictly implies simple strings or if rich text is allowed. The class uses `CharSequence`, so rich text is possible. C++ needs to handle the `TextUtils` wire format.
-   **Intent/PendingIntent Validation**: The "XOR" validation logic in the constructor must be replicated in C++ if C++ is creating these objects, or checked when receiving.

## Questions for C++ Team
-   Does the C++ `Parcel` reader support `TextUtils` CharSequence format?
