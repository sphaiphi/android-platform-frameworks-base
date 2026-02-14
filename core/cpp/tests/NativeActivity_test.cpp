#include <gtest/gtest.h>
#include <android/app/NativeActivity.h>
#include <android/os/Bundle.h>
#include <android/content/res/Configuration.h>

using namespace android::app;
using namespace android::os;
using namespace android::content::res;

class PublicNativeActivity : public NativeActivity {
public:
    using NativeActivity::on_configuration_changed;
    using NativeActivity::on_low_memory;
};

TEST(NativeActivityTest, Construction) {
    NativeActivity activity;
    EXPECT_EQ(activity.get_state(), ActivityState::initialized);
}

TEST(NativeActivityTest, LifecycleTransitions) {
    NativeActivity activity;
    Bundle icicle;
    
    EXPECT_TRUE(activity.perform_create(icicle).has_value());
    EXPECT_EQ(activity.get_state(), ActivityState::created);
    
    EXPECT_TRUE(activity.perform_start().has_value());
    EXPECT_EQ(activity.get_state(), ActivityState::started);
    
    EXPECT_TRUE(activity.perform_resume().has_value());
    EXPECT_EQ(activity.get_state(), ActivityState::resumed);
    
    EXPECT_TRUE(activity.perform_pause().has_value());
    EXPECT_EQ(activity.get_state(), ActivityState::paused);
    
    EXPECT_TRUE(activity.perform_stop().has_value());
    EXPECT_EQ(activity.get_state(), ActivityState::stopped);
    
    EXPECT_TRUE(activity.perform_destroy().has_value());
    EXPECT_EQ(activity.get_state(), ActivityState::destroyed);
}

TEST(NativeActivityTest, NativeHandleManagement) {
    NativeActivity activity;
    EXPECT_EQ(activity.get_native_handle(), 0);
}

TEST(NativeActivityTest, SystemCallbacks) {
    PublicNativeActivity activity;
    Configuration config;
    
    // These should not crash
    activity.on_configuration_changed(config);
    activity.on_low_memory();
    activity.on_window_focus_changed(true);
}
