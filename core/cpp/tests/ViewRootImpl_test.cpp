#include <gtest/gtest.h>
#include <android/view/ViewRootImpl.h>
#include <android/view/View.h>
#include <android/view/WindowSession.h>
#include <android/view/IWindow.h>
#include <memory>
#include <vector>
#include <string>

namespace android::view {

class MockIWindow : public IWindow {
public:
    std::vector<std::string> calls_received;

    void on_resized(const android::graphics::Rect& /*frames*/, bool /*report_draw*/) override {
        calls_received.push_back("resized");
    }

    void on_moved(int32_t /*new_x*/, int32_t /*new_y*/) override {
        calls_received.push_back("moved");
    }

    void on_dispatch_app_visibility(bool /*visible*/) override {
        calls_received.push_back("dispatchAppVisibility");
    }
};

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

TEST_F(ViewRootImplTest, PerformTraversalsWithSessionCallsRelayout) {
    auto session = std::make_shared<WindowSession>();
    auto mock_window = std::make_shared<MockIWindow>();
    view_root->set_window_session(session);
    view_root->set_window(mock_window);

    view_root->perform_traversals();

    // With a session set, relayout should be called during traversals
    // The session should have registered the window
    EXPECT_EQ(1u, session->registered_window_count());
    EXPECT_TRUE(session->is_window_registered(mock_window));
}

TEST_F(ViewRootImplTest, PerformTraversalsWithoutSessionDoesNotCrash) {
    // No session set — should still perform measure/layout/draw
    view_root->perform_traversals();

    ASSERT_EQ(mock_view->calls.size(), 3);
    EXPECT_EQ(mock_view->calls[0], "on_measure");
    EXPECT_EQ(mock_view->calls[1], "on_layout");
    EXPECT_EQ(mock_view->calls[2], "on_draw");
}
