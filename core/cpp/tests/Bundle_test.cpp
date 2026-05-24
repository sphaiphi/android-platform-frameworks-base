#include <gtest/gtest.h>
#include <android/os/Bundle.h>

using namespace android::os;

class BundleTest : public ::testing::Test {
protected:
    Bundle bundle;
};

TEST_F(BundleTest, PutAndGetInt) {
    bundle.putInt("key1", 42);
    auto result = bundle.getInt("key1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 42);
}

TEST_F(BundleTest, GetNonExistentKey) {
    auto result = bundle.getInt("nonexistent");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), BundleError::KeyNotFound);
}

TEST_F(BundleTest, TypeMismatch) {
    bundle.putInt("key1", 42);
    auto result = bundle.getString("key1");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), BundleError::TypeMismatch);
}

TEST_F(BundleTest, PutAndGetString) {
    bundle.putString("key1", "hello");
    auto result = bundle.getString("key1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "hello");
}

TEST_F(BundleTest, ClearAndIsEmpty) {
    EXPECT_TRUE(bundle.isEmpty());
    bundle.putInt("key1", 42);
    EXPECT_FALSE(bundle.isEmpty());
    bundle.clear();
    EXPECT_TRUE(bundle.isEmpty());
}

TEST_F(BundleTest, ContainsKey) {
    bundle.putInt("key1", 42);
    EXPECT_TRUE(bundle.containsKey("key1"));
    EXPECT_FALSE(bundle.containsKey("key2"));
}

TEST_F(BundleTest, Remove) {
    bundle.putInt("key1", 42);
    bundle.remove("key1");
    EXPECT_FALSE(bundle.containsKey("key1"));
}

TEST_F(BundleTest, OverwriteWithDifferentType) {
    bundle.putInt("key1", 42);
    bundle.putString("key1", "new value");
    auto result = bundle.getString("key1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, "new value");
    
    auto old_type_result = bundle.getInt("key1");
    ASSERT_FALSE(old_type_result.has_value());
    EXPECT_EQ(old_type_result.error(), BundleError::TypeMismatch);
}

TEST_F(BundleTest, PutAndGetStringArray) {
    std::vector<std::string> val = {"a", "b", "c"};
    bundle.putStringArray("key1", val);
    auto result = bundle.getStringArray("key1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, val);
}

TEST_F(BundleTest, NestedBundleDeep) {
    auto b1 = std::make_shared<Bundle>();
    auto b2 = std::make_shared<Bundle>();
    b2->putInt("val", 123);
    b1->putBundle("inner", b2);
    bundle.putBundle("outer", b1);
    
    auto r1 = bundle.getBundle("outer");
    ASSERT_TRUE(r1.has_value());
    auto r2 = (*r1)->getBundle("inner");
    ASSERT_TRUE(r2.has_value());
    auto r3 = (*r2)->getInt("val");
    ASSERT_TRUE(r3.has_value());
    EXPECT_EQ(*r3, 123);
}