#include <gtest/gtest.h>
#include <android/content/ComponentName.h>

using namespace android::content;

TEST(ComponentNameTest, Constructor) {
    ComponentName cn("com.example", "com.example.MyActivity");
    EXPECT_EQ("com.example", cn.getPackageName());
    EXPECT_EQ("com.example.MyActivity", cn.getClassName());
}

TEST(ComponentNameTest, ConstructorEmptyThrows) {
    EXPECT_THROW(ComponentName("", "Class"), std::invalid_argument);
    EXPECT_THROW(ComponentName("Pkg", ""), std::invalid_argument);
}

TEST(ComponentNameTest, CreateRelative) {
    auto cn = ComponentName::createRelative("com.example", ".MyActivity");
    EXPECT_EQ("com.example", cn.getPackageName());
    EXPECT_EQ("com.example.MyActivity", cn.getClassName());
}

TEST(ComponentNameTest, FlattenToString) {
    ComponentName cn("com.example", "com.example.MyActivity");
    EXPECT_EQ("com.example/com.example.MyActivity", cn.flattenToString());
}

TEST(ComponentNameTest, UnflattenFromString) {
    auto cn = ComponentName::unflattenFromString("com.example/com.example.MyActivity");
    ASSERT_TRUE(cn.has_value());
    EXPECT_EQ("com.example", cn->getPackageName());
    EXPECT_EQ("com.example.MyActivity", cn->getClassName());
}

TEST(ComponentNameTest, UnflattenFromStringRelative) {
    auto cn = ComponentName::unflattenFromString("com.example/.MyActivity");
    ASSERT_TRUE(cn.has_value());
    EXPECT_EQ("com.example", cn->getPackageName());
    EXPECT_EQ("com.example.MyActivity", cn->getClassName());
}

TEST(ComponentNameTest, Equality) {
    ComponentName cn1("com.example", "Activity");
    ComponentName cn2("com.example", "Activity");
    ComponentName cn3("com.other", "Activity");
    EXPECT_EQ(cn1, cn2);
    EXPECT_NE(cn1, cn3);
}

TEST(ComponentNameTest, ShortClassName) {
    ComponentName cn("com.example", "com.example.app.Activity");
    EXPECT_EQ(".app.Activity", cn.getShortClassName());
    
    ComponentName cn2("com.example", "other.app.Activity");
    EXPECT_EQ("other.app.Activity", cn2.getShortClassName());
}
