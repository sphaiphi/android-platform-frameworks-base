#include <gtest/gtest.h>
#include <android/content/Intent.h>

using namespace android::content;

class IntentCtsTest : public ::testing::Test {
protected:
    Intent intent;
};

TEST_F(IntentCtsTest, BasicOperations) {
    intent.setAction("ACTION_TEST");
    intent.addCategory("CATEGORY_TEST");
    intent.putExtra("extra", 123);
    
    auto action = intent.getAction();
    ASSERT_TRUE(action.has_value());
    EXPECT_EQ(*action, "ACTION_TEST");

    EXPECT_TRUE(intent.hasCategory("CATEGORY_TEST"));
    EXPECT_EQ(intent.getExtras().getInt("extra").value_or(0), 123);
}
