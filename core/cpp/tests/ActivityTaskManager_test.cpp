#include <gtest/gtest.h>
#include <android/app/ActivityTaskManager.h>

using namespace android::app;

TEST(ActivityTaskManagerTest, GetService) {
    auto service = ActivityTaskManager::get_service();
    // In unit tests without actual binder, this might be null or mock
    EXPECT_EQ(service, nullptr); 
}
