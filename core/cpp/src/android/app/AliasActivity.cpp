#include <android/app/AliasActivity.h>

namespace android::app {

AliasActivity::AliasActivity() : Activity() {}

void AliasActivity::on_create(const android::os::Bundle& saved_instance_state) {
    Activity::on_create(saved_instance_state);
    // TBD: Parse meta-data and launch target activity
}

} // namespace android::app
