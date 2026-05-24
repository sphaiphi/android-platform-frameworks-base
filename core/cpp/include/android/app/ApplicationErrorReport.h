#pragma once

#include <string>
#include <memory>
#include <vector>
#include <cstdint>

namespace android::app {

/**
 * Describes an application error.
 */
class ApplicationErrorReport {
public:
    enum ErrorType {
        TYPE_NONE = 0,
        TYPE_CRASH = 1,
        TYPE_ANR = 2,
        TYPE_BATTERY = 3,
        TYPE_RUNNING_SERVICE = 5
    };

    struct CrashInfo {
        std::string exceptionClassName;
        std::string exceptionMessage;
        std::string throwFileName;
        std::string throwClassName;
        std::string throwMethodName;
        int32_t throwLineNumber{0};
        std::string stackTrace;
    };

    struct AnrInfo {
        std::string activity;
        std::string cause;
        std::string info;
    };

    ApplicationErrorReport() = default;

    ErrorType type{TYPE_NONE};
    std::string packageName;
    std::string installerPackageName;
    std::string processName;
    int64_t time{0};
    bool systemApp{false};

    std::unique_ptr<CrashInfo> crashInfo;
    std::unique_ptr<AnrInfo> anrInfo;
};

} // namespace android::app
