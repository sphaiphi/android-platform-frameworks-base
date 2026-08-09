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
    void write_to_parcel(void* parcel, int32_t parcelable_flags) const;

    // Parcel constructor (for deserialization)
    explicit PackageInfo(void* parcel);
};

} // namespace android::content::pm
