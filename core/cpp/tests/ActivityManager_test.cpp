#include <gtest/gtest.h>
#include <android/app/ActivityManager.h>

using namespace android::app;

TEST(ActivityManagerTest, GetRunningAppProcesses) {
    ActivityManager am;
    auto processes = am.get_running_app_processes();
    // Currently returns empty vector as TBD
    EXPECT_TRUE(processes.empty());
}

TEST(ActivityManagerTest, GetMyMemoryState) {
    ActivityManager am;
    ActivityManager::RunningAppProcessInfo info;
    am.get_my_memory_state(&info);
    EXPECT_EQ(info.pid, 0); // TBD: Mock actual pid
}
