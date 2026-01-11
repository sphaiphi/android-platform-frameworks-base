#include <gtest/gtest.h>
#include <android/content/Intent.h>

using namespace android::content;
using namespace android::os;

class IntentTest : public ::testing::Test {
protected:
    Intent intent;
};

TEST_F(IntentTest, SetAndGetAction) {
    intent.setAction("android.intent.action.VIEW");
    auto action = intent.getAction();
    ASSERT_TRUE(action.has_value());
    EXPECT_EQ(action.value(), "android.intent.action.VIEW");
}

TEST_F(IntentTest, GetUnsetAction) {
    auto action = intent.getAction();
    ASSERT_FALSE(action.has_value());
    EXPECT_EQ(action.error(), IntentError::ActionNotSet);
}

TEST_F(IntentTest, SetAndGetData) {
    intent.setData("content://contacts/people/1");
    auto data = intent.getData();
    ASSERT_TRUE(data.has_value());
    EXPECT_EQ(data.value(), "content://contacts/people/1");
}

TEST_F(IntentTest, GetUnsetData) {
    auto data = intent.getData();
    ASSERT_FALSE(data.has_value());
    EXPECT_EQ(data.error(), IntentError::DataNotSet);
}

TEST_F(IntentTest, AddAndHasCategory) {
    intent.addCategory("android.intent.category.LAUNCHER");
    EXPECT_TRUE(intent.hasCategory("android.intent.category.LAUNCHER"));
    EXPECT_FALSE(intent.hasCategory("android.intent.category.DEFAULT"));
}

TEST_F(IntentTest, PutAndGetExtra) {
    intent.putExtra("key1", 42);
    EXPECT_TRUE(intent.hasExtra("key1"));
    EXPECT_FALSE(intent.hasExtra("key2"));
    auto& extras = intent.getExtras();
    auto result = extras.getInt("key1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 42);
}

TEST_F(IntentTest, PutExtrasIntegration) {
    Bundle extras;
    extras.putInt("int_key", 100);
    extras.putString("str_key", "value");
    
    intent.putExtras(extras);
    
    EXPECT_TRUE(intent.hasExtra("int_key"));
    EXPECT_TRUE(intent.hasExtra("str_key"));
    
    auto& retrievedExtras = intent.getExtras();
    auto intVal = retrievedExtras.getInt("int_key");
    auto strVal = retrievedExtras.getString("str_key");
    
    ASSERT_TRUE(intVal.has_value());
    EXPECT_EQ(intVal.value(), 100);
    ASSERT_TRUE(strVal.has_value());
    EXPECT_EQ(strVal.value(), "value");
}

TEST_F(IntentTest, MultipleCategories) {
    intent.addCategory("cat1");
    intent.addCategory("cat2");
    EXPECT_TRUE(intent.hasCategory("cat1"));
    EXPECT_TRUE(intent.hasCategory("cat2"));
    EXPECT_EQ(intent.getCategories().size(), 2);
    
    intent.removeCategory("cat1");
    EXPECT_FALSE(intent.hasCategory("cat1"));
    EXPECT_TRUE(intent.hasCategory("cat2"));
}

TEST_F(IntentTest, FlagsManipulation) {
    intent.setFlags(0x1);
    EXPECT_EQ(intent.getFlags(), 0x1);
    intent.addFlags(0x2);
    EXPECT_EQ(intent.getFlags(), 0x3);
}

TEST_F(IntentTest, TypeManipulation) {
    intent.setType("text/plain");
    auto type = intent.getType();
    ASSERT_TRUE(type.has_value());
    EXPECT_EQ(*type, "text/plain");
}

