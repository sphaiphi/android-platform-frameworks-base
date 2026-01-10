# SearchTarget - Reverse Engineering Documentation

## Executive Summary
`SearchTarget` is the core data structure representing a single search result. It is highly polymorphic, capable of holding App info, Shortcuts, Slices, Widgets, or custom `SearchAction`s, along with layout hints and metadata.

## Architecture Overview
-   **Package**: `android.app.search`
-   **Type**: `Parcelable` class, `final`

## Detailed Functionality

### Constants
-   **Result Types**: Bit flags (e.g., `RESULT_TYPE_APPLICATION`, `RESULT_TYPE_SHORTCUT`).
-   **Layout Types**: Strings (e.g., "icon", "icon_row").

## Data Model

| Field Name | Type | Description |
| :--- | :--- | :--- |
| `mResultType` | `int` | Type of result. |
| `mLayoutType` | `String` | UI layout hint. Non-null. |
| `mId` | `String` | Unique ID. Non-null. |
| `mParentId` | `String` | Grouping ID. Nullable. |
| `mScore` | `float` | Relevance score (0.0 - 1.0). |
| `mHidden` | `boolean` | Visibility flag. |
| `mPackageName` | `String` | Source package. Non-null. |
| `mUserHandle` | `UserHandle` | Associated user. Non-null. |
| `mSearchAction` | `SearchAction` | Custom action data. Nullable. |
| `mShortcutInfo` | `ShortcutInfo` | Shortcut data. Nullable. |
| `mAppWidgetProviderInfo` | `AppWidgetProviderInfo` | Widget data. Nullable. |
| `mSliceUri` | `Uri` | Slice URI. Nullable. |
| `mExtras` | `Bundle` | Extra data. Non-null. |

## Java-to-C++ Translation Guide

### Serialization (Parcelable)
**Strict Order**:
1.  `mResultType` (int)
2.  `mLayoutType` (String)
3.  `mId` (String)
4.  `mParentId` (String)
5.  `mScore` (float)
6.  `mHidden` (boolean)
7.  `mPackageName` (String)
8.  `mUserHandle` (UserHandle - specifically `writeInt(getIdentifier())` on write, but `UserHandle.of(readInt())` on read. **Wait**, checking code:
    -   Write: `parcel.writeInt(mUserHandle.getIdentifier());`
    -   Read: `mUserHandle = UserHandle.of(parcel.readInt());`
    -   *Crucial Note*: It does **not** use `writeTypedObject(UserHandle)`. It manually writes the integer ID.
9.  `mSearchAction` (SearchAction - `writeTypedObject`)
10. `mShortcutInfo` (ShortcutInfo - `writeTypedObject`)
11. `mAppWidgetProviderInfo` (AppWidgetProviderInfo - `writeTypedObject`)
12. `mSliceUri` (Uri - `writeTypedObject`)
13. `mExtras` (Bundle - `writeBundle` with classloader)

## Implementation Risks
-   **UserHandle Serialization**: The code deviates from standard `writeTypedObject` for `UserHandle`. It sends raw integer ID. C++ must match this exactly.
-   **Bundle ClassLoader**: `readBundle` uses `getClass().getClassLoader()`. This suggests the Bundle might contain custom objects (Parcelables) from the framework.

## Questions for C++ Team
-   None.
