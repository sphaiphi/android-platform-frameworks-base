#include <gtest/gtest.h>
#include <android/app/AppOpsManager.h>

using namespace android::app;

TEST(AppOpsManagerTest, Constants) {
    EXPECT_EQ(AppOpsManager::MODE_ALLOWED, 0);
    EXPECT_EQ(AppOpsManager::OP_COARSE_LOCATION, 0); // TBD: Define actual codes
}

TEST(AppOpsManagerTest, CheckOp) {
    AppOpsManager ops;
    // Basic check without service should return default or error
    EXPECT_EQ(ops.check_op(AppOpsManager::OP_COARSE_LOCATION, 1000, "com.example"), AppOpsManager::MODE_ALLOWED);
}
