#include <gtest/gtest.h>
#include <android/view/View.h>
#include <android/view/ViewGroup.h>

TEST(ViewTest, VisibilityManagement) {
    using namespace android::view;
    View view;
    
    // Default visibility should be VISIBLE
    EXPECT_EQ(View::VISIBLE, view.get_visibility());
    
    view.set_visibility(View::INVISIBLE);
    EXPECT_EQ(View::INVISIBLE, view.get_visibility());
    
    view.set_visibility(View::GONE);
    EXPECT_EQ(View::GONE, view.get_visibility());
    
    view.set_visibility(View::VISIBLE);
    EXPECT_EQ(View::VISIBLE, view.get_visibility());
}

TEST(ViewTest, IdManagement) {
    using namespace android::view;
    View view;
    
    EXPECT_EQ(View::NO_ID, view.get_id());
    
    view.set_id(100);
    EXPECT_EQ(100, view.get_id());
}

TEST(ViewTest, EnabledState) {
    using namespace android::view;
    View view;
    
    EXPECT_TRUE(view.is_enabled());
    
    view.set_enabled(false);
    EXPECT_FALSE(view.is_enabled());
}

TEST(ViewTest, CoordinateSystem) {
    using namespace android::view;
    View view;
    
    // Initial coordinates should be zero
    EXPECT_EQ(0, view.get_left());
    EXPECT_EQ(0, view.get_top());
    EXPECT_EQ(0, view.get_right());
    EXPECT_EQ(0, view.get_bottom());
    EXPECT_EQ(0, view.get_width());
    EXPECT_EQ(0, view.get_height());

    view.layout(10, 20, 110, 120);
    EXPECT_EQ(10, view.get_left());
    EXPECT_EQ(20, view.get_top());
    EXPECT_EQ(110, view.get_right());
    EXPECT_EQ(120, view.get_bottom());
    EXPECT_EQ(100, view.get_width());
    EXPECT_EQ(100, view.get_height());
}

TEST(ViewTest, MeasurePass) {
    using namespace android::view;
    View view;
    
    // Initial measured dimensions should be zero
    EXPECT_EQ(0, view.get_measured_width());
    EXPECT_EQ(0, view.get_measured_height());

    // Simple measure call (specs simplified for now)
    view.measure(100, 200);
    EXPECT_EQ(100, view.get_measured_width());
    EXPECT_EQ(200, view.get_measured_height());
}

TEST(ViewTest, GetResources) {
    using namespace android::view;
    View view;
    // In our C++ implementation, we don't have a full Resources object yet,
    // but we can verify the architectural intent if/when it's added.
    // For now, this is a placeholder for CTS parity.
}

TEST(ViewTest, GetParent) {
    using namespace android::view;
    auto parent = std::make_shared<ViewGroup>();
    auto child = std::make_shared<View>();
    
    EXPECT_EQ(nullptr, child->get_parent());
    parent->add_view(child);
    EXPECT_EQ(parent.get(), child->get_parent());
}

TEST(ViewTest, FindViewById) {
    using namespace android::view;
    ViewGroup parent;
    auto child = std::make_shared<View>();
    child->set_id(100);
    parent.add_view(child);
    
    // In a real implementation, findViewById would traverse the hierarchy.
    // Our current ViewGroup doesn't implement it yet, so this serves as a 
    // requirement for Phase 5 if needed, or we can implement a simple version.
}
