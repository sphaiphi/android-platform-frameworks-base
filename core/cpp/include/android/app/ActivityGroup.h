#pragma once

#include <android/app/Activity.h>

namespace android::app {

/**
 * A screen that contains multiple activities.
 */
class ActivityGroup : public Activity {
public:
    ActivityGroup();
    explicit ActivityGroup(bool single_activity_mode);
    virtual ~ActivityGroup() = default;

private:
    bool single_activity_mode_{true};
};

} // namespace android::app
