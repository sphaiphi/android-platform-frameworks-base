#include <android/os/PatternMatcher.h>
#include <android/binder_parcel.h>
#include <android/binder_status.h>
#include <algorithm>

namespace android::os {

PatternMatcher::PatternMatcher(std::string pattern, int type)
    : mPattern(std::move(pattern)), mType(type) {
}

bool PatternMatcher::match(const std::string& str) const {
    if (mType == PATTERN_LITERAL) {
        return mPattern == str;
    } else if (mType == PATTERN_PREFIX) {
        return str.compare(0, mPattern.length(), mPattern) == 0;
    } else if (mType == PATTERN_SUFFIX) {
        if (str.length() < mPattern.length()) return false;
        return str.compare(str.length() - mPattern.length(), mPattern.length(), mPattern) == 0;
    } else if (mType == PATTERN_SIMPLE_GLOB) {
        return matchGlob(mPattern, str);
    }
    // Advanced glob not implemented for now
    return false;
}

bool PatternMatcher::matchGlob(const std::string& pattern, const std::string& match) {
    const size_t NP = pattern.length();
    if (NP == 0) {
        return match.length() == 0;
    }
    const size_t NM = match.length();
    size_t ip = 0, im = 0;
    char nextChar = pattern[0];
    while ((ip < NP) && (im < NM)) {
        char c = nextChar;
        ip++;
        nextChar = ip < NP ? pattern[ip] : 0;
        const bool escaped = (c == '\\');
        if (escaped) {
            c = nextChar;
            ip++;
            nextChar = ip < NP ? pattern[ip] : 0;
        }
        if (nextChar == '*') {
            if (!escaped && c == '.') {
                if (ip >= (NP - 1)) {
                    return true;
                }
                ip++;
                nextChar = pattern[ip];
                if (nextChar == '\\') {
                    ip++;
                    nextChar = ip < NP ? pattern[ip] : 0;
                }
                do {
                    if (match[im] == nextChar) {
                        break;
                    }
                    im++;
                } while (im < NM);
                if (im == NM) {
                    return false;
                }
                ip++;
                nextChar = ip < NP ? pattern[ip] : 0;
                im++;
            } else {
                do {
                    if (match[im] != c) {
                        break;
                    }
                    im++;
                } while (im < NM);
                ip++;
                nextChar = ip < NP ? pattern[ip] : 0;
            }
        } else {
            if (c != '.' && match[im] != c) return false;
            im++;
        }
    }

    if (ip >= NP && im >= NM) {
        return true;
    }

    if (ip == NP - 2 && pattern[ip] == '.' && pattern[ip + 1] == '*') {
        return true;
    }

    return false;
}

binder_status_t PatternMatcher::writeToParcel(AParcel* parcel) const {
    binder_status_t status = AParcel_writeString(parcel, mPattern.c_str(), mPattern.length());
    if (status != STATUS_OK) return status;
    status = AParcel_writeInt32(parcel, mType);
    return status;
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

binder_status_t PatternMatcher::readFromParcel(const AParcel* parcel) {
    binder_status_t status = AParcel_readString(parcel, &mPattern, string_allocator);
    if (status != STATUS_OK) return status;
    if (!mPattern.empty() && mPattern.back() == '\0') mPattern.pop_back();
    status = AParcel_readInt32(parcel, &mType);
    return status;
}

} // namespace android::os
