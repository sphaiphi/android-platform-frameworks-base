# Data Model: port-package-info

This document defines the data model for the `port-package-info` feature, describing the entities and information extracted from Java source files to be represented in C++.

## Entities

### PackageInfo

Represents the complete public API of `android.content.pm.PackageInfo` from `core/java/android/content/pm/PackageInfo.java`.

#### Public Fields

| # | Java Type | Java Name | C++ Type | C++ Name | Notes |
|---|-----------|-----------|----------|----------|-------|
| 1 | `String` | `packageName` | `std::string_view` | `package_name` | `@NonNull` |
| 2 | `String[]` | `splitNames` | `std::span<const std::string_view>` | `split_names` | `@NonNull` |
| 3 | `int` | `versionCode` | `int32_t` | `version_code` | `@Deprecated` |
| 4 | `int` | `versionCodeMajor` | `int32_t` | `version_code_major` | `@hide` |
| 5 | `String` | `versionName` | `std::optional<std::string_view>` | `version_name` | `@Nullable` |
| 6 | `int` | `baseRevisionCode` | `int32_t` | `base_revision_code` | — |
| 7 | `int[]` | `splitRevisionCodes` | `std::span<const int32_t>` | `split_revision_codes` | `@NonNull` |
| 8 | `String` | `sharedUserId` | `std::optional<std::string_view>` | `shared_user_id` | `@Nullable` |
| 9 | `int` | `sharedUserLabel` | `int32_t` | `shared_user_label` | — |
| 10 | `ApplicationInfo` | `applicationInfo` | `std::optional<std::reference_wrapper<const ApplicationInfo>>` | `application_info` | `@Nullable` |
| 11 | `long` | `firstInstallTime` | `int64_t` | `first_install_time` | — |
| 12 | `long` | `lastUpdateTime` | `int64_t` | `last_update_time` | — |
| 13 | `int[]` | `gids` | `std::optional<std::span<const int32_t>>` | `gids` | `@Nullable`, requires `GET_GIDS` |
| 14 | `ActivityInfo[]` | `activities` | `std::optional<std::span<const ActivityInfo>>` | `activities` | `@Nullable`, requires `GET_ACTIVITIES` |
| 15 | `ActivityInfo[]` | `receivers` | `std::optional<std::span<const ActivityInfo>>` | `receivers` | `@Nullable`, requires `GET_RECEIVERS` |
| 16 | `ServiceInfo[]` | `services` | `std::optional<std::span<const ServiceInfo>>` | `services` | `@Nullable`, requires `GET_SERVICES` |
| 17 | `ProviderInfo[]` | `providers` | `std::optional<std::span<const ProviderInfo>>` | `providers` | `@Nullable`, requires `GET_PROVIDERS` |
| 18 | `InstrumentationInfo[]` | `instrumentation` | `std::optional<std::span<const InstrumentationInfo>>` | `instrumentation` | `@Nullable`, requires `GET_INSTRUMENTATION` |
| 19 | `PermissionInfo[]` | `permissions` | `std::optional<std::span<const PermissionInfo>>` | `permissions` | `@Nullable`, requires `GET_PERMISSIONS` |
| 20 | `String[]` | `requestedPermissions` | `std::optional<std::span<const std::string_view>>` | `requested_permissions` | `@Nullable` |
| 21 | `int[]` | `requestedPermissionsFlags` | `std::optional<std::span<const RequestedPermissionFlag>>` | `requested_permissions_flags` | `@Nullable` |
| 22 | `Attribution[]` | `attributions` | `std::optional<std::span<const Attribution>>` | `attributions` | `@Nullable`, requires `GET_ATTRIBUTIONS_LONG` |
| 23 | `Signature[]` | `signatures` | `std::optional<std::span<const Signature>>` | `signatures` | `@Deprecated`, `@Nullable` |
| 24 | `SigningInfo` | `signingInfo` | `std::optional<std::reference_wrapper<const SigningInfo>>` | `signing_info` | `@Nullable` |
| 25 | `ConfigurationInfo[]` | `configPreferences` | `std::optional<std::span<const ConfigurationInfo>>` | `config_preferences` | `@Nullable` |
| 26 | `FeatureInfo[]` | `reqFeatures` | `std::optional<std::span<const FeatureInfo>>` | `req_features` | `@Nullable` |
| 27 | `FeatureGroupInfo[]` | `featureGroups` | `std::optional<std::span<const FeatureGroupInfo>>` | `feature_groups` | `@Nullable` |
| 28 | `int` | `installLocation` | `InstallLocation` | `install_location` | Default: `INTERNAL_ONLY` |
| 29 | `boolean` | `isStub` | `bool` | `is_stub` | `@hide` |
| 30 | `boolean` | `coreApp` | `bool` | `core_app` | `@hide` |
| 31 | `boolean` | `requiredForAllUsers` | `bool` | `required_for_all_users` | `@hide` |
| 32 | `String` | `restrictedAccountType` | `std::optional<std::string_view>` | `restricted_account_type` | `@hide`, `@Nullable` |
| 33 | `String` | `requiredAccountType` | `std::optional<std::string_view>` | `required_account_type` | `@hide`, `@Nullable` |
| 34 | `String` | `overlayTarget` | `std::optional<std::string_view>` | `overlay_target` | `@hide`, `@Nullable` |
| 35 | `String` | `targetOverlayableName` | `std::optional<std::string_view>` | `target_overlayable_name` | `@hide`, `@Nullable` |
| 36 | `String` | `overlayCategory` | `std::optional<std::string_view>` | `overlay_category` | `@hide`, `@Nullable` |
| 37 | `int` | `overlayPriority` | `int32_t` | `overlay_priority` | `@hide` |
| 38 | `boolean` | `mOverlayIsStatic` | `bool` | `overlay_is_static` | `@hide` |
| 39 | `int` | `compileSdkVersion` | `int32_t` | `compile_sdk_version` | `@hide` |
| 40 | `String` | `compileSdkVersionCodename` | `std::optional<std::string_view>` | `compile_sdk_version_codename` | `@hide`, `@Nullable` |
| 41 | `boolean` | `isApex` | `bool` | `is_apex` | — |
| 42 | `boolean` | `isActiveApex` | `bool` | `is_active_apex` | `@hide` |

#### Private Fields

| Type | Name | C++ Type | C++ Name | Notes |
|------|------|----------|----------|-------|
| `long` | `mArchiveTimeMillis` | `int64_t` | `archive_time_millis` | Accessed via getter/setter |
| `String` | `mApexPackageName` | `std::optional<std::string_view>` | `apex_package_name` | `@Nullable`, accessed via getter/setter |

#### Static Constants

| Java Name | Value | C++ Name | C++ Type | Notes |
|-----------|-------|----------|----------|-------|
| `REQUESTED_PERMISSION_REQUIRED` | `0x00000001` | `REQUESTED_PERMISSION_REQUIRED` | `RequestedPermissionFlag` | `@removed` |
| `REQUESTED_PERMISSION_GRANTED` | `0x00000002` | `REQUESTED_PERMISSION_GRANTED` | `RequestedPermissionFlag` | — |
| `REQUESTED_PERMISSION_NEVER_FOR_LOCATION` | `0x00010000` | `REQUESTED_PERMISSION_NEVER_FOR_LOCATION` | `RequestedPermissionFlag` | — |
| `REQUESTED_PERMISSION_IMPLICIT` | `0x00000004` | `REQUESTED_PERMISSION_IMPLICIT` | `RequestedPermissionFlag` | — |
| `INSTALL_LOCATION_UNSPECIFIED` | `-1` | `UNSPECIFIED` | `InstallLocation` | `@hide` |
| `INSTALL_LOCATION_AUTO` | `0` | `AUTO` | `InstallLocation` | — |
| `INSTALL_LOCATION_INTERNAL_ONLY` | `1` | `INTERNAL_ONLY` | `InstallLocation` | — |
| `INSTALL_LOCATION_PREFER_EXTERNAL` | `2` | `PREFER_EXTERNAL` | `InstallLocation` | — |

#### Methods

| Java Method | Return | C++ Method | Return | Notes |
|-------------|--------|------------|--------|-------|
| `PackageInfo()` | — | `PackageInfo()` | — | Default constructor |
| `getLongVersionCode()` | `long` | `long_version_code()` | `int64_t` | Combines major+minor |
| `setLongVersionCode(long)` | `void` | `set_long_version_code(int64_t)` | `void` | Sets version code |
| `composeLongVersionCode(int, int)` | `long` | `compose_long_version_code(int32_t, int32_t)` | `int64_t` | Static, `@hide` |
| `isOverlayPackage()` | `boolean` | `is_overlay_package()` | `bool` | `@hide` |
| `isStaticOverlayPackage()` | `boolean` | `is_static_overlay_package()` | `bool` | `@hide` |
| `getArchiveTimeMillis()` | `long` | `archive_time_millis()` | `int64_t` | Flagged API |
| `setArchiveTimeMillis(long)` | `void` | `set_archive_time_millis(int64_t)` | `void` | `@hide` |
| `getApexPackageName()` | `String` | `apex_package_name()` | `std::optional<std::string_view>` | Flagged API |
| `setApexPackageName(String)` | `void` | `set_apex_package_name(std::string_view)` | `void` | `@hide` |
| `toString()` | `String` | `to_string()` | `std::string` | Override |
| `describeContents()` | `int` | `describe_contents()` | `int` | Returns 0 |
| `writeToParcel(Parcel, int)` | `void` | `write_to_parcel(Parcel&, int32_t)` | `void` | Override |

#### Strong Types

```cpp
enum class InstallLocation : int32_t {
    UNSPECIFIED = -1,
    AUTO = 0,
    INTERNAL_ONLY = 1,
    PREFER_EXTERNAL = 2,
};

enum class RequestedPermissionFlag : int32_t {
    REQUIRED = 0x00000001,
    GRANTED = 0x00000002,
    IMPLICIT = 0x00000004,
    NEVER_FOR_LOCATION = 0x00010000,
};
```

### Package

Represents a Java package and its associated metadata extracted from `package-info.java`.

- **Name**: The fully qualified package name (e.g., `android.os`).
- **Documentation**: The block comment text from `package-info.java`.
- **Annotations**: A collection of annotations present in the package.

### Annotation

Represents a Java annotation found in `package-info.java`.

- **Name**: The simple name of the annotation (e.g., `Deprecated`, `hide`).
- **Value/Metadata**: The content of the annotation (if any). In the C++ port, this is primarily represented as a comment.

## Relationships

- A **Package** contains zero or more **Annotations**.
- A **Package** has a single, primary **Documentation** block (may be empty).
- **PackageInfo** references other info types (`ApplicationInfo`, `ActivityInfo`, `ServiceInfo`, `ProviderInfo`, `PermissionInfo`, `SigningInfo`) by `std::reference_wrapper<const T>` or `std::span<const T>`.

## Validation Rules

- **Package Name**: Must follow standard Java package naming conventions (lowercase, dots).
- **Documentation**: Must be non-empty if present in the source.
- **Annotation Names**: Must be valid Java annotation names.
- **versionCode**: Must be non-negative.
- **installLocation**: Must be one of the defined `InstallLocation` enum values.

## State Transitions

N/A (This is a data representation model, not a state machine).
