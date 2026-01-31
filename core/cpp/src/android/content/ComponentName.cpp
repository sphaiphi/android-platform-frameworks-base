#include <android/content/ComponentName.h>
#include <algorithm>
#include <stdexcept>

namespace android::content {

ComponentName::ComponentName(std::string pkg, std::string cls)
    : mPackage(std::move(pkg)), mClass(std::move(cls)) {
    if (mPackage.empty()) throw std::invalid_argument("package name is empty");
    if (mClass.empty()) throw std::invalid_argument("class name is empty");
}

auto ComponentName::createRelative(const std::string& pkg, const std::string& cls) -> ComponentName {
    if (cls.empty()) throw std::invalid_argument("class name is empty");
    std::string fullClass;
    if (cls[0] == '.') {
        fullClass = pkg + cls;
    } else {
        fullClass = cls;
    }
    return ComponentName(pkg, fullClass);
}

auto ComponentName::getPackageName() const -> const std::string& {
    return mPackage;
}

auto ComponentName::getClassName() const -> const std::string& {
    return mClass;
}

auto ComponentName::getShortClassName() const -> std::string {
    if (mClass.starts_with(mPackage)) {
        size_t PN = mPackage.length();
        size_t CN = mClass.length();
        if (CN > PN && mClass[PN] == '.') {
            return mClass.substr(PN);
        }
    }
    return mClass;
}

auto ComponentName::flattenToString() const -> std::string {
    return mPackage + "/" + mClass;
}

auto ComponentName::flattenToShortString() const -> std::string {
    return mPackage + "/" + getShortClassName();
}

auto ComponentName::unflattenFromString(const std::string& str) -> std::expected<ComponentName, std::string> {
    size_t sep = str.find('/');
    if (sep == std::string::npos || sep + 1 >= str.length()) {
        return std::unexpected("Invalid component name format");
    }
    std::string pkg = str.substr(0, sep);
    std::string cls = str.substr(sep + 1);
    if (!cls.empty() && cls[0] == '.') {
        cls = pkg + cls;
    }
    return ComponentName(pkg, cls);
}

auto ComponentName::operator==(const ComponentName& other) const -> bool {
    return mPackage == other.mPackage && mClass == other.mClass;
}

auto ComponentName::operator!=(const ComponentName& other) const -> bool {
    return !(*this == other);
}

auto ComponentName::operator<(const ComponentName& other) const -> bool {
    if (mPackage != other.mPackage) return mPackage < other.mPackage;
    return mClass < other.mClass;
}

auto ComponentName::writeToParcel(AParcel* parcel) const -> binder_status_t {
    binder_status_t status = AParcel_writeString(parcel, mPackage.c_str(), mPackage.length());
    if (status != STATUS_OK) return status;
    return AParcel_writeString(parcel, mClass.c_str(), mClass.length());
}

// Helper for AParcel_readString
static bool string_allocator(void* stringData, int32_t length, char** outBuffer) {
    if (length < 0) return false;
    auto* str = static_cast<std::string*>(stringData);
    if (length == 0) {
        str->clear();
        *outBuffer = nullptr;
        return true;
    }
    str->resize(length);
    *outBuffer = &((*str)[0]);
    return true;
}

auto ComponentName::readFromParcel(const AParcel* parcel) -> binder_status_t {
    binder_status_t status = AParcel_readString(parcel, &mPackage, string_allocator);
    if (status != STATUS_OK) return status;
    if (!mPackage.empty() && mPackage.back() == '\0') mPackage.pop_back();
    status = AParcel_readString(parcel, &mClass, string_allocator);
    if (status != STATUS_OK) return status;
    if (!mClass.empty() && mClass.back() == '\0') mClass.pop_back();
    return STATUS_OK;
}

auto ComponentName::writeToParcel(const std::optional<ComponentName>& c, AParcel* out) -> binder_status_t {
    if (c.has_value()) {
        return c->writeToParcel(out);
    } else {
        return AParcel_writeString(out, nullptr, -1);
    }
}

auto ComponentName::readFromParcel(const AParcel* in, std::optional<ComponentName>& out) -> binder_status_t {
    std::string pkg;
    binder_status_t status = AParcel_readString(in, &pkg, string_allocator);
    if (status != STATUS_OK) return status;
    if (pkg.empty()) { // Assuming empty/null was written
        out = std::nullopt;
        return STATUS_OK;
    }
    if (pkg.back() == '\0') pkg.pop_back();
    std::string cls;
    status = AParcel_readString(in, &cls, string_allocator);
    if (status != STATUS_OK) return status;
    if (cls.back() == '\0') cls.pop_back();
    try {
        out = ComponentName(pkg, cls);
    } catch (...) {
        return STATUS_BAD_VALUE;
    }
    return STATUS_OK;
}

} // namespace android::content
