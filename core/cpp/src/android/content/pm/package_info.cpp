// package_info.cpp — android.content.pm.PackageInfo implementation
// Mirrors core/java/android/content/pm/PackageInfo.java

#include "android/content/pm/package_info.h"
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace android::content::pm {

// === Internal Parcel serialization helpers ===

// Simple binary buffer for Parcel-like serialization.
// Mirrors the Java writeToParcel() field order exactly.
// Format: each field is prefixed with a 1-byte type tag followed by the data.
// Type tags: 0=String, 1=StringArray, 2=int, 3=intArray, 4=long, 5=bool,
//            6=Object (1-byte presence + object data), 7=ObjectArray

namespace {

constexpr int32_t TAG_STRING   = 0;
constexpr int32_t TAG_STRING_A = 1;
constexpr int32_t TAG_INT      = 2;
constexpr int32_t TAG_INT_A    = 3;
constexpr int32_t TAG_LONG     = 4;
constexpr int32_t TAG_BOOL     = 5;
constexpr int32_t TAG_OBJECT   = 6;
constexpr int32_t TAG_OBJ_A    = 7;

// Write a 32-bit little-endian integer into the buffer at the current offset.
void write_int32(std::vector<uint8_t>& buf, int32_t val, size_t& off) {
    for (int i = 0; i < 4; ++i) {
        buf.push_back(static_cast<uint8_t>(val >> (i * 8)));
        ++off;
    }
}

// Write a 64-bit little-endian long into the buffer.
void write_int64(std::vector<uint8_t>& buf, int64_t val, size_t& off) {
    for (int i = 0; i < 8; ++i) {
        buf.push_back(static_cast<uint8_t>(val >> (i * 8)));
        ++off;
    }
}

// Read a 32-bit little-endian integer from the buffer.
int32_t read_int32(const std::vector<uint8_t>& buf, size_t& off) {
    int32_t val = 0;
    for (int i = 0; i < 4; ++i) {
        val |= static_cast<int32_t>(buf[off++]) << (i * 8);
    }
    return val;
}

// Read a 64-bit little-endian long from the buffer.
int64_t read_int64(const std::vector<uint8_t>& buf, size_t& off) {
    int64_t val = 0;
    for (int i = 0; i < 8; ++i) {
        val |= static_cast<int64_t>(buf[off++]) << (i * 8);
    }
    return val;
}

// Write a string (or nullopt) as: 1-byte presence + length(4B LE) + UTF-8 bytes.
void write_nullable_string(std::vector<uint8_t>& buf,
                           const std::optional<std::string_view>& opt,
                           size_t& off) {
    write_int32(buf, opt.has_value() ? 1 : 0, off);
    if (opt.has_value()) {
        std::string s(opt->begin(), opt->end());
        write_int32(buf, static_cast<int32_t>(s.size()), off);
        for (char c : s) {
            buf.push_back(static_cast<uint8_t>(c));
            ++off;
        }
    }
}

// Read a string (or nullopt) from the buffer.
std::optional<std::string_view> read_nullable_string(const std::vector<uint8_t>& buf,
                                                     size_t& off,
                                                     std::vector<char>& storage) {
    int32_t has = read_int32(buf, off);
    if (has == 0) return std::nullopt;
    int32_t len = read_int32(buf, off);
    storage.resize(len);
    for (int i = 0; i < len; ++i) {
        storage[i] = static_cast<char>(buf[off++]);
    }
    return std::string_view(storage.data(), static_cast<size_t>(len));
}

// Write an int array (or nullopt) as: 1-byte presence + length(4B LE) + int[] bytes.
void write_nullable_int_array(std::vector<uint8_t>& buf,
                              const std::optional<std::span<const int32_t>>& opt,
                              size_t& off) {
    write_int32(buf, opt.has_value() ? 1 : 0, off);
    if (opt.has_value()) {
        int32_t len = static_cast<int32_t>(opt->size());
        write_int32(buf, len, off);
        for (int32_t v : *opt) {
            write_int32(buf, v, off);
        }
    }
}

// Read an int array (or nullopt) from the buffer.
std::optional<std::span<const int32_t>> read_nullable_int_array(
    const std::vector<uint8_t>& buf, size_t& off,
    std::vector<int32_t>& storage) {
    int32_t has = read_int32(buf, off);
    if (has == 0) return std::nullopt;
    int32_t len = read_int32(buf, off);
    storage.resize(static_cast<size_t>(len));
    for (int i = 0; i < len; ++i) {
        storage[i] = read_int32(buf, off);
    }
    return std::span<const int32_t>(storage);
}

// Write a string array (or nullopt) as: 1-byte presence + length(4B LE) + strings.
void write_nullable_string_array(std::vector<uint8_t>& buf,
                                 const std::span<const std::string_view>& opt,
                                 size_t& off) {
    write_int32(buf, opt.empty() ? 0 : 1, off);
    int32_t len = static_cast<int32_t>(opt.size());
    write_int32(buf, len, off);
    for (const auto& sv : opt) {
        write_nullable_string(buf, sv, off);
    }
}

// Read a string array (or empty) from the buffer.
std::vector<std::string_view> read_nullable_string_array(
    const std::vector<uint8_t>& buf, size_t& off,
    std::vector<std::string>& str_storage) {
    int32_t has = read_int32(buf, off);
    std::vector<std::string_view> result;
    if (has == 0) return result;
    int32_t len = read_int32(buf, off);
    result.reserve(static_cast<size_t>(len));
    for (int i = 0; i < len; ++i) {
        auto opt = read_nullable_string(buf, off, str_storage);
        result.push_back(*opt);
    }
    return result;
}

// Write a typed object (or nullopt) as: 1-byte presence + object data.
// For PackageInfo, we serialize ApplicationInfo and SigningInfo as simple fields.
void write_nullable_object(std::vector<uint8_t>& buf, bool has_value, size_t& off) {
    write_int32(buf, has_value ? 1 : 0, off);
}

} // namespace

// === Version code methods ===

int64_t PackageInfo::long_version_code() const {
    return compose_long_version_code(version_code_major, version_code);
}

void PackageInfo::set_long_version_code(int64_t long_version_code) {
    version_code_major = static_cast<int32_t>(long_version_code >> 32);
    version_code = static_cast<int32_t>(long_version_code);
}

int64_t PackageInfo::compose_long_version_code(int32_t major, int32_t minor) {
    return (static_cast<int64_t>(major) << 32) |
           (static_cast<int64_t>(static_cast<uint32_t>(minor)));
}

// === Overlay package checks ===

bool PackageInfo::is_overlay_package() const {
    return overlay_target.has_value() && !overlay_target->empty();
}

bool PackageInfo::is_static_overlay_package() const {
    return overlay_target.has_value() && !overlay_target->empty() && overlay_is_static;
}

// === Archive time methods ===

int64_t PackageInfo::archive_time_millis() const {
    return archive_time_millis_;
}

void PackageInfo::set_archive_time_millis(int64_t value) {
    archive_time_millis_ = value;
}

// === APEX package name methods ===

std::optional<std::string_view> PackageInfo::apex_package_name() const {
    return apex_package_name_;
}

void PackageInfo::set_apex_package_name(std::string_view apex_package_name) {
    apex_package_name_ = apex_package_name;
}

// === toString ===

std::string PackageInfo::to_string() const {
    std::ostringstream oss;
    oss << "PackageInfo{"
        << "package_name='" << package_name << "', "
        << "version_code=" << version_code << ", "
        << "version_code_major=" << version_code_major << ", "
        << "install_location=" << static_cast<int32_t>(install_location) << ", "
        << "is_stub=" << is_stub << ", "
        << "core_app=" << core_app << ", "
        << "is_apex=" << is_apex << ", "
        << "is_active_apex=" << is_active_apex
        << "}";
    return oss.str();
}

// === describe_contents ===

int PackageInfo::describe_contents() const {
    return 0;
}

// === Parcel serialization ===

// Note: This is a simplified implementation that serializes all fields
// in Java field order to a memory buffer. The full implementation would
// write to a real Parcel object. See contract for exact field order.
void PackageInfo::write_to_parcel(void* parcel, int32_t) const {
    if (!parcel) return;
    auto* buf = static_cast<std::vector<uint8_t>*>(parcel);
    size_t off = 0;

    // Field order matches Java writeToParcel() exactly.

    // packageName
    write_nullable_string(*buf, package_name.empty() ? std::nullopt : std::optional<std::string_view>(package_name), off);

    // splitNames
    write_nullable_string_array(*buf, split_names, off);

    // versionCode
    write_int32(*buf, version_code, off);

    // versionCodeMajor
    write_int32(*buf, version_code_major, off);

    // versionName
    write_nullable_string(*buf, version_name, off);

    // baseRevisionCode
    write_int32(*buf, base_revision_code, off);

    // splitRevisionCodes
    write_nullable_int_array(*buf, split_revision_codes.empty() ? std::nullopt : std::optional<std::span<const int32_t>>(split_revision_codes), off);

    // sharedUserId
    write_nullable_string(*buf, shared_user_id, off);

    // sharedUserLabel
    write_int32(*buf, shared_user_label, off);

    // applicationInfo
    write_nullable_object(*buf, application_info.has_value(), off);

    // firstInstallTime
    write_int64(*buf, first_install_time, off);

    // lastUpdateTime
    write_int64(*buf, last_update_time, off);

    // gids
    write_nullable_int_array(*buf, gids, off);

    // activities, receivers, services, providers, instrumentation
    // (object arrays — presence flag only in simplified impl)
    write_nullable_object(*buf, activities.has_value(), off);
    write_nullable_object(*buf, receivers.has_value(), off);
    write_nullable_object(*buf, services.has_value(), off);
    write_nullable_object(*buf, providers.has_value(), off);
    write_nullable_object(*buf, instrumentation.has_value(), off);

    // permissions
    write_nullable_object(*buf, permissions.has_value(), off);

    // requestedPermissions
    write_nullable_object(*buf, requested_permissions.has_value(), off);

    // requestedPermissionsFlags
    write_nullable_object(*buf, requested_permissions_flags.has_value(), off);

    // signatures
    write_nullable_object(*buf, signatures.has_value(), off);

    // configPreferences
    write_nullable_object(*buf, config_preferences.has_value(), off);

    // reqFeatures
    write_nullable_object(*buf, req_features.has_value(), off);

    // featureGroups
    write_nullable_object(*buf, feature_groups.has_value(), off);

    // attributions
    write_nullable_object(*buf, attributions.has_value(), off);

    // installLocation
    write_int32(*buf, static_cast<int32_t>(install_location), off);

    // isStub
    write_int32(*buf, is_stub ? 1 : 0, off);

    // coreApp
    write_int32(*buf, core_app ? 1 : 0, off);

    // requiredForAllUsers
    write_int32(*buf, required_for_all_users ? 1 : 0, off);

    // restrictedAccountType
    write_nullable_string(*buf, restricted_account_type, off);

    // requiredAccountType
    write_nullable_string(*buf, required_account_type, off);

    // overlayTarget
    write_nullable_string(*buf, overlay_target, off);

    // overlayCategory
    write_nullable_string(*buf, overlay_category, off);

    // overlayPriority
    write_int32(*buf, overlay_priority, off);

    // mOverlayIsStatic
    write_int32(*buf, overlay_is_static ? 1 : 0, off);

    // compileSdkVersion
    write_int32(*buf, compile_sdk_version, off);

    // compileSdkVersionCodename
    write_nullable_string(*buf, compile_sdk_version_codename, off);

    // signingInfo
    write_nullable_object(*buf, signing_info.has_value(), off);

    // isApex
    write_int32(*buf, is_apex ? 1 : 0, off);

    // isActiveApex
    write_int32(*buf, is_active_apex ? 1 : 0, off);

    // mArchiveTimeMillis
    write_int64(*buf, archive_time_millis_, off);

    // mApexPackageName
    write_nullable_object(*buf, apex_package_name_.has_value(), off);
}

// === Parcel deserialization constructor ===

PackageInfo::PackageInfo(void* parcel)
    : archive_time_millis_(0), apex_package_name_(std::nullopt) {
    if (!parcel) return;
    const auto* buf = static_cast<const std::vector<uint8_t>*>(parcel);
    size_t off = 0;

    // Field order matches Java Parcel constructor exactly.

    // packageName
    {
        std::vector<char> storage;
        auto opt = read_nullable_string(*buf, off, storage);
        if (opt.has_value()) {
            // Store a copy to avoid dangling reference
            // In a real implementation, this would be managed differently
        }
    }

    // splitNames
    {
        std::vector<std::string> str_storage;
        auto result = read_nullable_string_array(*buf, off, str_storage);
        // split_names would be set from result
    }

    // versionCode
    version_code = read_int32(*buf, off);

    // versionCodeMajor
    version_code_major = read_int32(*buf, off);

    // versionName
    {
        std::vector<char> storage;
        auto opt = read_nullable_string(*buf, off, storage);
        if (opt.has_value()) {
            version_name = opt;
        }
    }

    // baseRevisionCode
    base_revision_code = read_int32(*buf, off);

    // splitRevisionCodes
    {
        std::vector<int32_t> storage;
        auto opt = read_nullable_int_array(*buf, off, storage);
        if (opt.has_value()) {
            split_revision_codes = *opt;
        }
    }

    // sharedUserId
    {
        std::vector<char> storage;
        auto opt = read_nullable_string(*buf, off, storage);
        if (opt.has_value()) {
            shared_user_id = opt;
        }
    }

    // sharedUserLabel
    shared_user_label = read_int32(*buf, off);

    // applicationInfo (presence flag only in simplified impl)
    {
        int32_t has = read_int32(*buf, off);
        (void)has;
    }

    // firstInstallTime
    first_install_time = read_int64(*buf, off);

    // lastUpdateTime
    last_update_time = read_int64(*buf, off);

    // gids
    {
        std::vector<int32_t> storage;
        auto opt = read_nullable_int_array(*buf, off, storage);
        if (opt.has_value()) {
            gids = opt;
        }
    }

    // activities, receivers, services, providers, instrumentation (presence only)
    {
        int32_t has = read_int32(*buf, off); (void)has;
        has = read_int32(*buf, off); (void)has;
        has = read_int32(*buf, off); (void)has;
        has = read_int32(*buf, off); (void)has;
        has = read_int32(*buf, off); (void)has;
    }

    // permissions
    {
        int32_t has = read_int32(*buf, off); (void)has;
    }

    // requestedPermissions
    {
        int32_t has = read_int32(*buf, off); (void)has;
    }

    // requestedPermissionsFlags
    {
        int32_t has = read_int32(*buf, off); (void)has;
    }

    // signatures
    {
        int32_t has = read_int32(*buf, off); (void)has;
    }

    // configPreferences
    {
        int32_t has = read_int32(*buf, off); (void)has;
    }

    // reqFeatures
    {
        int32_t has = read_int32(*buf, off); (void)has;
    }

    // featureGroups
    {
        int32_t has = read_int32(*buf, off); (void)has;
    }

    // attributions
    {
        int32_t has = read_int32(*buf, off); (void)has;
    }

    // installLocation
    install_location = static_cast<InstallLocation>(read_int32(*buf, off));

    // isStub
    is_stub = read_int32(*buf, off) != 0;

    // coreApp
    core_app = read_int32(*buf, off) != 0;

    // requiredForAllUsers
    required_for_all_users = read_int32(*buf, off) != 0;

    // restrictedAccountType
    {
        std::vector<char> storage;
        auto opt = read_nullable_string(*buf, off, storage);
        if (opt.has_value()) {
            restricted_account_type = opt;
        }
    }

    // requiredAccountType
    {
        std::vector<char> storage;
        auto opt = read_nullable_string(*buf, off, storage);
        if (opt.has_value()) {
            required_account_type = opt;
        }
    }

    // overlayTarget
    {
        std::vector<char> storage;
        auto opt = read_nullable_string(*buf, off, storage);
        if (opt.has_value()) {
            overlay_target = opt;
        }
    }

    // overlayCategory
    {
        std::vector<char> storage;
        auto opt = read_nullable_string(*buf, off, storage);
        if (opt.has_value()) {
            overlay_category = opt;
        }
    }

    // overlayPriority
    overlay_priority = read_int32(*buf, off);

    // mOverlayIsStatic
    overlay_is_static = read_int32(*buf, off) != 0;

    // compileSdkVersion
    compile_sdk_version = read_int32(*buf, off);

    // compileSdkVersionCodename
    {
        std::vector<char> storage;
        auto opt = read_nullable_string(*buf, off, storage);
        if (opt.has_value()) {
            compile_sdk_version_codename = opt;
        }
    }

    // signingInfo (presence flag only)
    {
        int32_t has = read_int32(*buf, off); (void)has;
    }

    // isApex
    is_apex = read_int32(*buf, off) != 0;

    // isActiveApex
    is_active_apex = read_int32(*buf, off) != 0;

    // mArchiveTimeMillis
    archive_time_millis_ = read_int64(*buf, off);

    // mApexPackageName
    {
        int32_t has = read_int32(*buf, off);
        if (has != 0) {
            std::vector<char> storage;
            auto opt = read_nullable_string(*buf, off, storage);
            if (opt.has_value()) {
                apex_package_name_ = opt;
            }
        }
    }
}

} // namespace android::content::pm

} // namespace android::content::pm
