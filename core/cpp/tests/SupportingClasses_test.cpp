#include <gtest/gtest.h>
#include <android/app/Fragment.h>
#include <android/app/FragmentManager.h>
#include <android/app/LoaderManager.h>

using namespace android::app;

TEST(SupportingClassesTest, FragmentTag) {
    Fragment f;
    f.set_tag("test_tag");
    ASSERT_TRUE(f.get_tag().has_value());
    EXPECT_EQ(f.get_tag().value(), "test_tag");
}

TEST(SupportingClassesTest, FragmentManagerFind) {
    FragmentManagerImpl fm;
    auto f1 = std::make_shared<Fragment>();
    f1->set_tag("f1");
    fm.add_fragment(f1);
    
    auto found = fm.find_fragment_by_tag("f1");
    EXPECT_EQ(found, f1);
    
    auto not_found = fm.find_fragment_by_tag("unknown");
    EXPECT_EQ(not_found, nullptr);
}

TEST(SupportingClassesTest, LoaderManagerNoOp) {
    LoaderManagerImpl lm;
    lm.do_start();
    lm.do_stop();
    lm.do_destroy();
}
