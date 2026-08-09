# Contract: PackageInfo Header

## Overview

This contract defines the public API surface of the C++ `android::content::pm::PackageInfo`
class, ensuring API compatibility with the Java `android.content.pm.PackageInfo` reference
implementation in `core/java/android/content/pm/PackageInfo.java`.

## Header Path

```
core/cpp/include/android/content/pm/package_info.h
```

## Class Declaration

```cpp
#pragma once

#include <cstdint>
#include <optional>
#include <string_view>
#include <string>
#include <span>
#include <utility>

// Forward declarations for referenced types
namespace android { namespace content { namespace pm {
    class ApplicationInfo;
    class ActivityInfo;
    class ServiceInfo;
    class ProviderInfo;
    class InstrumentationInfo;
    class PermissionInfo;
    class ConfigurationInfo;
    class FeatureInfo;
    class FeatureGroupInfo;
    class SigningInfo;
    struct Attribution;
    class Signature;
}}}

namespace android::content::pm {

// Strong type for install location constants
enum class InstallLocation : int32_t {
    UNSPECIFIED = -1,   // @hide
    AUTO = 0,
    INTERNAL_ONLY = 1,
    PREFER_EXTERNAL = 2,
};

// Strong type for requested permission flags
enum class RequestedPermissionFlag : int32_t {
    REQUIRED = 0x00000001,         // @removed
    GRANTED = 0x00000002,
    IMPLICIT = 0x00000004,
    NEVER_FOR_LOCATION = 0x00010000,
};

/**
 * @brief Overall information about the contents of a package.
 *
 * Mirrors android.content.pm.PackageInfo. This corresponds to all of the
 * information collected from AndroidManifest.xml.
 */
class PackageInfo {
public:
    // === Public Fields (mirroring Java package fields) ===

    /// The name of this package. From the <manifest> tag's "name" attribute.
    std::string_view package_name;

    /// The names of any installed split APKs for this package.
    std::span<const std::string_view> split_names;

    /// @deprecated Use getLongVersionCode() instead
    int32_t version_code;

    /// @hide The major version number of this package.
    int32_t version_code_major;

    /// The version name of this package, or std::nullopt if there was none.
    std::optional<std::string_view> version_name;

    /// The revision number of the base APK for this package.
    int32_t base_revision_code;

    /// The revision number of any split APKs. Indexes map 1:1 against split_names.
    std::span<const int32_t> split_revision_codes;

    /// The shared user ID name, or std::nullopt.
    std::optional<std::string_view> shared_user_id;

    /// The shared user ID label (resource ID).
    int32_t shared_user_label;

    /// Information from the <application> tag, or std::nullopt.
    std::optional<std::reference_wrapper<const ApplicationInfo>> application_info;

    /// The time at which the app was first installed (System.currentTimeMillis).
    int64_t first_install_time;

    /// The time at which the app was last updated (System.currentTimeMillis).
    int64_t last_update_time;

    /// Kernel group-IDs, or std::nullopt (requires GET_GIDS flag).
    std::optional<std::span<const int32_t>> gids;

    /// ActivityInfo[] for <activity> tags, or std::nullopt (requires GET_ACTIVITIES).
    std::optional<std::span<const ActivityInfo>> activities;

    /// ActivityInfo[] for <receiver> tags, or std::nullopt (requires GET_RECEIVERS).
    std::optional<std::span<const ActivityInfo>> receivers;

    /// ServiceInfo[] for <service> tags, or std::nullopt (requires GET_SERVICES).
    std::optional<std::span<const ServiceInfo>> services;

    /// ProviderInfo[] for <provider> tags, or std::nullopt (requires GET_PROVIDERS).
    std::optional<std::span<const ProviderInfo>> providers;

    /// InstrumentationInfo[] for <instrumentation> tags, or std::nullopt.
    std::optional<std::span<const InstrumentationInfo>> instrumentation;

    /// PermissionInfo[] for <permission> tags, or std::nullopt (requires GET_PERMISSIONS).
    std::optional<std::span<const PermissionInfo>> permissions;

    /// String[] for <uses-permission> tags, or std::nullopt.
    std::optional<std::span<const std::string_view>> requested_permissions;

    /// int[] of flags for requested permissions, or std::nullopt.
    std::optional<std::span<const RequestedPermissionFlag>> requested_permissions_flags;

    /// Attribution[] for <attribution> tags, or std::nullopt.
    std::optional<std::span<const Attribution>> attributions;

    /// @deprecated use signingInfo instead
    /// @hide
    std::optional<std::span<const Signature>> signatures;

    /// Signing information, or std::nullopt (requires GET_SIGNING_CERTIFICATES).
    std::optional<std::reference_wrapper<const SigningInfo>> signing_info;

    /// ConfigurationInfo[] for <uses-configuration> tags, or std::nullopt.
    std::optional<std::span<const ConfigurationInfo>> config_preferences;

    /// FeatureInfo[] for requested features.
    std::optional<std::span<const FeatureInfo>> req_features;

    /// FeatureGroupInfo[] for feature groups.
    std::optional<std::span<const FeatureGroupInfo>> feature_groups;

    /// Install location requested by the package. Default: INTERNAL_ONLY.
    InstallLocation install_location = InstallLocation::INTERNAL_ONLY;

    /// @hide Whether or not the package is a stub.
    bool is_stub;

    /// @hide Whether the app is a core app.
    bool core_app;

    /// @hide Whether this app is required for all users.
    bool required_for_all_users;

    /// @hide The restricted account authenticator type.
    std::optional<std::string_view> restricted_account_type;

    /// @hide The required account type.
    std::optional<std::string_view> required_account_type;

    /// @hide Package this package will overlay, or std::nullopt.
    std::optional<std::string_view> overlay_target;

    /// @hide Overlayable set of elements name, or std::nullopt.
    std::optional<std::string_view> target_overlayable_name;

    /// @hide The overlay category.
    std::optional<std::string_view> overlay_category;

    /// @hide
    int32_t overlay_priority;

    /// @hide Whether the overlay is static.
    bool overlay_is_static;

    /// @hide The user-visible SDK version.
    int32_t compile_sdk_version;

    /// @hide The development codename.
    std::optional<std::string_view> compile_sdk_version_codename;

    /// Whether the package is an APEX package.
    bool is_apex;

    /// @hide Whether this is an active APEX package.
    bool is_active_apex;

    // === Private Fields (accessed via getter/setter) ===

    /// @hide The time at which the app was archived (System.currentTimeMillis).
    int64_t archive_time_millis_ = 0;

    /// @hide Package name of the APEX, or std::nullopt.
    std::optional<std::string> apex_package_name_;

    // === Static Constants ===

    static constexpr RequestedPermissionFlag REQUESTED_PERMISSION_REQUIRED =
        RequestedPermissionFlag::REQUIRED;
    static constexpr RequestedPermissionFlag REQUESTED_PERMISSION_GRANTED =
        RequestedPermissionFlag::GRANTED;
    static constexpr RequestedPermissionFlag REQUESTED_PERMISSION_NEVER_FOR_LOCATION =
        RequestedPermissionFlag::NEVER_FOR_LOCATION;
    static constexpr RequestedPermissionFlag REQUESTED_PERMISSION_IMPLICIT =
        RequestedPermissionFlag::IMPLICIT;

    static constexpr InstallLocation INSTALL_LOCATION_UNSPECIFIED =
        InstallLocation::UNSPECIFIED;
    static constexpr InstallLocation INSTALL_LOCATION_AUTO =
        InstallLocation::AUTO;
    static constexpr InstallLocation INSTALL_LOCATION_INTERNAL_ONLY =
        InstallLocation::INTERNAL_ONLY;
    static constexpr InstallLocation INSTALL_LOCATION_PREFER_EXTERNAL =
        InstallLocation::PREFER_EXTERNAL;

    // === Methods ===

    PackageInfo() = default;

    /// Returns versionCode and versionCodeMajor combined as a single long value.
    int64_t long_version_code() const;

    /// Sets the full version code, updating versionCode with the lower bits.
    void set_long_version_code(int64_t long_version_code);

    /// Static: Compose major and minor version codes into a single long.
    static int64_t compose_long_version_code(int32_t major, int32_t minor);

    /// @hide Returns true if this is a valid Runtime Overlay package.
    bool is_overlay_package() const;

    /// @hide Returns true if this is a valid static Runtime Overlay package.
    bool is_static_overlay_package() const;

    /// Returns the time at which the app was archived for the user.
    int64_t archive_time_millis() const;

    /// @hide
    void set_archive_time_millis(int64_t value);

    /// Returns the package name of the APEX, or std::nullopt.
    std::optional<std::string_view> apex_package_name() const;

    /// @hide
    void set_apex_package_name(std::string_view apex_package_name);

    /// Returns a string representation.
    std::string to_string() const;

    /// Returns 0 (describeContents equivalent).
    int describe_contents() const;

    /// Writes this PackageInfo to a Parcel (Parcelable equivalent).
    void write_to_parcel(void& parcel, int32_t parcelable_flags) const;

    // Parcel constructor (for deserialization)
    explicit PackageInfo(void& parcel);
};

} // namespace android::content::pm
```

## Type Mapping Rules

| Java Type | C++ Type | Constraint |
|-----------|----------|------------|
| `String` (non-null) | `std::string_view` | Non-optional, requires valid source |
| `String` (nullable) | `std::optional<std::string_view>` | Empty optional for null |
| `String[]` (non-null) | `std::span<const std::string_view>` | Empty span for empty array |
| `String[]` (nullable) | `std::optional<std::span<const std::string_view>>` | Empty optional for null |
| `int[]` (non-null) | `std::span<const int32_t>` | Empty span for empty array |
| `int[]` (nullable) | `std::optional<std::span<const int32_t>>` | Empty optional for null |
| `long` | `int64_t` | Fixed-width |
| `boolean` / `boolean` | `bool` | Direct mapping |
| `@Nullable T` | `std::optional<T>` | Type-system enforced |
| `@NonNull T` | `T` | Type-system enforced |
| `@Deprecated` | `// @Deprecated` | Documentation marker |
| `@hide` | `// @hide` | Documentation marker |

## Field Count

- **Public fields**: 42 (matching Java PackageInfo)
- **Private fields**: 2 (mArchiveTimeMillis, mApexPackageName — accessed via getter/setter)
- **Static constants**: 8 (4 permission flags + 4 install locations)
- **Instance methods**: 10 (version code, overlay checks, archive time, apex name, toString, describeContents, writeToParcel)
- **Static methods**: 1 (composeLongVersionCode)

## Parcel Serialization Contract

The `writeToParcel` / `createFromParcel` methods must preserve the exact field
order of the Java implementation to maintain ABI compatibility with existing
serialized data:

1. packageName (String8)
2. splitNames (String8[])
3. versionCode (int32)
4. versionCodeMajor (int32)
5. versionName (String8)
6. baseRevisionCode (int32)
7. splitRevisionCodes (int32[])
8. sharedUserId (String8)
9. sharedUserLabel (int32)
10. applicationInfo (Parcelable, nullable)
11. firstInstallTime (int64)
12. lastUpdateTime (int64)
13. gids (int32[])
14. activities (Parcelable[], nullable)
15. receivers (Parcelable[], nullable)
16. services (Parcelable[], nullable)
17. providers (Parcelable[], nullable)
18. instrumentation (Parcelable[], nullable)
19. permissions (Parcelable[], nullable)
20. requestedPermissions (String8[])
21. requestedPermissionsFlags (int32[])
22. signatures (Parcelable[], nullable, @Deprecated)
23. configPreferences (Parcelable[], nullable)
24. reqFeatures (Parcelable[], nullable)
25. featureGroups (Parcelable[], nullable)
26. attributions (Parcelable[], nullable)
27. installLocation (int32)
28. isStub (boolean)
29. coreApp (boolean)
30. requiredForAllUsers (boolean)
31. restrictedAccountType (String8)
32. requiredAccountType (String8)
33. overlayTarget (String8)
34. overlayCategory (String8)
35. overlayPriority (int32)
36. mOverlayIsStatic (boolean)
37. compileSdkVersion (int32)
38. compileSdkVersionCodename (String8)
39. signingInfo (Parcelable, nullable)
40. isApex (boolean)
41. isActiveApex (boolean)
42. mArchiveTimeMillis (int64)
43. mApexPackageName (String8, nullable)
