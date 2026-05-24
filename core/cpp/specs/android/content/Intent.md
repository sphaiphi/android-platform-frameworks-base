# android.content.Intent - Reverse Engineering Documentation

## Executive Summary
`Intent` is an abstract description of an operation to be performed. It is used to launch activities, services, and broadcasts. It acts as a messaging object between components.

## Architecture Overview
- **Structure**: Complex data holder with multiple optional fields.
- **Key Characteristics**:
    - **Explicit Intent**: Specifies a `ComponentName`.
    - **Implicit Intent**: Specifies an `action`, `data`, and/or `type`, allowing the system to resolve the target.

## Detailed Functionality

### Core Fields
- `mAction`: String (e.g., `ACTION_VIEW`).
- `mData`: `Uri` (e.g., `content://...`).
- `mType`: String (MIME type).
- `mIdentifier`: String.
- `mPackage`: String (Target package for resolution).
- `mComponent`: `ComponentName` (Target component).
- `mFlags`: int (Launch flags, e.g., `FLAG_ACTIVITY_NEW_TASK`).
- `mCategories`: Set of Strings.
- `mExtras`: `Bundle`.
- `mSourceBounds`: `Rect`.
- `mClipData`: `ClipData`.
- `mSelector`: `Intent` (Allows choosing a specific intent from a set).

### Parceling (Wire Format)
`Intent.writeToParcel` order:
1. `mAction`: `writeString8`
2. `mData`: `Uri.writeToParcel`
3. `mType`: `writeString8`
4. `mIdentifier`: `writeString8`
5. `mFlags`: `writeInt`
6. `mExtendedFlags`: `writeInt`
7. `mPackage`: `writeString8`
8. `mComponent`: `ComponentName.writeToParcel`
9. `mSourceBounds`: `writeInt(1)` then `writeToParcel` OR `writeInt(0)`
10. `mCategories`: `writeInt(size)` then `writeString8` for each OR `writeInt(0)`
11. `mSelector`: `writeInt(1)` then `writeToParcel` OR `writeInt(0)`
12. `mClipData`: `writeInt(1)` then `writeToParcel` OR `writeInt(0)`
13. `mContentUserHint`: `writeInt`
14. `mExtras`: `writeBundle`
15. `mOriginalIntent`: `writeInt(1)` then `writeToParcel` OR `writeInt(0)`
16. (Optional) `mCreatorTokenInfo`: Based on `preventIntentRedirect()` flag.

## Data Model
- `action`: `std::string`
- `data`: `android::net::Uri`
- `type`: `std::string`
- `identifier`: `std::string`
- `package`: `std::string`
- `component`: `android::content::ComponentName`
- `flags`: `int32_t`
- `categories`: `std::set<std::string>`
- `extras`: `android::os::Bundle`
- `sourceBounds`: `android::graphics::Rect`
- `clipData`: `android::content::ClipData`
- `selector`: `std::unique_ptr<Intent>`

## API Reference
- `setAction(String)`, `getAction()`
- `setData(Uri)`, `getData()`
- `setType(String)`, `getType()`
- `setPackage(String)`, `getPackage()`
- `setComponent(ComponentName)`, `getComponent()`
- `addCategory(String)`, `removeCategory(String)`, `hasCategory(String)`
- `setFlags(int)`, `addFlags(int)`, `getFlags()`
- `putExtra(String, ...)`, `get*Extra(String)`
- `filterEquals(Intent)`: Compares only fields used for intent resolution (Action, Data, Type, Package, Component, Categories).

## Java-to-C++ Translation Guide
- **Recursion**: `Selector` and `OriginalIntent` are recursive `Intent` objects. Use `std::unique_ptr` or `std::shared_ptr`.
- **Error Handling**: Use `std::expected` for data retrieval where type mismatch or missing fields might occur.
- **Parceling Order**: Must strictly match the Java `writeToParcel` / `readFromParcel` sequence for cross-language IPC.

## Test Cases & Validation
- Setting/Getting all fields.
- `filterEquals` with various combinations.
- Parcel round-trip with complex nested data (extras, clipdata, selector).

## Implementation Risks
- **Bundle Compatibility**: Ensure C++ `Bundle` can handle all data types present in Java `Intent` extras.
- **MIME Type Normalization**: Java performs some normalization on MIME types.
- **Recursion Depth**: Nested intents could theoretically cause issues, though unlikely in practice.
