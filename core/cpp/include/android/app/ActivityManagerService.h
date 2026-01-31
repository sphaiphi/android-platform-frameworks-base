#pragma once

#include <android/app/ActivityManager.h> // For TaskDescription
#include <memory>
#include <vector>
#include <string>

namespace android::app {

class IActivityManager {
public:
    virtual ~IActivityManager() = default;
    // TBD: Define methods as needed from AIDL
};

class ActivityManager {
public:
    ActivityManager() = default;
    
    // TBD: Implement methods from spec
};

} // namespace android::app
