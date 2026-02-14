#pragma once

#include <android/app/Activity.h>

namespace android::app {

/**
 * Stub activity used to launch another activity.
 */
class AliasActivity : public Activity {
public:
    AliasActivity();
    virtual ~AliasActivity() = default;

protected:
    void on_create(const android::os::Bundle& saved_instance_state) override;
};

} // namespace android::app
