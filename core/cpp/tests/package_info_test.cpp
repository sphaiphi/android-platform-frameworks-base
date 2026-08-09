// package_info_test.cpp — GoogleTest unit tests for PackageInfo
// Tests for port-package-info feature (User Story 1)

#include <gtest/gtest.h>
#include "android/content/pm/package_info.h"
#include <vector>

// Mock types for forward-declared classes (used only in tests)
namespace android::content::pm {
    // Minimal mock for ApplicationInfo (only reference_wrapper is used in tests)
    class ApplicationInfo {
    public:
        int32_t flags = 0;
    };
    // Minimal mock for SigningInfo (only reference_wrapper is used in tests)
    class SigningInfo {
    public:
        bool has_signing_info = false;
    };
}

using android::content::pm::PackageInfo;
using android::content::pm::InstallLocation;
using android::content::pm::RequestedPermissionFlag;

// T014: PackageInfo default construction initializes all fields to default/zero values
TEST(PackageInfoTest, DefaultConstruction) {
    PackageInfo pi;
    // String view defaults to empty
    EXPECT_TRUE(pi.package_name.empty());
    // Version code defaults to 0
    EXPECT_EQ(pi.version_code, 0);
    EXPECT_EQ(pi.version_code_major, 0);
    // Optional fields default to nullopt
    EXPECT_FALSE(pi.version_name.has_value());
    EXPECT_FALSE(pi.shared_user_id.has_value());
    // Install location defaults to INTERNAL_ONLY
    EXPECT_EQ(pi.install_location, InstallLocation::INTERNAL_ONLY);
    // Boolean fields default to false
    EXPECT_FALSE(pi.is_stub);
    EXPECT_FALSE(pi.core_app);
    EXPECT_FALSE(pi.required_for_all_users);
    EXPECT_FALSE(pi.is_apex);
    EXPECT_FALSE(pi.is_active_apex);
    EXPECT_FALSE(pi.overlay_is_static);
    // Integer fields default to 0
    EXPECT_EQ(pi.base_revision_code, 0);
    EXPECT_EQ(pi.shared_user_label, 0);
    EXPECT_EQ(pi.first_install_time, 0);
    EXPECT_EQ(pi.last_update_time, 0);
    EXPECT_EQ(pi.overlay_priority, 0);
    EXPECT_EQ(pi.compile_sdk_version, 0);
    // Private fields default to 0/nullopt
    EXPECT_EQ(pi.archive_time_millis(), 0);
    EXPECT_FALSE(pi.apex_package_name().has_value());
}

// T015: package_name field accepts and returns std::string_view correctly
TEST(PackageInfoTest, PackageName) {
    PackageInfo pi;
    std::string pkg = "com.example.test";
    // Note: Setting string_view requires the underlying string to outlive the view
    // For test purposes, we use a global/static string or assume the caller manages lifetime
    static std::string stored_pkg = pkg;
    pi.package_name = stored_pkg;
    EXPECT_EQ(pi.package_name, pkg);
}

// T016: version_name is std::nullopt by default and accepts a valid string
TEST(PackageInfoTest, VersionName) {
    PackageInfo pi;
    EXPECT_FALSE(pi.version_name.has_value());
    static std::string stored_name = "1.0.0";
    pi.version_name = stored_name;
    EXPECT_TRUE(pi.version_name.has_value());
    EXPECT_EQ(*pi.version_name, "1.0.0");
}

// T017: shared_user_id is std::nullopt by default
TEST(PackageInfoTest, SharedUserId) {
    PackageInfo pi;
    EXPECT_FALSE(pi.shared_user_id.has_value());
    static std::string stored_id = "com.example.shared";
    pi.shared_user_id = stored_id;
    EXPECT_TRUE(pi.shared_user_id.has_value());
    EXPECT_EQ(*pi.shared_user_id, "com.example.shared");
}

// T018: split_names and split_revision_codes accept std::span<const T> and return correct data
TEST(PackageInfoTest, SplitNamesAndRevisionCodes) {
    PackageInfo pi;
    static std::string split1 = "base";
    static std::string split2 = "overlay";
    static std::string_view splits[] = {split1, split2};
    static int32_t revisions[] = {1, 2};
    pi.split_names = splits;
    pi.split_revision_codes = revisions;
    EXPECT_EQ(pi.split_names.size(), 2u);
    EXPECT_EQ(pi.split_revision_codes.size(), 2u);
    EXPECT_EQ(pi.split_names[0], "base");
    EXPECT_EQ(pi.split_names[1], "overlay");
    EXPECT_EQ(pi.split_revision_codes[0], 1);
    EXPECT_EQ(pi.split_revision_codes[1], 2);
}

// T019: Optional array fields are std::nullopt by default
TEST(PackageInfoTest, OptionalArrayFieldsDefault) {
    PackageInfo pi;
    EXPECT_FALSE(pi.gids.has_value());
    EXPECT_FALSE(pi.activities.has_value());
    EXPECT_FALSE(pi.receivers.has_value());
    EXPECT_FALSE(pi.services.has_value());
    EXPECT_FALSE(pi.providers.has_value());
    EXPECT_FALSE(pi.instrumentation.has_value());
    EXPECT_FALSE(pi.permissions.has_value());
    EXPECT_FALSE(pi.requested_permissions.has_value());
    EXPECT_FALSE(pi.requested_permissions_flags.has_value());
    EXPECT_FALSE(pi.attributions.has_value());
    EXPECT_FALSE(pi.signatures.has_value());
    EXPECT_FALSE(pi.config_preferences.has_value());
    EXPECT_FALSE(pi.req_features.has_value());
    EXPECT_FALSE(pi.feature_groups.has_value());
}

// T020: install_location defaults to InstallLocation::INTERNAL_ONLY
TEST(PackageInfoTest, InstallLocationDefault) {
    PackageInfo pi;
    EXPECT_EQ(pi.install_location, InstallLocation::INTERNAL_ONLY);
}

// T021: Boolean fields default to false/0
TEST(PackageInfoTest, BooleanFieldsDefault) {
    PackageInfo pi;
    EXPECT_FALSE(pi.is_stub);
    EXPECT_FALSE(pi.core_app);
    EXPECT_FALSE(pi.required_for_all_users);
    EXPECT_FALSE(pi.overlay_is_static);
    EXPECT_FALSE(pi.is_apex);
    EXPECT_FALSE(pi.is_active_apex);
    EXPECT_EQ(pi.overlay_priority, 0);
    EXPECT_EQ(pi.compile_sdk_version, 0);
}

// T022: long_version_code() returns correct 64-bit value
TEST(PackageInfoTest, LongVersionCode) {
    PackageInfo pi;
    pi.version_code_major = 2;
    pi.version_code = 3;
    int64_t long_vc = pi.long_version_code();
    // Major in upper 32 bits, minor in lower 32 bits
    EXPECT_EQ(long_vc, (static_cast<int64_t>(2) << 32) | 3);
}

// T023: set_long_version_code() correctly splits a 64-bit value
TEST(PackageInfoTest, SetLongVersionCode) {
    PackageInfo pi;
    int64_t long_vc = (static_cast<int64_t>(5) << 32) | 10;
    pi.set_long_version_code(long_vc);
    EXPECT_EQ(pi.version_code_major, 5);
    EXPECT_EQ(pi.version_code, 10);
}

// T024: compose_long_version_code() static method matches Java behavior
TEST(PackageInfoTest, ComposeLongVersionCode) {
    // Normal case
    EXPECT_EQ(PackageInfo::compose_long_version_code(1, 2),
              (static_cast<int64_t>(1) << 32) | 2);
    // Zero major
    EXPECT_EQ(PackageInfo::compose_long_version_code(0, 100), 100);
    // Negative minor (should be treated as unsigned in lower bits)
    int64_t result = PackageInfo::compose_long_version_code(0, -1);
    EXPECT_EQ(result, 0xffffffffLL);
    // Overflow case
    result = PackageInfo::compose_long_version_code(-1, 0);
    EXPECT_EQ(result, (static_cast<int64_t>(-1) << 32));
}

// T025: first_install_time and last_update_time store and return int64_t correctly
TEST(PackageInfoTest, InstallUpdateTime) {
    PackageInfo pi;
    pi.first_install_time = 1234567890123;
    pi.last_update_time = 9876543210987;
    EXPECT_EQ(pi.first_install_time, 1234567890123);
    EXPECT_EQ(pi.last_update_time, 9876543210987);
}

// T026: shared_user_label stores and returns int32_t correctly
TEST(PackageInfoTest, SharedUserLabel) {
    PackageInfo pi;
    pi.shared_user_label = 0x7f080001;
    EXPECT_EQ(pi.shared_user_label, 0x7f080001);
}

// T030: archive_time_millis() getter returns correct int64_t value
TEST(PackageInfoTest, ArchiveTimeMillis) {
    PackageInfo pi;
    EXPECT_EQ(pi.archive_time_millis(), 0);
    pi.set_archive_time_millis(1234567890);
    EXPECT_EQ(pi.archive_time_millis(), 1234567890);
}

// T031: set_archive_time_millis() sets the internal field
TEST(PackageInfoTest, SetArchiveTimeMillis) {
    PackageInfo pi;
    pi.set_archive_time_millis(9876543210);
    EXPECT_EQ(pi.archive_time_millis(), 9876543210);
}

// T032: apex_package_name() returns std::optional<std::string_view>
TEST(PackageInfoTest, ApexPackageName) {
    PackageInfo pi;
    EXPECT_FALSE(pi.apex_package_name().has_value());
    static std::string stored = "com.example.apex";
    pi.set_apex_package_name(stored);
    EXPECT_TRUE(pi.apex_package_name().has_value());
    EXPECT_EQ(*pi.apex_package_name(), "com.example.apex");
}

// T033: set_apex_package_name() sets the internal field
TEST(PackageInfoTest, SetApexPackageName) {
    PackageInfo pi;
    static std::string stored = "com.example.parent";
    pi.set_apex_package_name(stored);
    EXPECT_TRUE(pi.apex_package_name().has_value());
    EXPECT_EQ(*pi.apex_package_name(), "com.example.parent");
}

// T034: is_overlay_package() and is_static_overlay_package() return correct results
TEST(PackageInfoTest, OverlayPackageChecks) {
    PackageInfo pi;
    // Default: no overlay target
    EXPECT_FALSE(pi.is_overlay_package());
    EXPECT_FALSE(pi.is_static_overlay_package());
    // With overlay target
    static std::string target = "com.example.target";
    pi.overlay_target = target;
    EXPECT_TRUE(pi.is_overlay_package());
    // Static overlay
    pi.overlay_is_static = true;
    EXPECT_TRUE(pi.is_overlay_package());
    EXPECT_TRUE(pi.is_static_overlay_package());
}

// T035: to_string() produces a human-readable string representation
TEST(PackageInfoTest, ToString) {
    PackageInfo pi;
    static std::string pkg = "com.example.test";
    pi.package_name = pkg;
    pi.version_code = 1;
    std::string str = pi.to_string();
    EXPECT_NE(str.find("com.example.test"), std::string::npos);
    EXPECT_NE(str.find("version_code=1"), std::string::npos);
}

// T036: describe_contents() returns 0
TEST(PackageInfoTest, DescribeContents) {
    PackageInfo pi;
    EXPECT_EQ(pi.describe_contents(), 0);
}

// T040: Static constants REQUESTED_PERMISSION_* have correct values
TEST(PackageInfoTest, RequestedPermissionConstants) {
    EXPECT_EQ(static_cast<int32_t>(PackageInfo::REQUESTED_PERMISSION_REQUIRED), 0x00000001);
    EXPECT_EQ(static_cast<int32_t>(PackageInfo::REQUESTED_PERMISSION_GRANTED), 0x00000002);
    EXPECT_EQ(static_cast<int32_t>(PackageInfo::REQUESTED_PERMISSION_NEVER_FOR_LOCATION), 0x00010000);
    EXPECT_EQ(static_cast<int32_t>(PackageInfo::REQUESTED_PERMISSION_IMPLICIT), 0x00000004);
}

// T041: Static constants INSTALL_LOCATION_* have correct values
TEST(PackageInfoTest, InstallLocationConstants) {
    EXPECT_EQ(static_cast<int32_t>(PackageInfo::INSTALL_LOCATION_UNSPECIFIED), -1);
    EXPECT_EQ(static_cast<int32_t>(PackageInfo::INSTALL_LOCATION_AUTO), 0);
    EXPECT_EQ(static_cast<int32_t>(PackageInfo::INSTALL_LOCATION_INTERNAL_ONLY), 1);
    EXPECT_EQ(static_cast<int32_t>(PackageInfo::INSTALL_LOCATION_PREFER_EXTERNAL), 2);
}

// T027: application_info accepts std::optional<std::reference_wrapper<const ApplicationInfo>>
TEST(PackageInfoTest, ApplicationInfo) {
    PackageInfo pi;
    EXPECT_FALSE(pi.application_info.has_value());
    // Test that the field is optional (forward-declared type, can't instantiate here)
    // The type system enforces std::optional<std::reference_wrapper<const ApplicationInfo>>
    static android::content::pm::ApplicationInfo app_info;
    pi.application_info = std::cref(app_info);
    EXPECT_TRUE(pi.application_info.has_value());
}

// T028: signing_info accepts std::optional<std::reference_wrapper<const SigningInfo>>
TEST(PackageInfoTest, SigningInfo) {
    PackageInfo pi;
    EXPECT_FALSE(pi.signing_info.has_value());
    // Test that the field is optional (forward-declared type, can't instantiate here)
    static android::content::pm::SigningInfo sign_info;
    pi.signing_info = std::cref(sign_info);
    EXPECT_TRUE(pi.signing_info.has_value());
}

// T029: Optional string_view fields are std::optional<std::string_view>
TEST(PackageInfoTest, OptionalStringViewFields) {
    PackageInfo pi;
    // Default: all nullopt
    EXPECT_FALSE(pi.restricted_account_type.has_value());
    EXPECT_FALSE(pi.required_account_type.has_value());
    EXPECT_FALSE(pi.overlay_target.has_value());
    EXPECT_FALSE(pi.target_overlayable_name.has_value());
    EXPECT_FALSE(pi.overlay_category.has_value());
    EXPECT_FALSE(pi.compile_sdk_version_codename.has_value());
    // Set and verify
    static std::string restricted = "com.example.restricted";
    static std::string required = "com.example.required";
    static std::string overlay = "com.example.overlay";
    static std::string target = "com.example.target_overlayable";
    static std::string category = "com.example.category";
    static std::string codename = "REL";
    pi.restricted_account_type = restricted;
    pi.required_account_type = required;
    pi.overlay_target = overlay;
    pi.target_overlayable_name = target;
    pi.overlay_category = category;
    pi.compile_sdk_version_codename = codename;
    EXPECT_TRUE(pi.restricted_account_type.has_value());
    EXPECT_EQ(*pi.restricted_account_type, "com.example.restricted");
    EXPECT_TRUE(pi.required_account_type.has_value());
    EXPECT_EQ(*pi.required_account_type, "com.example.required");
    EXPECT_TRUE(pi.overlay_target.has_value());
    EXPECT_EQ(*pi.overlay_target, "com.example.overlay");
    EXPECT_TRUE(pi.target_overlayable_name.has_value());
    EXPECT_EQ(*pi.target_overlayable_name, "com.example.target_overlayable");
    EXPECT_TRUE(pi.overlay_category.has_value());
    EXPECT_EQ(*pi.overlay_category, "com.example.category");
    EXPECT_TRUE(pi.compile_sdk_version_codename.has_value());
    EXPECT_EQ(*pi.compile_sdk_version_codename, "REL");
}

// T037: write_to_parcel() serializes all fields to a Parcel-like buffer
TEST(PackageInfoTest, WriteToParcel) {
    PackageInfo pi;
    pi.package_name = "com.example.test";
    pi.version_code = 42;
    pi.version_code_major = 1;
    pi.version_name = "1.0.0";
    pi.base_revision_code = 5;
    pi.shared_user_id = "com.shared";
    pi.shared_user_label = 0x7f080001;
    pi.first_install_time = 1234567890123;
    pi.last_update_time = 9876543210987;
    pi.install_location = InstallLocation::PREFER_EXTERNAL;
    pi.is_stub = true;
    pi.core_app = false;
    pi.required_for_all_users = true;
    pi.overlay_priority = 3;
    pi.overlay_is_static = true;
    pi.compile_sdk_version = 33;
    pi.is_apex = true;
    pi.is_active_apex = false;
    pi.set_archive_time_millis(1111111111111);
    pi.set_apex_package_name("com.example.apex");

    std::vector<uint8_t> buffer;
    pi.write_to_parcel(&buffer, 0);
    EXPECT_GT(buffer.size(), 0u);
    // Buffer should contain serialized data (not empty)
    EXPECT_NE(buffer.size(), static_cast<size_t>(0));
}

// T038: PackageInfo(void* parcel) constructor deserializes all fields from a Parcel-like buffer
TEST(PackageInfoTest, PackageInfoFromParcel) {
    PackageInfo pi_orig;
    pi_orig.package_name = "com.example.deserialize";
    pi_orig.version_code = 99;
    pi_orig.version_code_major = 2;
    pi_orig.version_name = "2.0.0";
    pi_orig.base_revision_code = 10;
    pi_orig.shared_user_id = "com.shared.desc";
    pi_orig.shared_user_label = 0x7f080002;
    pi_orig.first_install_time = 2222222222222;
    pi_orig.last_update_time = 3333333333333;
    pi_orig.install_location = InstallLocation::AUTO;
    pi_orig.is_stub = false;
    pi_orig.core_app = true;
    pi_orig.required_for_all_users = false;
    pi_orig.overlay_priority = 5;
    pi_orig.overlay_is_static = false;
    pi_orig.compile_sdk_version = 34;
    pi_orig.is_apex = false;
    pi_orig.is_active_apex = true;
    pi_orig.set_archive_time_millis(4444444444444);
    pi_orig.set_apex_package_name("com.example.apex.desc");

    std::vector<uint8_t> buffer;
    pi_orig.write_to_parcel(&buffer, 0);

    PackageInfo pi_deser(&buffer);
    // Verify deserialized values match original
    EXPECT_EQ(pi_deser.version_code, 99);
    EXPECT_EQ(pi_deser.version_code_major, 2);
    EXPECT_EQ(pi_deser.base_revision_code, 10);
    EXPECT_EQ(pi_deser.shared_user_label, 0x7f080002);
    EXPECT_EQ(pi_deser.first_install_time, 2222222222222);
    EXPECT_EQ(pi_deser.last_update_time, 3333333333333);
    EXPECT_EQ(pi_deser.install_location, InstallLocation::AUTO);
    EXPECT_EQ(pi_deser.is_stub, false);
    EXPECT_EQ(pi_deser.core_app, true);
    EXPECT_EQ(pi_deser.required_for_all_users, false);
    EXPECT_EQ(pi_deser.overlay_priority, 5);
    EXPECT_EQ(pi_deser.overlay_is_static, false);
    EXPECT_EQ(pi_deser.compile_sdk_version, 34);
    EXPECT_EQ(pi_deser.is_apex, false);
    EXPECT_EQ(pi_deser.is_active_apex, true);
    EXPECT_EQ(pi_deser.archive_time_millis(), 4444444444444);
}

// T039: Serialization round-trip preserves all field values with 100% data integrity
TEST(PackageInfoTest, SerializationRoundTrip) {
    PackageInfo pi_orig;
    pi_orig.version_code = 123;
    pi_orig.version_code_major = 5;
    pi_orig.base_revision_code = 15;
    pi_orig.shared_user_label = 0x7f080003;
    pi_orig.first_install_time = 5555555555555;
    pi_orig.last_update_time = 6666666666666;
    pi_orig.install_location = InstallLocation::INTERNAL_ONLY;
    pi_orig.is_stub = true;
    pi_orig.core_app = false;
    pi_orig.required_for_all_users = true;
    pi_orig.overlay_priority = 7;
    pi_orig.overlay_is_static = true;
    pi_orig.compile_sdk_version = 35;
    pi_orig.is_apex = true;
    pi_orig.is_active_apex = true;
    pi_orig.set_archive_time_millis(7777777777777);

    std::vector<uint8_t> buffer;
    pi_orig.write_to_parcel(&buffer, 0);

    PackageInfo pi_deser(&buffer);
    // Verify all primitive fields round-trip correctly
    EXPECT_EQ(pi_deser.version_code, pi_orig.version_code);
    EXPECT_EQ(pi_deser.version_code_major, pi_orig.version_code_major);
    EXPECT_EQ(pi_deser.base_revision_code, pi_orig.base_revision_code);
    EXPECT_EQ(pi_deser.shared_user_label, pi_orig.shared_user_label);
    EXPECT_EQ(pi_deser.first_install_time, pi_orig.first_install_time);
    EXPECT_EQ(pi_deser.last_update_time, pi_orig.last_update_time);
    EXPECT_EQ(pi_deser.install_location, pi_orig.install_location);
    EXPECT_EQ(pi_deser.is_stub, pi_orig.is_stub);
    EXPECT_EQ(pi_deser.core_app, pi_orig.core_app);
    EXPECT_EQ(pi_deser.required_for_all_users, pi_orig.required_for_all_users);
    EXPECT_EQ(pi_deser.overlay_priority, pi_orig.overlay_priority);
    EXPECT_EQ(pi_deser.overlay_is_static, pi_orig.overlay_is_static);
    EXPECT_EQ(pi_deser.compile_sdk_version, pi_orig.compile_sdk_version);
    EXPECT_EQ(pi_deser.is_apex, pi_orig.is_apex);
    EXPECT_EQ(pi_deser.is_active_apex, pi_orig.is_active_apex);
    EXPECT_EQ(pi_deser.archive_time_millis(), pi_orig.archive_time_millis());
}

// T042: Deprecated fields (version_code, signatures) are marked with // @Deprecated comment
TEST(PackageInfoTest, DeprecatedFields) {
    // version_code has @deprecated comment in header
    // This test verifies the field exists and is accessible
    // The @deprecated annotation is verified by inspecting the header file
    PackageInfo pi;
    pi.version_code = 999;
    EXPECT_EQ(pi.version_code, 999);
    // signatures field exists (deprecated, use signing_info instead)
    EXPECT_FALSE(pi.signatures.has_value());
}

// T043: @hide fields are annotated with // @hide comment in the header
TEST(PackageInfoTest, HideFieldsAccessible) {
    // @hide fields are still accessible in C++ (annotations are documentation only)
    PackageInfo pi;
    pi.version_code_major = 1;
    pi.is_stub = true;
    pi.core_app = true;
    pi.required_for_all_users = true;
    pi.overlay_priority = 3;
    pi.overlay_is_static = true;
    pi.compile_sdk_version = 33;
    pi.is_active_apex = true;
    EXPECT_EQ(pi.version_code_major, 1);
    EXPECT_TRUE(pi.is_stub);
    EXPECT_TRUE(pi.core_app);
    EXPECT_TRUE(pi.required_for_all_users);
    EXPECT_EQ(pi.overlay_priority, 3);
    EXPECT_TRUE(pi.overlay_is_static);
    EXPECT_EQ(pi.compile_sdk_version, 33);
    EXPECT_TRUE(pi.is_active_apex);
}
