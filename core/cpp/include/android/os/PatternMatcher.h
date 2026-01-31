#pragma once

#include <string>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::os {

class PatternMatcher {
public:
    static constexpr int PATTERN_LITERAL = 0;
    static constexpr int PATTERN_PREFIX = 1;
    static constexpr int PATTERN_SIMPLE_GLOB = 2;
    static constexpr int PATTERN_ADVANCED_GLOB = 3;
    static constexpr int PATTERN_SUFFIX = 4;

    PatternMatcher() = default;
    PatternMatcher(std::string pattern, int type);

    [[nodiscard]] const std::string& getPath() const { return mPattern; }
    [[nodiscard]] int getType() const { return mType; }

    [[nodiscard]] bool match(const std::string& str) const;

    // NDK Binder
    binder_status_t writeToParcel(AParcel* parcel) const;
    binder_status_t readFromParcel(const AParcel* parcel);

private:
    std::string mPattern;
    int mType{PATTERN_LITERAL};

    static bool matchGlob(const std::string& pattern, const std::string& str);
};

} // namespace android::os
