#include <gtest/gtest.h>
#include <android/content/Intent.h>

using namespace android::content;
using namespace android::net;
using namespace android::graphics;

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

TEST_F(IntentTest, SetAndGetDataUri) {
    auto uri = Uri::parse("content://contacts/people/1");
    intent.setData(uri);
    auto data = intent.getData();
    ASSERT_TRUE(data.has_value());
    EXPECT_EQ(uri, *data);
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

TEST_F(IntentTest, FlagsManipulation) {
    intent.setFlags(0x1);
    EXPECT_EQ(intent.getFlags(), 0x1);
    intent.addFlags(0x2);
    EXPECT_EQ(intent.getFlags(), 0x3);
}

TEST_F(IntentTest, SetAndGetComponent) {
    ComponentName cn("com.pkg", "com.pkg.Class");
    intent.setComponent(cn);
    auto comp = intent.getComponent();
    ASSERT_TRUE(comp.has_value());
    EXPECT_EQ(cn, *comp);
}

TEST_F(IntentTest, SetSourceBounds) {
    Rect bounds(1, 2, 3, 4);
    intent.setSourceBounds(bounds);
    auto b = intent.getSourceBounds();
    ASSERT_TRUE(b.has_value());
    EXPECT_EQ(bounds, *b);
}

TEST_F(IntentTest, FilterEquals) {
    Intent intent1("action1");
    intent1.setData(Uri::parse("http://test"));
    
    Intent intent2("action1");
    intent2.setData(Uri::parse("http://test"));
    
    EXPECT_TRUE(intent1.filterEquals(intent2));
    
    intent2.setAction("action2");
    EXPECT_FALSE(intent1.filterEquals(intent2));
}

TEST_F(IntentTest, SelectorRecursion) {
    auto selector = std::make_shared<Intent>("selector_action");
    intent.setSelector(selector);
    auto s = intent.getSelector();
    ASSERT_TRUE(s != nullptr);
    EXPECT_EQ("selector_action", s->getAction().value_or(""));
}