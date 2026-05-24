#include <gtest/gtest.h>
#include <android/app/Activity.h>
#include <android/app/ActivityThread.h>
#include <android/content/Intent.h>
#include <android/app/ContextImpl.h>

using namespace android::app;
using namespace android::content;

class ActivityCtsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // ActivityThread::system_main prepares the looper and sets current thread
        thread = ActivityThread::system_main();
        thread->bind_application("android.cts.activity");
    }

    void TearDown() override {
        if (thread) {
            thread->detach();
        }
    }

    std::shared_ptr<ActivityThread> thread;
};

TEST_F(ActivityCtsTest, LifecycleCompliance) {
    auto r = std::make_shared<ActivityThread::ActivityClientRecord>();
    r->intent = std::make_shared<Intent>("android.intent.action.MAIN");
    
    // 1. Launch -> Created
    thread->handle_launch_activity(r);
    ASSERT_NE(r->activity, nullptr);
    EXPECT_EQ(r->activity->get_state(), ActivityState::created);
    
    // 2. Resume -> Resumed (also calls onStart)
    thread->handle_resume_activity(r.get(), true, false);
    EXPECT_EQ(r->activity->get_state(), ActivityState::resumed);

    // 3. Pause -> Paused
    thread->handle_pause_activity(r.get(), false, false, 0);
    EXPECT_EQ(r->activity->get_state(), ActivityState::paused);
}

TEST_F(ActivityCtsTest, ContextAndIntentCompliance) {
    auto r = std::make_shared<ActivityThread::ActivityClientRecord>();
    r->intent = std::make_shared<Intent>("android.intent.action.VIEW");
    
    thread->handle_launch_activity(r);
    
    auto activity = r->activity;
    EXPECT_EQ(activity->get_package_name(), "android.cts.activity");
    
    auto intent = activity->get_intent();
    ASSERT_NE(intent, nullptr);
    auto action = intent->getAction();
    ASSERT_TRUE(action.has_value());
    EXPECT_EQ(*action, "android.intent.action.VIEW");
}
