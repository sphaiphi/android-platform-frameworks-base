#include <android/os/Bundle.h>

namespace android::os {

auto Bundle::putInt(const std::string& key, int32_t value) -> void {
    mData[key] = value;
}

auto Bundle::putLong(const std::string& key, int64_t value) -> void {
    mData[key] = value;
}

auto Bundle::putDouble(const std::string& key, double value) -> void {
    mData[key] = value;
}

auto Bundle::putBoolean(const std::string& key, bool value) -> void {
    mData[key] = value;
}

auto Bundle::putString(const std::string& key, std::string value) -> void {
    mData[key] = std::move(value);
}

auto Bundle::putStringArray(const std::string& key, std::vector<std::string> value) -> void {
    mData[key] = std::move(value);
}

auto Bundle::putBundle(const std::string& key, std::shared_ptr<Bundle> value) -> void {
    mData[key] = std::move(value);
}

template<typename T>
auto Bundle::get(const std::string& key) const -> std::expected<T, BundleError> {
    if (auto it = mData.find(key); it != mData.end()) {
        if (std::holds_alternative<T>(it->second)) {
            return std::get<T>(it->second);
        }
        return std::unexpected(BundleError::TypeMismatch);
    }
    return std::unexpected(BundleError::KeyNotFound);
}

auto Bundle::getInt(const std::string& key) const -> std::expected<int32_t, BundleError> {
    return get<int32_t>(key);
}

auto Bundle::getLong(const std::string& key) const -> std::expected<int64_t, BundleError> {
    return get<int64_t>(key);
}

auto Bundle::getDouble(const std::string& key) const -> std::expected<double, BundleError> {
    return get<double>(key);
}

auto Bundle::getBoolean(const std::string& key) const -> std::expected<bool, BundleError> {
    return get<bool>(key);
}

auto Bundle::getString(const std::string& key) const -> std::expected<std::string, BundleError> {
    return get<std::string>(key);
}

auto Bundle::getStringArray(const std::string& key) const -> std::expected<std::vector<std::string>, BundleError> {
    return get<std::vector<std::string>>(key);
}

auto Bundle::getBundle(const std::string& key) const -> std::expected<std::shared_ptr<Bundle>, BundleError> {
    return get<std::shared_ptr<Bundle>>(key);
}

auto Bundle::containsKey(const std::string& key) const -> bool {
    return mData.contains(key);
}

auto Bundle::size() const -> size_t {
    return mData.size();
}

auto Bundle::isEmpty() const -> bool {
    return mData.empty();
}

auto Bundle::clear() -> void {
    mData.clear();
}

auto Bundle::remove(const std::string& key) -> void {
    mData.erase(key);
}

} // namespace android::os