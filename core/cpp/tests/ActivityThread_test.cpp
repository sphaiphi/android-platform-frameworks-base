#include <gtest/gtest.h>
#include <android/app/ActivityThread.h>

using namespace android::app;

class ActivityThreadTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure we start with a clean state
    }
};

TEST_F(ActivityThreadTest, SystemMain) {
    auto thread = ActivityThread::system_main();
    ASSERT_NE(thread, nullptr);
    EXPECT_EQ(ActivityThread::current_activity_thread(), thread);
}

TEST_F(ActivityThreadTest, BindApplication) {
    auto thread = std::make_shared<ActivityThread>();
    thread->bind_application("com.example.app");
    EXPECT_EQ(thread->get_process_name(), "com.example.app");
}

TEST_F(ActivityThreadTest, LaunchActivityFlow) {
    auto thread = ActivityThread::system_main();
    thread->bind_application("com.example.app");

    auto r = std::make_shared<ActivityThread::ActivityClientRecord>();
    r->intent = std::make_shared<android::content::Intent>("android.intent.action.MAIN");
    
    thread->handle_launch_activity(r);
    
    ASSERT_NE(r->activity, nullptr);
    EXPECT_EQ(r->activity->get_state(), ActivityState::created);
    
    thread->handle_resume_activity(r.get(), true, false);
    EXPECT_EQ(r->activity->get_state(), ActivityState::resumed);

    thread->handle_pause_activity(r.get(), false, false, 0);
    EXPECT_EQ(r->activity->get_state(), ActivityState::paused);
    
    EXPECT_EQ(r->activity->get_package_name(), "com.example.app");
    ASSERT_NE(r->activity->get_intent(), nullptr);
    auto action = r->activity->get_intent()->getAction();
    ASSERT_TRUE(action.has_value());
    EXPECT_EQ(action.value(), "android.intent.action.MAIN");
}

TEST_F(ActivityThreadTest, HHandlerInitialState) {
    auto thread = ActivityThread::system_main();
    EXPECT_NE(thread, nullptr);
}
