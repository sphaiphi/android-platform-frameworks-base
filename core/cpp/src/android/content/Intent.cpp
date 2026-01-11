#include <android/content/Intent.h>

namespace android::content {

Intent::Intent(std::string action) : mAction(std::move(action)) {}

auto Intent::setAction(std::string action) -> void {
    mAction = std::move(action);
}

auto Intent::getAction() const -> std::expected<std::string, IntentError> {
    if (mAction) return *mAction;
    return std::unexpected(IntentError::ActionNotSet);
}

auto Intent::setData(std::string data) -> void {
    mData = std::move(data);
}

auto Intent::getData() const -> std::expected<std::string, IntentError> {
    if (mData) return *mData;
    return std::unexpected(IntentError::DataNotSet);
}

auto Intent::setType(std::string type) -> void {
    mType = std::move(type);
}

auto Intent::getType() const -> std::expected<std::string, IntentError> {
    if (mType) return *mType;
    return std::unexpected(IntentError::TypeNotSet);
}

auto Intent::addCategory(const std::string& category) -> void {
    mCategories.insert(category);
}

auto Intent::removeCategory(const std::string& category) -> void {
    mCategories.erase(category);
}

auto Intent::hasCategory(const std::string& category) const -> bool {
    return mCategories.contains(category);
}

auto Intent::getCategories() const -> const std::set<std::string>& {
    return mCategories;
}

auto Intent::putExtra(const std::string& key, int32_t value) -> void {
    mExtras.putInt(key, value);
}

auto Intent::putExtra(const std::string& key, std::string value) -> void {
    mExtras.putString(key, std::move(value));
}

auto Intent::putExtras(const android::os::Bundle& extras) -> void {
    // This is a shallow copy of the extras map for now, as defined in Bundle's rule of zero
    // In a real implementation, we might want a deep copy or merge.
    mExtras = extras;
}

auto Intent::hasExtra(const std::string& key) const -> bool {
    return mExtras.containsKey(key);
}

auto Intent::getExtras() -> android::os::Bundle& {
    return mExtras;
}

auto Intent::getExtras() const -> const android::os::Bundle& {
    return mExtras;
}

auto Intent::setFlags(int32_t flags) -> void {
    mFlags = flags;
}

auto Intent::addFlags(int32_t flags) -> void {
    mFlags |= flags;
}

auto Intent::getFlags() const -> int32_t {
    return mFlags;
}

} // namespace android::content
