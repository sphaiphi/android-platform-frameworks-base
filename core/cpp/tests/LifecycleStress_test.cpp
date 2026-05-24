#include <gtest/gtest.h>
#include <android/app/ActivityThread.h>
#include <android/app/Instrumentation.h>
#include <android/app/Activity.h>

using namespace android::app;

class LifecycleStressTest : public ::testing::Test {
protected:
    void SetUp() override {
        thread = ActivityThread::system_main();
        thread->bind_application("com.stress.test");
    }

    void TearDown() override {
        if (thread) {
            thread->detach();
        }
    }

    std::shared_ptr<ActivityThread> thread;
};

TEST_F(LifecycleStressTest, RapidLaunchResumePause) {
    for (int i = 0; i < 100; ++i) {
        auto r = std::make_shared<ActivityThread::ActivityClientRecord>();
        r->intent = std::make_shared<android::content::Intent>("android.intent.action.MAIN");
        
        thread->handle_launch_activity(r);
        thread->handle_resume_activity(r.get(), true, false);
        thread->handle_pause_activity(r.get(), false, false, 0);
        thread->handle_stop_activity(r.get(), false, 0);
        thread->handle_destroy_activity(r.get(), false, 0, false);
    }
}
