#include <gtest/gtest.h>
#include <android/view/IWindowSession.h>
#include <android/view/IWindow.h>
#include <android/view/WindowSession.h>
#include <android/view/ViewRootImpl.h>
#include <android/graphics/Rect.h>
#include <memory>
#include <vector>

namespace android::view {

class MockIWindow : public IWindow {
public:
    std::vector<std::string> calls_received;
    android::graphics::Rect last_frames;
    int32_t last_x{0}, last_y{0};
    bool last_visible{false};

    void on_resized(const android::graphics::Rect& frames, bool /*report_draw*/) override {
        calls_received.push_back("resized");
        last_frames = frames;
    }

    void on_moved(int32_t new_x, int32_t new_y) override {
        calls_received.push_back("moved");
        last_x = new_x;
        last_y = new_y;
    }

    void on_dispatch_app_visibility(bool visible) override {
        calls_received.push_back("dispatchAppVisibility");
        last_visible = visible;
    }
};

TEST(IWindowSessionTest, WindowSessionCanBeCreated) {
    auto session = std::make_shared<WindowSession>();
    EXPECT_NE(nullptr, session);
}

TEST(IWindowSessionTest, WindowSessionIsCastableToIWindowSession) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindowSession> iface = session;
    EXPECT_NE(nullptr, iface);
}

TEST(IWindowSessionTest, AddToDisplayReturnsZero) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindow> window = std::make_shared<MockIWindow>();

    std::shared_ptr<InputChannel> out_input_channel;
    std::shared_ptr<InsetsState> out_insets_state;
    std::shared_ptr<InsetsSourceControlArray> out_active_controls;
    android::graphics::Rect out_attached_frame;
    std::vector<float> out_size_compat_scale;

    int result = session->add_to_display(
        window, nullptr, 0, 0, 0,
        out_input_channel, out_insets_state, out_active_controls,
        out_attached_frame, out_size_compat_scale);

    EXPECT_EQ(0, result);
    // Stub returns empty insets state
    EXPECT_TRUE(out_insets_state != nullptr);
    EXPECT_TRUE(out_insets_state->sources.empty());
}

TEST(IWindowSessionTest, RelayoutReturnsResult) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindow> window = std::make_shared<MockIWindow>();

    std::shared_ptr<WindowRelayoutResult> out_result;
    int result = session->relayout(
        window, nullptr, 1080, 1920, 0, 0, 1, 0, out_result);

    EXPECT_EQ(0, result);
    EXPECT_TRUE(out_result != nullptr);
}

TEST(IWindowSessionTest, FinishDrawingIsNoOp) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindow> window = std::make_shared<MockIWindow>();
    // Should not crash
    session->finish_drawing(window, nullptr, 1);
}

TEST(IWindowSessionTest, RemoveIsNoOp) {
    auto session = std::make_shared<WindowSession>();
    // Should not crash
    session->remove(nullptr);
}

TEST(IWindowSessionTest, CancelDrawReturnsFalse) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindow> window = std::make_shared<MockIWindow>();
    EXPECT_FALSE(session->cancel_draw(window));
}

TEST(IWindowSessionTest, OutOfMemoryReturnsFalse) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindow> window = std::make_shared<MockIWindow>();
    EXPECT_FALSE(session->out_of_memory(window));
}

TEST(MockIWindowTest, OnResizedRecordsCall) {
    MockIWindow window;
    android::graphics::Rect frames{0, 0, 100, 200};
    window.on_resized(frames, true);
    ASSERT_EQ(1u, window.calls_received.size());
    EXPECT_EQ("resized", window.calls_received[0]);
}

TEST(MockIWindowTest, OnMovedRecordsCall) {
    MockIWindow window;
    window.on_moved(10, 20);
    ASSERT_EQ(1u, window.calls_received.size());
    EXPECT_EQ("moved", window.calls_received[0]);
}

} // namespace android::view
