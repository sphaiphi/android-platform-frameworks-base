#pragma once

#include <memory>
#include <vector>
#include <string>

namespace android::app {

class ActivityTransitionCoordinator {
public:
    virtual ~ActivityTransitionCoordinator() = default;

protected:
    ActivityTransitionCoordinator() = default;
};

} // namespace android::app
