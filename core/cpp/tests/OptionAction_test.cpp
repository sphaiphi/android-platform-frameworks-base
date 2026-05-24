#include <gtest/gtest.h>
#include <android/app/ActivityOptions.h>
#include <android/app/ActivityTransitionState.h>
#include <android/app/AsyncNotedAppOp.h>

using namespace android::app;

TEST(OptionActionTest, ActivityOptions) {
    auto options = ActivityOptions::make_custom_animation(10, 20);
    auto bundle = options->to_bundle();
    EXPECT_EQ(bundle.getInt("android:activity.animEnterRes").value(), 10);
    EXPECT_EQ(bundle.getInt("android:activity.animExitRes").value(), 20);
}

TEST(OptionActionTest, ActivityTransitionState) {
    ActivityTransitionState state;
    // Basic construction
}

TEST(OptionActionTest, AsyncNotedAppOp) {
    AsyncNotedAppOp op(1, 1000, "tag", "msg", 123456789L);
    EXPECT_EQ(op.get_op_code(), 1);
    EXPECT_EQ(op.get_noting_uid(), 1000);
    EXPECT_EQ(op.get_attribution_tag(), "tag");
    EXPECT_EQ(op.get_message(), "msg");
    EXPECT_EQ(op.get_time(), 123456789L);
}
