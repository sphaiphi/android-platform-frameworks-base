#include <gtest/gtest.h>
#include <android/app/Activity.h>
#include <android/os/Bundle.h>
#include <vector>
#include <string>

using namespace android::app;
using namespace android::os;

/**
 * Port of android.app.cts.LifecycleTest and ActivityCallbacksTest logic.
 * Ensures the C++ Activity implementation follows standard lifecycle state transitions.
 */

namespace android::app::cts {

class MockActivity : public Activity {
public:
    std::vector<ActivityState> states;

protected:
    auto on_create(const Bundle&) -> void override { states.push_back(ActivityState::created); }
    auto on_start() -> void override { states.push_back(ActivityState::started); }
    auto on_resume() -> void override { states.push_back(ActivityState::resumed); }
    auto on_pause() -> void override { states.push_back(ActivityState::paused); }
    auto on_stop() -> void override { states.push_back(ActivityState::stopped); }
    auto on_destroy() -> void override { states.push_back(ActivityState::destroyed); }
};

class ActivityCtsTest : public ::testing::Test {
protected:
    MockActivity activity;
    Bundle empty_bundle;
};

TEST_F(ActivityCtsTest, TestBasicLifecycle) {
    // Initial -> Created
    activity.perform_create(empty_bundle);
    EXPECT_EQ(activity.get_state(), ActivityState::created);
    ASSERT_EQ(activity.states.size(), 1);
    EXPECT_EQ(activity.states[0], ActivityState::created);

    // Created -> Started
    activity.perform_start();
    EXPECT_EQ(activity.get_state(), ActivityState::started);
    ASSERT_EQ(activity.states.size(), 2);
    EXPECT_EQ(activity.states[1], ActivityState::started);

    // Started -> Resumed
    activity.perform_resume();
    EXPECT_EQ(activity.get_state(), ActivityState::resumed);
    ASSERT_EQ(activity.states.size(), 3);
    EXPECT_EQ(activity.states[2], ActivityState::resumed);

    // Resumed -> Paused
    activity.perform_pause();
    EXPECT_EQ(activity.get_state(), ActivityState::paused);
    ASSERT_EQ(activity.states.size(), 4);
    EXPECT_EQ(activity.states[3], ActivityState::paused);

    // Paused -> Stopped
    activity.perform_stop();
    EXPECT_EQ(activity.get_state(), ActivityState::stopped);
    ASSERT_EQ(activity.states.size(), 5);
    EXPECT_EQ(activity.states[4], ActivityState::stopped);

    // Stopped -> Destroyed
    activity.perform_destroy();
    EXPECT_EQ(activity.get_state(), ActivityState::destroyed);
    ASSERT_EQ(activity.states.size(), 6);
    EXPECT_EQ(activity.states[5], ActivityState::destroyed);
}

TEST_F(ActivityCtsTest, TestRestartLifecycle) {
    activity.perform_create(empty_bundle);
    activity.perform_start();
    activity.perform_resume();
    
    // Resume -> Pause -> Stop
    activity.perform_pause();
    activity.perform_stop();
    EXPECT_EQ(activity.get_state(), ActivityState::stopped);
    
    // Clear log to check subsequent transitions clearly
    activity.states.clear();
    
    // Stop -> Start -> Resume (Simulating returning to activity)
    activity.perform_start();
    activity.perform_resume();
    EXPECT_EQ(activity.get_state(), ActivityState::resumed);
    
    ASSERT_EQ(activity.states.size(), 2);
    EXPECT_EQ(activity.states[0], ActivityState::started);
    EXPECT_EQ(activity.states[1], ActivityState::resumed);
}

} // namespace android::app::cts
