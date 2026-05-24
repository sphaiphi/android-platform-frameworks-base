#pragma once

#include <memory>

namespace android::app {

class IActivityTaskManager {
public:
    virtual ~IActivityTaskManager() = default;
};

/**
 * Interface for interacting with the window manager task system.
 */
class ActivityTaskManager {
public:
    ActivityTaskManager() = default;

    /**
     * @hide
     */
    static auto get_service() -> std::shared_ptr<IActivityTaskManager>;
};

} // namespace android::app
