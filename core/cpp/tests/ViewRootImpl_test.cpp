#include <gtest/gtest.h>
#include <android/view/ViewRootImpl.h>
#include <android/view/View.h>
#include <memory>
#include <vector>
#include <string>

namespace android::view {

class ViewRootImplMockView : public View {
public:
    std::vector<std::string> calls;

    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override {
        calls.push_back("on_measure");
        set_measured_dimension(View::MeasureSpec::get_size(width_measure_spec),
                               View::MeasureSpec::get_size(height_measure_spec));
    }

    void on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) override {
        calls.push_back("on_layout");
    }

    void on_draw(android::graphics::Canvas& canvas) override {
        calls.push_back("on_draw");
    }
};

} // namespace android::view

using namespace android::view;

class ViewRootImplTest : public ::testing::Test {
protected:
    std::shared_ptr<ViewRootImpl> view_root;
    std::shared_ptr<ViewRootImplMockView> mock_view;

    void SetUp() override {
        view_root = std::make_shared<ViewRootImpl>();
        mock_view = std::make_shared<ViewRootImplMockView>();
        view_root->set_view(mock_view);
    }
};

TEST_F(ViewRootImplTest, PerformTraversalsTriggered) {
    view_root->perform_traversals();
    
    ASSERT_EQ(mock_view->calls.size(), 3);
    EXPECT_EQ(mock_view->calls[0], "on_measure");
    EXPECT_EQ(mock_view->calls[1], "on_layout");
    EXPECT_EQ(mock_view->calls[2], "on_draw");
}
