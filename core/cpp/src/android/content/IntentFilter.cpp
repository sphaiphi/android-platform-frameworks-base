#include <android/content/IntentFilter.h>
#include <algorithm>

namespace android::content {

// AuthorityEntry implementation
IntentFilter::AuthorityEntry::AuthorityEntry(std::string h, std::string p)
    : host(std::move(h)) {
    wild = !host.empty() && host[0] == '*';
    if (wild) {
        host = host.substr(1);
    }
    if (!p.empty()) {
        try {
            port = std::stoi(p);
        } catch (...) {
            port = -1;
        }
    }
}

bool IntentFilter::AuthorityEntry::match(const std::string& dataHost, int dataPort) const {
    if (dataHost.empty()) return false;
    
    std::string matchHost = dataHost;
    if (wild) {
        if (matchHost.length() < host.length()) return false;
        matchHost = matchHost.substr(matchHost.length() - host.length());
    }
    
    if (matchHost != host) return false;
    
    if (port >= 0) {
        return port == dataPort;
    }
    
    return true;
}

binder_status_t IntentFilter::AuthorityEntry::writeToParcel(AParcel* parcel) const {
    binder_status_t status = AParcel_writeString(parcel, host.c_str(), host.length());
    if (status != STATUS_OK) return status;
    status = AParcel_writeInt32(parcel, port);
    if (status != STATUS_OK) return status;
    status = AParcel_writeBool(parcel, wild);
    return status;
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

binder_status_t IntentFilter::AuthorityEntry::readFromParcel(const AParcel* parcel) {
    binder_status_t status = AParcel_readString(parcel, &host, string_allocator);
    if (status != STATUS_OK) return status;
    if (!host.empty() && host.back() == '\0') host.pop_back();
    status = AParcel_readInt32(parcel, &port);
    if (status != STATUS_OK) return status;
    status = AParcel_readBool(parcel, &wild);
    return status;
}

// IntentFilter implementation
IntentFilter::IntentFilter() = default;

IntentFilter::IntentFilter(const std::string& action) {
    addAction(action);
}

IntentFilter::IntentFilter(const std::string& action, const std::string& dataType) {
    addAction(action);
    addDataType(dataType);
}

IntentFilter::IntentFilter(const IntentFilter& o)
    : mActions(o.mActions),
      mCategories(o.mCategories),
      mDataSchemes(o.mDataSchemes),
      mDataAuthorities(o.mDataAuthorities),
      mDataPaths(o.mDataPaths),
      mDataTypes(o.mDataTypes) {
}

void IntentFilter::addAction(const std::string& action) {
    if (std::find(mActions.begin(), mActions.end(), action) == mActions.end()) {
        mActions.push_back(action);
    }
}

int IntentFilter::countActions() const {
    return mActions.size();
}

std::string IntentFilter::getAction(int index) const {
    return mActions[index];
}

bool IntentFilter::hasAction(const std::string& action) const {
    return std::find(mActions.begin(), mActions.end(), action) != mActions.end();
}

bool IntentFilter::matchAction(const std::string& action) const {
    if (action.empty()) return mActions.empty();
    return hasAction(action);
}

void IntentFilter::addCategory(const std::string& category) {
    if (std::find(mCategories.begin(), mCategories.end(), category) == mCategories.end()) {
        mCategories.push_back(category);
    }
}

int IntentFilter::countCategories() const {
    return mCategories.size();
}

std::string IntentFilter::getCategory(int index) const {
    return mCategories[index];
}

bool IntentFilter::hasCategory(const std::string& category) const {
    return std::find(mCategories.begin(), mCategories.end(), category) != mCategories.end();
}

std::optional<std::string> IntentFilter::matchCategories(const std::vector<std::string>& categories) const {
    for (const auto& category : categories) {
        if (!hasCategory(category)) {
            return category;
        }
    }
    return std::nullopt;
}

void IntentFilter::addDataScheme(const std::string& scheme) {
    if (std::find(mDataSchemes.begin(), mDataSchemes.end(), scheme) == mDataSchemes.end()) {
        mDataSchemes.push_back(scheme);
    }
}

int IntentFilter::countDataSchemes() const {
    return mDataSchemes.size();
}

std::string IntentFilter::getDataScheme(int index) const {
    return mDataSchemes[index];
}

bool IntentFilter::hasDataScheme(const std::string& scheme) const {
    return std::find(mDataSchemes.begin(), mDataSchemes.end(), scheme) != mDataSchemes.end();
}

void IntentFilter::addDataAuthority(const std::string& host, const std::string& port) {
    mDataAuthorities.emplace_back(host, port);
}

int IntentFilter::countDataAuthorities() const {
    return mDataAuthorities.size();
}

const IntentFilter::AuthorityEntry& IntentFilter::getDataAuthority(int index) const {
    return mDataAuthorities[index];
}

void IntentFilter::addDataPath(const std::string& path, int type) {
    mDataPaths.emplace_back(path, type);
}

int IntentFilter::countDataPaths() const {
    return mDataPaths.size();
}

const os::PatternMatcher& IntentFilter::getDataPath(int index) const {
    return mDataPaths[index];
}

void IntentFilter::addDataType(const std::string& type) {
    if (std::find(mDataTypes.begin(), mDataTypes.end(), type) == mDataTypes.end()) {
        mDataTypes.push_back(type);
    }
}

int IntentFilter::countDataTypes() const {
    return mDataTypes.size();
}

std::string IntentFilter::getDataType(int index) const {
    return mDataTypes[index];
}

bool IntentFilter::hasDataType(const std::string& type) const {
    return findMimeType(type);
}

bool IntentFilter::findMimeType(const std::string& type) const {
    for (const auto& filterType : mDataTypes) {
        if (filterType == type) return true;
        if (filterType.length() >= 2 && filterType.back() == '*') {
            std::string prefix = filterType.substr(0, filterType.length() - 1);
            if (type.compare(0, prefix.length(), prefix) == 0) return true;
        }
    }
    return false;
}

int IntentFilter::match(const std::string& action, const std::string& type, const std::string& scheme, const std::string& dataHost, int dataPort, const std::string& dataPath, const std::vector<std::string>& categories) const {
    if (!matchAction(action)) return NO_MATCH_ACTION;
    int dataMatch = matchData(type, scheme, dataHost, dataPort, dataPath);
    if (dataMatch < 0) return dataMatch;
    if (matchCategories(categories).has_value()) return NO_MATCH_CATEGORY;
    return dataMatch;
}

int IntentFilter::matchData(const std::string& type, const std::string& scheme, const std::string& dataHost, int dataPort, const std::string& dataPath) const {
    int match = MATCH_CATEGORY_EMPTY;

    if (mDataTypes.empty() && mDataSchemes.empty()) {
        return (type.empty() && scheme.empty()) ? (MATCH_CATEGORY_EMPTY + MATCH_ADJUSTMENT_NORMAL) : NO_MATCH_DATA;
    }

    if (!mDataSchemes.empty()) {
        if (std::find(mDataSchemes.begin(), mDataSchemes.end(), scheme) != mDataSchemes.end()) {
            match = MATCH_CATEGORY_SCHEME;
        } else {
            return NO_MATCH_DATA;
        }

        if (!mDataAuthorities.empty()) {
            bool authMatched = false;
            for (const auto& auth : mDataAuthorities) {
                if (auth.match(dataHost, dataPort)) {
                    authMatched = true;
                    match = (auth.port >= 0) ? MATCH_CATEGORY_PORT : MATCH_CATEGORY_HOST;
                    break;
                }
            }
            if (!authMatched) return NO_MATCH_DATA;

            if (!mDataPaths.empty()) {
                bool pathMatched = false;
                for (const auto& path : mDataPaths) {
                    if (path.match(dataPath)) {
                        pathMatched = true;
                        match = MATCH_CATEGORY_PATH;
                        break;
                    }
                }
                if (!pathMatched) return NO_MATCH_DATA;
            }
        }
    } else if (!scheme.empty() && scheme != "content" && scheme != "file") {
        return NO_MATCH_DATA;
    }

    if (!mDataTypes.empty()) {
        if (findMimeType(type)) {
            match = MATCH_CATEGORY_TYPE;
        } else {
            return NO_MATCH_TYPE;
        }
    } else if (!type.empty()) {
        return NO_MATCH_TYPE;
    }

    return match + MATCH_ADJUSTMENT_NORMAL;
}

binder_status_t IntentFilter::writeToParcel(AParcel* parcel) const {
    AParcel_writeInt32(parcel, mActions.size());
    for (const auto& a : mActions) AParcel_writeString(parcel, a.c_str(), a.length());
    
    AParcel_writeInt32(parcel, mCategories.size());
    for (const auto& c : mCategories) AParcel_writeString(parcel, c.c_str(), c.length());
    
    AParcel_writeInt32(parcel, mDataSchemes.size());
    for (const auto& s : mDataSchemes) AParcel_writeString(parcel, s.c_str(), s.length());
    
    AParcel_writeInt32(parcel, mDataAuthorities.size());
    for (const auto& auth : mDataAuthorities) auth.writeToParcel(parcel);
    
    AParcel_writeInt32(parcel, mDataPaths.size());
    for (const auto& path : mDataPaths) path.writeToParcel(parcel);
    
    AParcel_writeInt32(parcel, mDataTypes.size());
    for (const auto& t : mDataTypes) AParcel_writeString(parcel, t.c_str(), t.length());

    return STATUS_OK;
}

binder_status_t IntentFilter::readFromParcel(const AParcel* parcel) {
    int32_t count;
    
    if (AParcel_readInt32(parcel, &count) == STATUS_OK) {
        mActions.resize(count);
        for (int i = 0; i < count; ++i) {
            AParcel_readString(parcel, &mActions[i], string_allocator);
            if (!mActions[i].empty() && mActions[i].back() == '\0') mActions[i].pop_back();
        }
    }
    
    if (AParcel_readInt32(parcel, &count) == STATUS_OK) {
        mCategories.resize(count);
        for (int i = 0; i < count; ++i) {
            AParcel_readString(parcel, &mCategories[i], string_allocator);
            if (!mCategories[i].empty() && mCategories[i].back() == '\0') mCategories[i].pop_back();
        }
    }
    
    if (AParcel_readInt32(parcel, &count) == STATUS_OK) {
        mDataSchemes.resize(count);
        for (int i = 0; i < count; ++i) {
            AParcel_readString(parcel, &mDataSchemes[i], string_allocator);
            if (!mDataSchemes[i].empty() && mDataSchemes[i].back() == '\0') mDataSchemes[i].pop_back();
        }
    }
    
    if (AParcel_readInt32(parcel, &count) == STATUS_OK) {
        mDataAuthorities.resize(count);
        for (int i = 0; i < count; ++i) mDataAuthorities[i].readFromParcel(parcel);
    }
    
    if (AParcel_readInt32(parcel, &count) == STATUS_OK) {
        mDataPaths.resize(count);
        for (int i = 0; i < count; ++i) mDataPaths[i].readFromParcel(parcel);
    }
    
    if (AParcel_readInt32(parcel, &count) == STATUS_OK) {
        mDataTypes.resize(count);
        for (int i = 0; i < count; ++i) {
            AParcel_readString(parcel, &mDataTypes[i], string_allocator);
            if (!mDataTypes[i].empty() && mDataTypes[i].back() == '\0') mDataTypes[i].pop_back();
        }
    }

    return STATUS_OK;
}

} // namespace android::content