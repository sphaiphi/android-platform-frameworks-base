#include <android/net/Uri.h>
#include <algorithm>
#include <regex>

namespace android::net {

Uri::Uri(Builder builder)
    : mScheme(std::move(builder.mScheme)),
      mOpaquePart(std::move(builder.mOpaquePart)),
      mAuthority(std::move(builder.mAuthority)),
      mPath(std::move(builder.mPath)),
      mQuery(std::move(builder.mQuery)),
      mFragment(std::move(builder.mFragment)) {}

auto Uri::parse(const std::string& uriString) -> Uri {
    Builder builder;
    if (uriString.empty()) return builder.build();

    // Basic regex-based parsing for URI components
    std::regex uriRegex("^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?$");
    std::smatch match;
    if (std::regex_match(uriString, match, uriRegex)) {
        if (match[2].matched) builder.scheme(match[2].str());
        if (match[4].matched) builder.authority(match[4].str());
        if (match[5].matched) builder.path(match[5].str());
        if (match[7].matched) builder.query(match[7].str());
        if (match[9].matched) builder.fragment(match[9].str());
    }
    
    // Check for opaque URIs (scheme provided but not starting with //)
    if (builder.mScheme.has_value() && !builder.mAuthority.has_value() && !builder.mPath.has_value()) {
        size_t colon = uriString.find(':');
        if (colon != std::string::npos) {
            std::string ssp = uriString.substr(colon + 1);
            if (!ssp.starts_with("/")) {
                builder.mOpaquePart = ssp;
            }
        }
    }

    return builder.build();
}

auto Uri::getScheme() const -> std::optional<std::string> { return mScheme; }
auto Uri::getSchemeSpecificPart() const -> std::string {
    if (mOpaquePart) return *mOpaquePart;
    std::string ssp;
    if (mAuthority) ssp += "//" + *mAuthority;
    if (mPath) ssp += *mPath;
    if (mQuery) ssp += "?" + *mQuery;
    return ssp;
}
auto Uri::getEncodedSchemeSpecificPart() const -> std::string { return getSchemeSpecificPart(); }
auto Uri::getAuthority() const -> std::optional<std::string> { return mAuthority; }
auto Uri::getEncodedAuthority() const -> std::optional<std::string> { return mAuthority; }
auto Uri::getPath() const -> std::optional<std::string> { return mPath; }
auto Uri::getEncodedPath() const -> std::optional<std::string> { return mPath; }
auto Uri::getQuery() const -> std::optional<std::string> { return mQuery; }
auto Uri::getEncodedQuery() const -> std::optional<std::string> { return mQuery; }
auto Uri::getFragment() const -> std::optional<std::string> { return mFragment; }
auto Uri::getEncodedFragment() const -> std::optional<std::string> { return mFragment; }

auto Uri::isHierarchical() const -> bool {
    return !isOpaque();
}

auto Uri::isOpaque() const -> bool {
    return mOpaquePart.has_value();
}

auto Uri::isRelative() const -> bool {
    return !mScheme.has_value();
}

auto Uri::isAbsolute() const -> bool {
    return mScheme.has_value();
}

auto Uri::toString() const -> std::string {
    if (mCachedString) return *mCachedString;

    std::string result;
    if (mScheme) result += *mScheme + ":";
    if (mOpaquePart) {
        result += *mOpaquePart;
    } else {
        if (mAuthority) result += "//" + *mAuthority;
        if (mPath) result += *mPath;
        if (mQuery) result += "?" + *mQuery;
    }
    if (mFragment) result += "#" + *mFragment;

    mCachedString = result;
    return result;
}

auto Uri::buildUpon() const -> Builder {
    Builder builder;
    builder.mScheme = mScheme;
    builder.mOpaquePart = mOpaquePart;
    builder.mAuthority = mAuthority;
    builder.mPath = mPath;
    builder.mQuery = mQuery;
    builder.mFragment = mFragment;
    return builder;
}

auto Uri::operator==(const Uri& other) const -> bool {
    return toString() == other.toString();
}

auto Uri::operator<(const Uri& other) const -> bool {
    return toString() < other.toString();
}

auto Uri::writeToParcel(AParcel* parcel) const -> binder_status_t {
    AParcel_writeInt32(parcel, STRING_TYPE_ID);
    std::string s = toString();
    return AParcel_writeString(parcel, s.c_str(), s.length());
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

auto Uri::readFromParcel(const AParcel* parcel) -> binder_status_t {
    int32_t type;
    binder_status_t status = AParcel_readInt32(parcel, &type);
    if (status != STATUS_OK) return status;

    if (type == STRING_TYPE_ID) {
        std::string s;
        status = AParcel_readString(parcel, &s, string_allocator);
        if (status != STATUS_OK) return status;
        if (!s.empty() && s.back() == '\0') s.pop_back();
        *this = parse(s);
    } else if (type == NULL_TYPE_ID) {
        *this = Uri();
    } else {
        return STATUS_BAD_VALUE;
    }
    return STATUS_OK;
}

// Builder implementation
auto Uri::Builder::scheme(std::string scheme) -> Builder& { mScheme = std::move(scheme); return *this; }
auto Uri::Builder::opaquePart(std::string opaquePart) -> Builder& { mOpaquePart = std::move(opaquePart); return *this; }
auto Uri::Builder::authority(std::string authority) -> Builder& { mAuthority = std::move(authority); return *this; }
auto Uri::Builder::path(std::string path) -> Builder& { mPath = std::move(path); return *this; }
auto Uri::Builder::appendPath(const std::string& newSegment) -> Builder& {
    if (!mPath) mPath = "";
    if (mPath->empty() || mPath->back() != '/') *mPath += "/";
    *mPath += newSegment;
    return *this;
}
auto Uri::Builder::query(std::string query) -> Builder& { mQuery = std::move(query); return *this; }
auto Uri::Builder::appendQueryParameter(const std::string& key, const std::string& value) -> Builder& {
    if (!mQuery) mQuery = "";
    if (!mQuery->empty()) *mQuery += "&";
    *mQuery += key + "=" + value;
    return *this;
}
auto Uri::Builder::fragment(std::string fragment) -> Builder& { mFragment = std::move(fragment); return *this; }
auto Uri::Builder::build() -> Uri { return Uri(*this); }

} // namespace android::net
