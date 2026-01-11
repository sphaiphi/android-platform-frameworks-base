# Intent - Reverse Engineering Documentation

## Executive Summary
`Intent` is a polymorphic messaging object used to request actions from other app components. It serves as the glue for Android's component-based architecture, facilitating Activity transitions, Service starts, and Broadcast distributions.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`, `Cloneable`.
- **Core Components:**
    - **Action**: String (e.g., `ACTION_VIEW`).
    - **Data/Type**: `Uri` and MIME type.
    - **Component**: Explicit `ComponentName` (skips resolution).
    - **Categories**: Metadata for filtering.
    - **Extras**: `Bundle` for arbitrary data.
    - **Flags**: Bitmask for runtime behavior (e.g., `FLAG_ACTIVITY_NEW_TASK`).

## Detailed Functionality

### Intent Resolution (Implicit vs Explicit)
- **Explicit**: `setComponent()` or `setClass()` is used. The system goes directly to that component.
- **Implicit**: Only action/data/categories are set. The `PackageManager` matches this against `IntentFilter`s in all installed manifests.

### URI Handling and Normalization
- **`setDataAndTypeAndNormalize`**: Ensures schemes and MIME types are lowercase to prevent matching failures due to casing.
- **Uri Permission Grants**: `FLAG_GRANT_READ_URI_PERMISSION` and `FLAG_GRANT_WRITE_URI_PERMISSION` allow an app to share data it owns with a target component without giving that component global permission to its provider.

### Security: Intent Redirection Protection
- **`CreatorTokenInfo` / `NestedIntentKey`**: Modern Android feature to track the "creator" of an intent. If an app receives an intent and "redirects" it (wraps it in another intent and sends it), the system uses these tokens to ensure the original creator had the permissions to perform the final action.
- **`collectExtraIntentKeys`**: Recursively scans `Extras` and `ClipData` for nested `Intent` objects to build a security map.

### Shell and Command Support
- **`parseCommandArgs`**: Logic used by the `am` (Activity Manager) shell command to construct intents from command-line flags (e.g., `-a`, `-d`, `-e`).

### URI Representation
- **`toUri` / `parseUri`**: Encodes the entire `Intent` object (Action, Data, Extras, etc.) into a single `intent://` or `android-app://` URI string.

## Data Model (Parceled Fields)
1. `mAction` (String8)
2. `mData` (Uri)
3. `mType` (String8)
4. `mIdentifier` (String8)
5. `mFlags` (int)
6. `mExtendedFlags` (int)
7. `mPackage` (String8)
8. `mComponent` (ComponentName)
9. `mSourceBounds` (Rect)
10. `mCategories` (ArraySet<String>)
11. `mSelector` (Intent)
12. `mClipData` (ClipData)
13. `mExtras` (Bundle)
14. `mCreatorTokenInfo` (Binder + Metadata)

## API Reference
- `public Intent setAction(String action)`
- `public Intent putExtra(String name, Parcelable value)`
- `public static Intent parseUri(String uri, int flags)`
- `public ComponentName resolveActivity(PackageManager pm)`

## Java-to-C++ Translation Guide
- **Parceling Order**: Must strictly match the Java `writeToParcel` / `readFromParcel` sequence for cross-language IPC.
- **String Interning**: Java uses `String.intern()` for actions and categories to save memory; C++ can use an `InternPool` or `std::string_view` with a backing store.
- **Recursion**: `fillIn` and security scanning are recursive; ensure protection against stack overflow for maliciously nested intents.

## Implementation Risks
- **Mutable vs Immutable**: `Intent` is mutable. In a multi-threaded C++ environment, defensive copying or mutex protection is required.
- **Bundle Compatibility**: The `mExtras` bundle must be compatible with the native `Bundle` / `PersistableBundle` implementation.