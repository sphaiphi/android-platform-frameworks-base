#pragma once

#include <string>
#include <vector>
#include <optional>
#include <android/os/PatternMatcher.h>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::content {

class IntentFilter {
public:
    struct AuthorityEntry {
        std::string host;
        int port{-1};
        bool wild{false};

        AuthorityEntry(std::string h, std::string p);
        AuthorityEntry() = default;

        bool match(const std::string& dataHost, int dataPort) const;
        
        binder_status_t writeToParcel(AParcel* parcel) const;
        binder_status_t readFromParcel(const AParcel* parcel);
    };

    IntentFilter();
    explicit IntentFilter(const std::string& action);
    IntentFilter(const std::string& action, const std::string& dataType);
    IntentFilter(const IntentFilter& o);
    ~IntentFilter() = default;

    // Actions
    void addAction(const std::string& action);
    int countActions() const;
    std::string getAction(int index) const;
    bool hasAction(const std::string& action) const;
    bool matchAction(const std::string& action) const;

    // Categories
    void addCategory(const std::string& category);
    int countCategories() const;
    std::string getCategory(int index) const;
    bool hasCategory(const std::string& category) const;
    std::optional<std::string> matchCategories(const std::vector<std::string>& categories) const;

    // Data Schemes
    void addDataScheme(const std::string& scheme);
    int countDataSchemes() const;
    std::string getDataScheme(int index) const;
    bool hasDataScheme(const std::string& scheme) const;

    // Data Authorities
    void addDataAuthority(const std::string& host, const std::string& port);
    int countDataAuthorities() const;
    const AuthorityEntry& getDataAuthority(int index) const;

    // Data Paths
    void addDataPath(const std::string& path, int type);
    int countDataPaths() const;
    const os::PatternMatcher& getDataPath(int index) const;

    // Data Types
    void addDataType(const std::string& type);
    int countDataTypes() const;
    std::string getDataType(int index) const;
    bool hasDataType(const std::string& type) const;

    // Matching
    int match(const std::string& action, const std::string& type, const std::string& scheme, const std::string& dataHost, int dataPort, const std::string& dataPath, const std::vector<std::string>& categories) const;
    int matchData(const std::string& type, const std::string& scheme, const std::string& dataHost, int dataPort, const std::string& dataPath) const;

    // NDK Binder
    binder_status_t writeToParcel(AParcel* parcel) const;
    binder_status_t readFromParcel(const AParcel* parcel);

    // Constants
    static constexpr int MATCH_CATEGORY_MASK = 0xfff0000;
    static constexpr int MATCH_ADJUSTMENT_MASK = 0x000ffff;
    static constexpr int MATCH_ADJUSTMENT_NORMAL = 0x8000;
    static constexpr int MATCH_CATEGORY_EMPTY = 0x0100000;
    static constexpr int MATCH_CATEGORY_SCHEME = 0x0200000;
    static constexpr int MATCH_CATEGORY_HOST = 0x0300000;
    static constexpr int MATCH_CATEGORY_PORT = 0x0400000;
    static constexpr int MATCH_CATEGORY_PATH = 0x0500000;
    static constexpr int MATCH_CATEGORY_SCHEME_SPECIFIC_PART = 0x0580000;
    static constexpr int MATCH_CATEGORY_TYPE = 0x0600000;

    static constexpr int NO_MATCH_TYPE = -1;
    static constexpr int NO_MATCH_DATA = -2;
    static constexpr int NO_MATCH_ACTION = -3;
    static constexpr int NO_MATCH_CATEGORY = -4;

private:
    std::vector<std::string> mActions;
    std::vector<std::string> mCategories;
    std::vector<std::string> mDataSchemes;
    std::vector<AuthorityEntry> mDataAuthorities;
    std::vector<os::PatternMatcher> mDataPaths;
    std::vector<std::string> mDataTypes;

    bool findMimeType(const std::string& type) const;
};

} // namespace android::content