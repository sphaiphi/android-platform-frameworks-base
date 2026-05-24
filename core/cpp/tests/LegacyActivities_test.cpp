#include <gtest/gtest.h>
#include <android/app/ActivityGroup.h>
#include <android/app/AliasActivity.h>

using namespace android::app;

TEST(ActivityGroupTest, Construction) {
    ActivityGroup group;
    EXPECT_EQ(group.get_state(), ActivityState::initialized);
}

TEST(AliasActivityTest, Construction) {
    AliasActivity alias;
    EXPECT_EQ(alias.get_state(), ActivityState::initialized);
}
