# CredentialProviderInfo - Reverse Engineering Documentation

## Executive Summary
`CredentialProviderInfo` contains metadata about a specific credential provider service, including its capabilities, settings UI info, and service properties.

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: Used in service discovery and settings to display available providers.

## Detailed Functionality

### Core Fields
- `mServiceInfo` (`ServiceInfo`): Standard Android Service metadata.
- `mCapabilities` (`List<String>`): List of credential types this provider supports.
- `mOverrideLabel` (CharSequence): For testing/overrides.
- `mSettingsSubtitle`, `mSettingsActivity`: UI metadata for the settings screen.
- `mIsSystemProvider` (boolean): True if it's a system provider.
- `mIsEnabled` (boolean): True if user enabled it.
- `mIsPrimary` (boolean): True if it's a primary provider.

### Methods
- `hasCapability(String type)`: Checks if type is supported.
- `getServiceIcon(Context)`, `getLabel(Context)`: UI helpers.
- `getComponentName()`: Derived from `ServiceInfo`.

## Java-Specific Notes
- **`ServiceInfo`**: Heavy Android framework object. C++ might hold a lighter representation or a serialized blob if it doesn't need full access.
- **`CharSequence`**: String handling.
- **`Drawable`**: `getServiceIcon` returns a Java Drawable. C++ layer likely cannot produce this directly without JNI or higher-level graphics resources.

## Java-to-C++ Translation Guide
- **Capabilities**: `std::vector<std::string>`.
- **Flags**: `isSystemProvider`, `isEnabled`, `isPrimary`.
- **ServiceInfo**: This is the tricky part. In C++, you might only store the `ComponentName` and maybe the `meta-data` Bundle, rather than the full `ServiceInfo` object unless necessary.

## Data Model
```cpp
struct CredentialProviderInfo {
    ServiceInfo serviceInfo; // or componentName + metadata
    std::vector<std::string> capabilities;
    bool isSystemProvider;
    bool isEnabled;
    bool isPrimary;
    std::string settingsSubtitle;
    std::string settingsActivity;
};
```
