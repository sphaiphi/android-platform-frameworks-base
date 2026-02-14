#include <android/app/ActivityGroup.h>

namespace android::app {

ActivityGroup::ActivityGroup() : Activity() {}

ActivityGroup::ActivityGroup(bool single_activity_mode) : Activity(), single_activity_mode_(single_activity_mode) {}

} // namespace android::app
