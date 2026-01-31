#include <android/content/ClipData.h>
#include <android/content/Intent.h>
#include <android/binder_parcel.h>

namespace android::content {

ClipData::Item::Item(std::string text) : mText(std::move(text)) {}
ClipData::Item::Item(std::shared_ptr<Intent> intent) : mIntent(std::move(intent)) {}
ClipData::Item::Item(net::Uri uri) : mUri(std::move(uri)) {}
ClipData::Item::Item(std::string text, std::shared_ptr<Intent> intent, net::Uri uri)
    : mText(std::move(text)), mIntent(std::move(intent)), mUri(std::move(uri)) {}
ClipData::Item::Item() = default;
ClipData::Item::~Item() = default;

auto ClipData::Item::getText() const -> const std::string& { return mText; }
auto ClipData::Item::getIntent() const -> std::shared_ptr<Intent> { return mIntent; }
auto ClipData::Item::getUri() const -> const net::Uri& { return mUri; }

auto ClipData::Item::writeToParcel(AParcel* parcel) const -> binder_status_t {
    // Basic implementation for now, will be updated when Intent parceling is ready
    binder_status_t status = AParcel_writeString(parcel, mText.c_str(), mText.length());
    if (status != STATUS_OK) return status;
    status = AParcel_writeString(parcel, mHtmlText.c_str(), mHtmlText.length());
    if (status != STATUS_OK) return status;
    
    // Intent skip
    status = AParcel_writeInt32(parcel, 0);
    if (status != STATUS_OK) return status;

    // IntentSender skip
    status = AParcel_writeInt32(parcel, 0);
    if (status != STATUS_OK) return status;

    return mUri.writeToParcel(parcel);
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

auto ClipData::Item::readFromParcel(const AParcel* parcel) -> binder_status_t {
    binder_status_t status = AParcel_readString(parcel, &mText, string_allocator);
    if (status != STATUS_OK) return status;
    if (!mText.empty() && mText.back() == '\0') mText.pop_back();

    status = AParcel_readString(parcel, &mHtmlText, string_allocator);
    if (status != STATUS_OK) return status;
    if (!mHtmlText.empty() && mHtmlText.back() == '\0') mHtmlText.pop_back();

    int32_t hasIntent;
    status = AParcel_readInt32(parcel, &hasIntent);
    if (status != STATUS_OK) return status;
    // Skip reading intent for now

    int32_t hasIntentSender;
    status = AParcel_readInt32(parcel, &hasIntentSender); // Skip
    if (status != STATUS_OK) return status;

    return mUri.readFromParcel(parcel);
}

ClipData::ClipData(ClipDescription description, Item item)
    : mClipDescription(std::move(description)) {
    mItems.push_back(std::move(item));
}

ClipData::ClipData(const ClipData& other)
    : mClipDescription(other.mClipDescription), mItems(other.mItems) {}

auto ClipData::getDescription() const -> const ClipDescription& { return mClipDescription; }
auto ClipData::addItem(Item item) -> void { mItems.push_back(std::move(item)); }
auto ClipData::getItemCount() const -> int { return static_cast<int>(mItems.size()); }
auto ClipData::getItemAt(int index) const -> const Item& { return mItems[index]; }

auto ClipData::writeToParcel(AParcel* parcel) const -> binder_status_t {
    binder_status_t status = mClipDescription.writeToParcel(parcel);
    if (status != STATUS_OK) return status;
    
    // Icon skip
    status = AParcel_writeInt32(parcel, 0);
    if (status != STATUS_OK) return status;

    status = AParcel_writeInt32(parcel, static_cast<int32_t>(mItems.size()));
    if (status != STATUS_OK) return status;
    for (const auto& item : mItems) {
        status = item.writeToParcel(parcel);
        if (status != STATUS_OK) return status;
    }
    return STATUS_OK;
}

auto ClipData::readFromParcel(const AParcel* parcel) -> binder_status_t {
    binder_status_t status = mClipDescription.readFromParcel(parcel);
    if (status != STATUS_OK) return status;

    int32_t hasIcon;
    status = AParcel_readInt32(parcel, &hasIcon);
    if (status != STATUS_OK) return status;

    int32_t count;
    status = AParcel_readInt32(parcel, &count);
    if (status != STATUS_OK) return status;
    mItems.resize(count);
    for (int i = 0; i < count; ++i) {
        status = mItems[i].readFromParcel(parcel);
        if (status != STATUS_OK) return status;
    }
    return STATUS_OK;
}

} // namespace android::content
