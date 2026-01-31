#include <gtest/gtest.h>
#include <android/app/Instrumentation.h>
#include <android/app/Activity.h>

using namespace android::app;
using namespace android::os;

class InstrumentationTest : public ::testing::Test {
protected:
    Instrumentation instr;
    Bundle empty_bundle;
};

TEST_F(InstrumentationTest, NewActivity) {
    auto activity = instr.new_activity("TestActivity");
    ASSERT_NE(activity, nullptr);
    EXPECT_EQ(activity->get_state(), ActivityState::initialized);
}

TEST_F(InstrumentationTest, CallActivityOnCreate) {
    auto activity = std::make_shared<Activity>();
    instr.call_activity_on_create(activity, empty_bundle);
    EXPECT_EQ(activity->get_state(), ActivityState::created);
}

TEST_F(InstrumentationTest, LifecycleSequence) {
    auto activity = std::make_shared<Activity>();
    instr.call_activity_on_create(activity, empty_bundle);
    instr.call_activity_on_start(activity);
    instr.call_activity_on_resume(activity);
    EXPECT_EQ(activity->get_state(), ActivityState::resumed);
    
    instr.call_activity_on_pause(activity);
    instr.call_activity_on_stop(activity);
    instr.call_activity_on_destroy(activity);
    EXPECT_EQ(activity->get_state(), ActivityState::destroyed);
}
