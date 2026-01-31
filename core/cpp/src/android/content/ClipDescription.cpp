#include <android/content/ClipDescription.h>
#include <android/binder_parcel.h>

namespace android::content {

ClipDescription::ClipDescription(std::string label, std::vector<std::string> mimeTypes)
    : mLabel(std::move(label)), mMimeTypes(std::move(mimeTypes)) {}

auto ClipDescription::getLabel() const -> const std::string& { return mLabel; }
auto ClipDescription::getMimeTypeCount() const -> int { return static_cast<int>(mMimeTypes.size()); }
auto ClipDescription::getMimeType(int index) const -> const std::string& { return mMimeTypes[index]; }
auto ClipDescription::hasMimeType(const std::string& mimeType) const -> bool {
    for (const auto& m : mMimeTypes) {
        if (m == mimeType) return true;
    }
    return false;
}

auto ClipDescription::writeToParcel(AParcel* parcel) const -> binder_status_t {
    binder_status_t status = AParcel_writeString(parcel, mLabel.c_str(), mLabel.length());
    if (status != STATUS_OK) return status;
    status = AParcel_writeInt32(parcel, static_cast<int32_t>(mMimeTypes.size()));
    if (status != STATUS_OK) return status;
    for (const auto& m : mMimeTypes) {
        status = AParcel_writeString(parcel, m.c_str(), m.length());
        if (status != STATUS_OK) return status;
    }
    return STATUS_OK;
}

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

auto ClipDescription::readFromParcel(const AParcel* parcel) -> binder_status_t {
    binder_status_t status = AParcel_readString(parcel, &mLabel, string_allocator);
    if (status != STATUS_OK) return status;
    if (!mLabel.empty() && mLabel.back() == '\0') mLabel.pop_back();

    int32_t count;
    status = AParcel_readInt32(parcel, &count);
    if (status != STATUS_OK) return status;
    mMimeTypes.resize(count);
    for (int i = 0; i < count; ++i) {
        status = AParcel_readString(parcel, &mMimeTypes[i], string_allocator);
        if (status != STATUS_OK) return status;
        if (!mMimeTypes[i].empty() && mMimeTypes[i].back() == '\0') mMimeTypes[i].pop_back();
    }
    return STATUS_OK;
}

} // namespace android::content
