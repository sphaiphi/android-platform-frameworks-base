#include <gtest/gtest.h>
#include <android/os/Bundle.h>

using namespace android::os;

class BundleCtsTest : public ::testing::Test {
protected:
    Bundle bundle;
};

TEST_F(BundleCtsTest, BasicOperations) {
    bundle.putInt("int", 1);
    bundle.putString("string", "test");
    
    EXPECT_EQ(bundle.getInt("int").value_or(0), 1);
    EXPECT_EQ(bundle.getString("string").value_or(""), "test");
    EXPECT_EQ(bundle.size(), 2);
}

TEST_F(BundleCtsTest, NestedBundles) {
    auto inner = std::make_shared<Bundle>();
    inner->putInt("inner_int", 100);
    
    bundle.putBundle("inner", inner);
    
    auto retrieved = bundle.getBundle("inner");
    ASSERT_TRUE(retrieved.has_value());
    EXPECT_EQ((*retrieved)->getInt("inner_int").value_or(0), 100);
}
