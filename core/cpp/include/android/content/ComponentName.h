#pragma once

#include <string>
#include <optional>
#include <expected_shim.h>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::content {

/**
 * Identifier for a specific application component.
 */
class ComponentName {
public:
    ComponentName(std::string pkg, std::string cls);
    ComponentName(const ComponentName& other) = default;
    ComponentName() = default;

    static auto createRelative(const std::string& pkg, const std::string& cls) -> ComponentName;

    [[nodiscard]] auto getPackageName() const -> const std::string&;
    [[nodiscard]] auto getClassName() const -> const std::string&;
    [[nodiscard]] auto getShortClassName() const -> std::string;

    [[nodiscard]] auto flattenToString() const -> std::string;
    [[nodiscard]] auto flattenToShortString() const -> std::string;

    static auto unflattenFromString(const std::string& str) -> std::expected<ComponentName, std::string>;

    auto operator==(const ComponentName& other) const -> bool;
    auto operator!=(const ComponentName& other) const -> bool;
    auto operator<(const ComponentName& other) const -> bool;

    // NDK Binder Parceling
    auto writeToParcel(AParcel* parcel) const -> binder_status_t;
    auto readFromParcel(const AParcel* parcel) -> binder_status_t;

    // Static helpers for parceling nullables
    static auto writeToParcel(const std::optional<ComponentName>& c, AParcel* out) -> binder_status_t;
    static auto readFromParcel(const AParcel* in, std::optional<ComponentName>& out) -> binder_status_t;

private:
    std::string mPackage;
    std::string mClass;
};

} // namespace android::content
