#pragma once

#include <memory>
#include <vector>

namespace android::app {

class IActivityTaskManager {
public:
    virtual ~IActivityTaskManager() = default;
};

class ActivityTaskManager {
public:
    ActivityTaskManager() = default;
    static auto getInstance() -> ActivityTaskManager&;

    auto remove_task(int task_id) -> bool;
};

} // namespace android::app
