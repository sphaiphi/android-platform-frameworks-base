#include <gtest/gtest.h>
#include <android/view/ViewGroup.h>
#include <android/view/View.h>
#include <memory>

using namespace android::view;

class ViewGroupTest : public ::testing::Test {
protected:
    std::shared_ptr<ViewGroup> parent;

    void SetUp() override {
        parent = std::make_shared<ViewGroup>();
    }
};

TEST_F(ViewGroupTest, InitialState) {
    EXPECT_EQ(0, parent->get_child_count());
}

TEST_F(ViewGroupTest, AddView) {
    auto child = std::make_shared<View>();
    parent->add_view(child);

    EXPECT_EQ(1, parent->get_child_count());
    EXPECT_EQ(child, parent->get_child_at(0));
    EXPECT_EQ(parent.get(), child->get_parent());
}

TEST_F(ViewGroupTest, RemoveView) {
    auto child = std::make_shared<View>();
    parent->add_view(child);
    EXPECT_EQ(1, parent->get_child_count());

    parent->remove_view(child);
    EXPECT_EQ(0, parent->get_child_count());
    EXPECT_EQ(nullptr, child->get_parent());
}

TEST_F(ViewGroupTest, RemoveAt) {
    auto child1 = std::make_shared<View>();
    auto child2 = std::make_shared<View>();
    parent->add_view(child1);
    parent->add_view(child2);

    parent->remove_view_at(0);
    EXPECT_EQ(1, parent->get_child_count());
    EXPECT_EQ(child2, parent->get_child_at(0));
    EXPECT_EQ(nullptr, child1->get_parent());
}

TEST_F(ViewGroupTest, ClearViews) {
    parent->add_view(std::make_shared<View>());
    parent->add_view(std::make_shared<View>());
    EXPECT_EQ(2, parent->get_child_count());

    parent->remove_all_views();
    EXPECT_EQ(0, parent->get_child_count());
}

TEST_F(ViewGroupTest, HierarchicalLayout) {
    auto child = std::make_shared<View>();
    parent->add_view(child);

    // Parent layout should trigger child layout in a real ViewGroup.
    // Our base ViewGroup currently has a simple on_layout implementation.
    parent->layout(0, 0, 100, 100);
    EXPECT_EQ(0, parent->get_left());
    EXPECT_EQ(100, parent->get_width());

    // In our simplified implementation, we verify that layout calls work.
    child->layout(10, 10, 90, 90);
    EXPECT_EQ(10, child->get_left());
    EXPECT_EQ(80, child->get_width());
}

