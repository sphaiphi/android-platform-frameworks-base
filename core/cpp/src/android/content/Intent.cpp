#include <android/content/Intent.h>
#include <android/binder_parcel.h>
#include <algorithm>

namespace android::content {

Intent::Intent(std::string action) : mAction(std::move(action)) {}
Intent::Intent(std::string action, net::Uri uri) : mAction(std::move(action)), mData(std::move(uri)) {}

Intent::Intent(const Intent& o)
    : mAction(o.mAction),
      mData(o.mData),
      mType(o.mType),
      mIdentifier(o.mIdentifier),
      mPackage(o.mPackage),
      mComponent(o.mComponent),
      mCategories(o.mCategories),
      mExtras(o.mExtras),
      mFlags(o.mFlags),
      mExtendedFlags(o.mExtendedFlags),
      mContentUserHint(o.mContentUserHint),
      mSourceBounds(o.mSourceBounds),
      mClipData(o.mClipData) {
    if (o.mSelector) mSelector = std::make_shared<Intent>(*o.mSelector);
    if (o.mOriginalIntent) mOriginalIntent = std::make_shared<Intent>(*o.mOriginalIntent);
}

Intent::Intent(Intent&&) noexcept = default;
auto Intent::operator=(const Intent& o) -> Intent& {
    if (this != &o) {
        mAction = o.mAction;
        mData = o.mData;
        mType = o.mType;
        mIdentifier = o.mIdentifier;
        mPackage = o.mPackage;
        mComponent = o.mComponent;
        mCategories = o.mCategories;
        mExtras = o.mExtras;
        mFlags = o.mFlags;
        mExtendedFlags = o.mExtendedFlags;
        mContentUserHint = o.mContentUserHint;
        mSourceBounds = o.mSourceBounds;
        mClipData = o.mClipData;
        if (o.mSelector) mSelector = std::make_shared<Intent>(*o.mSelector);
        else mSelector = nullptr;
        if (o.mOriginalIntent) mOriginalIntent = std::make_shared<Intent>(*o.mOriginalIntent);
        else mOriginalIntent = nullptr;
    }
    return *this;
}
auto Intent::operator=(Intent&&) noexcept -> Intent& = default;

auto Intent::setAction(std::string action) -> void { mAction = std::move(action); }
auto Intent::getAction() const -> std::optional<std::string> { return mAction; }

auto Intent::setData(net::Uri data) -> void { mData = std::move(data); mType = std::nullopt; }
auto Intent::getData() const -> std::optional<net::Uri> { return mData; }

auto Intent::setType(std::string type) -> void { mType = std::move(type); mData = std::nullopt; }
auto Intent::getType() const -> std::optional<std::string> { return mType; }

auto Intent::setDataAndType(net::Uri data, std::string type) -> void {
    mData = std::move(data);
    mType = std::move(type);
}

auto Intent::setIdentifier(std::string identifier) -> void { mIdentifier = std::move(identifier); }
auto Intent::getIdentifier() const -> std::optional<std::string> { return mIdentifier; }

auto Intent::setPackage(std::string package) -> void { mPackage = std::move(package); }
auto Intent::getPackage() const -> std::optional<std::string> { return mPackage; }

auto Intent::setComponent(ComponentName component) -> void { mComponent = std::move(component); }
auto Intent::getComponent() const -> std::optional<ComponentName> { return mComponent; }

auto Intent::addCategory(const std::string& category) -> void { mCategories.insert(category); }
auto Intent::removeCategory(const std::string& category) -> void { mCategories.erase(category); }
auto Intent::hasCategory(const std::string& category) const -> bool { return mCategories.contains(category); }
auto Intent::getCategories() const -> const std::set<std::string>& { return mCategories; }

auto Intent::putExtra(const std::string& key, int32_t value) -> void { mExtras.putInt(key, value); }
auto Intent::putExtra(const std::string& key, std::string value) -> void { mExtras.putString(key, std::move(value)); }
auto Intent::putExtras(const android::os::Bundle& extras) -> void {
    mExtras = extras;
}
auto Intent::hasExtra(const std::string& key) const -> bool { return mExtras.containsKey(key); }
auto Intent::getExtras() -> android::os::Bundle& { return mExtras; }
auto Intent::getExtras() const -> const android::os::Bundle& { return mExtras; }

auto Intent::setFlags(int32_t flags) -> void { mFlags = flags; }
auto Intent::addFlags(int32_t flags) -> void { mFlags |= flags; }
auto Intent::getFlags() const -> int32_t { return mFlags; }

auto Intent::setSourceBounds(graphics::Rect bounds) -> void { mSourceBounds = std::move(bounds); }
auto Intent::getSourceBounds() const -> std::optional<graphics::Rect> { return mSourceBounds; }

auto Intent::setClipData(ClipData clipData) -> void { mClipData = std::move(clipData); }
auto Intent::getClipData() const -> std::optional<ClipData> { return mClipData; }

auto Intent::setSelector(std::shared_ptr<Intent> selector) -> void { mSelector = std::move(selector); }
auto Intent::getSelector() const -> std::shared_ptr<Intent> { return mSelector; }

auto Intent::filterEquals(const Intent& o) const -> bool {
    if (mAction != o.mAction) return false;
    if (mData != o.mData) return false;
    if (mType != o.mType) return false;
    if (mIdentifier != o.mIdentifier) return false;
    if (mPackage != o.mPackage) return false;
    if (mComponent != o.mComponent) return false;
    if (mCategories != o.mCategories) return false;
    return true;
}

// NDK Binder Parceling
auto Intent::writeToParcel(AParcel* out) const -> binder_status_t {
    binder_status_t status;
    status = AParcel_writeString(out, mAction ? mAction->c_str() : nullptr, mAction ? static_cast<int32_t>(mAction->length()) : -1);
    if (status != STATUS_OK) return status;
    
    if (mData) {
        status = mData->writeToParcel(out);
    } else {
        status = AParcel_writeInt32(out, 0); // NULL_TYPE_ID
    }
    if (status != STATUS_OK) return status;

    status = AParcel_writeString(out, mType ? mType->c_str() : nullptr, mType ? static_cast<int32_t>(mType->length()) : -1);
    if (status != STATUS_OK) return status;

    status = AParcel_writeString(out, mIdentifier ? mIdentifier->c_str() : nullptr, mIdentifier ? static_cast<int32_t>(mIdentifier->length()) : -1);
    if (status != STATUS_OK) return status;

    status = AParcel_writeInt32(out, mFlags);
    if (status != STATUS_OK) return status;

    status = AParcel_writeInt32(out, mExtendedFlags);
    if (status != STATUS_OK) return status;

    status = AParcel_writeString(out, mPackage ? mPackage->c_str() : nullptr, mPackage ? static_cast<int32_t>(mPackage->length()) : -1);
    if (status != STATUS_OK) return status;

    status = ComponentName::writeToParcel(mComponent, out);
    if (status != STATUS_OK) return status;

    if (mSourceBounds) {
        status = AParcel_writeInt32(out, 1);
        if (status != STATUS_OK) return status;
        status = mSourceBounds->writeToParcel(out);
    } else {
        status = AParcel_writeInt32(out, 0);
    }
    if (status != STATUS_OK) return status;

    status = AParcel_writeInt32(out, static_cast<int32_t>(mCategories.size()));
    if (status != STATUS_OK) return status;
    for (const auto& cat : mCategories) {
        status = AParcel_writeString(out, cat.c_str(), static_cast<int32_t>(cat.length()));
        if (status != STATUS_OK) return status;
    }

    if (mSelector) {
        status = AParcel_writeInt32(out, 1);
        if (status != STATUS_OK) return status;
        status = mSelector->writeToParcel(out);
    } else {
        status = AParcel_writeInt32(out, 0);
    }
    if (status != STATUS_OK) return status;

    if (mClipData) {
        status = AParcel_writeInt32(out, 1);
        if (status != STATUS_OK) return status;
        status = mClipData->writeToParcel(out);
    } else {
        status = AParcel_writeInt32(out, 0);
    }
    if (status != STATUS_OK) return status;

    status = AParcel_writeInt32(out, mContentUserHint);
    if (status != STATUS_OK) return status;

    // Bundle parceling deferred
    status = AParcel_writeInt32(out, -1); // writeBundle(-1) means null or empty for now

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

auto Intent::readFromParcel(const AParcel* in) -> binder_status_t {
    binder_status_t status;
    std::string s;
    
    status = AParcel_readString(in, &s, string_allocator);
    if (status == STATUS_OK) {
        if (!s.empty() && s.back() == '\0') s.pop_back();
        mAction = std::move(s);
    } else {
        mAction = std::nullopt;
    }

    net::Uri uri;
    status = uri.readFromParcel(in);
    if (status == STATUS_OK) {
        mData = std::move(uri);
    } else {
        mData = std::nullopt;
    }

    status = AParcel_readString(in, &s, string_allocator);
    if (status == STATUS_OK) {
        if (!s.empty() && s.back() == '\0') s.pop_back();
        mType = std::move(s);
    } else {
        mType = std::nullopt;
    }

    status = AParcel_readString(in, &s, string_allocator);
    if (status == STATUS_OK) {
        if (!s.empty() && s.back() == '\0') s.pop_back();
        mIdentifier = std::move(s);
    } else {
        mIdentifier = std::nullopt;
    }

    status = AParcel_readInt32(in, &mFlags);
    if (status != STATUS_OK) return status;

    status = AParcel_readInt32(in, &mExtendedFlags);
    if (status != STATUS_OK) return status;

    status = AParcel_readString(in, &s, string_allocator);
    if (status == STATUS_OK) {
        if (!s.empty() && s.back() == '\0') s.pop_back();
        mPackage = std::move(s);
    } else {
        mPackage = std::nullopt;
    }

    status = ComponentName::readFromParcel(in, mComponent);
    if (status != STATUS_OK) return status;

    int32_t hasBounds;
    status = AParcel_readInt32(in, &hasBounds);
    if (status != STATUS_OK) return status;
    if (hasBounds) {
        graphics::Rect bounds;
        status = bounds.readFromParcel(in);
        if (status != STATUS_OK) return status;
        mSourceBounds = std::move(bounds);
    } else {
        mSourceBounds = std::nullopt;
    }

    int32_t catCount;
    status = AParcel_readInt32(in, &catCount);
    if (status != STATUS_OK) return status;
    mCategories.clear();
    for (int i = 0; i < catCount; ++i) {
        status = AParcel_readString(in, &s, string_allocator);
        if (status != STATUS_OK) return status;
        if (!s.empty() && s.back() == '\0') s.pop_back();
        mCategories.insert(s);
    }

    int32_t hasSelector;
    status = AParcel_readInt32(in, &hasSelector);
    if (status != STATUS_OK) return status;
    if (hasSelector) {
        mSelector = std::make_shared<Intent>();
        status = mSelector->readFromParcel(in);
        if (status != STATUS_OK) return status;
    } else {
        mSelector = nullptr;
    }

    int32_t hasClipData;
    status = AParcel_readInt32(in, &hasClipData);
    if (status != STATUS_OK) return status;
    if (hasClipData) {
        ClipData clip;
        status = clip.readFromParcel(in);
        if (status != STATUS_OK) return status;
        mClipData = std::move(clip);
    } else {
        mClipData = std::nullopt;
    }

    status = AParcel_readInt32(in, &mContentUserHint);
    if (status != STATUS_OK) return status;

    // Bundle skip
    int32_t bundleMagic;
    AParcel_readInt32(in, &bundleMagic);

    return STATUS_OK;
}

} // namespace android::content