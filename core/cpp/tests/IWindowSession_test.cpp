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

TEST(IWindowSessionTest, AddToDisplayPopulatesInsetsState) {
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
    EXPECT_TRUE(out_insets_state != nullptr);
    EXPECT_EQ(0, out_insets_state->seq);
    EXPECT_TRUE(out_insets_state->sources.empty());
    EXPECT_TRUE(out_insets_state->display_frame.isEmpty());
}

TEST(IWindowSessionTest, AddToDisplayPopulatesActiveControls) {
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
    EXPECT_TRUE(out_active_controls != nullptr);
    EXPECT_TRUE(out_active_controls->controls.empty());
    EXPECT_EQ(0, out_active_controls->seq);
}

TEST(IWindowSessionTest, AddToDisplayTracksRegistration) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindow> window = std::make_shared<MockIWindow>();

    std::shared_ptr<InputChannel> out_input_channel;
    std::shared_ptr<InsetsState> out_insets_state;
    std::shared_ptr<InsetsSourceControlArray> out_active_controls;
    android::graphics::Rect out_attached_frame;
    std::vector<float> out_size_compat_scale;

    EXPECT_EQ(0u, session->registered_window_count());

    session->add_to_display(
        window, nullptr, 0, 0, 0,
        out_input_channel, out_insets_state, out_active_controls,
        out_attached_frame, out_size_compat_scale);

    EXPECT_EQ(1u, session->registered_window_count());
    EXPECT_TRUE(session->is_window_registered(window));
}

TEST(IWindowSessionTest, AddToDisplayMultipleWindows) {
    auto session = std::make_shared<WindowSession>();

    std::shared_ptr<InputChannel> out_input_channel;
    std::shared_ptr<InsetsState> out_insets_state;
    std::shared_ptr<InsetsSourceControlArray> out_active_controls;
    android::graphics::Rect out_attached_frame;
    std::vector<float> out_size_compat_scale;

    auto w1 = std::make_shared<MockIWindow>();
    auto w2 = std::make_shared<MockIWindow>();

    session->add_to_display(w1, nullptr, 0, 0, 0,
        out_input_channel, out_insets_state, out_active_controls,
        out_attached_frame, out_size_compat_scale);
    session->add_to_display(w2, nullptr, 0, 0, 0,
        out_input_channel, out_insets_state, out_active_controls,
        out_attached_frame, out_size_compat_scale);

    EXPECT_EQ(2u, session->registered_window_count());
    EXPECT_TRUE(session->is_window_registered(w1));
    EXPECT_TRUE(session->is_window_registered(w2));
}

TEST(IWindowSessionTest, RemoveUnregistersWindow) {
    auto session = std::make_shared<WindowSession>();
    auto window = std::make_shared<MockIWindow>();

    std::shared_ptr<InputChannel> out_input_channel;
    std::shared_ptr<InsetsState> out_insets_state;
    std::shared_ptr<InsetsSourceControlArray> out_active_controls;
    android::graphics::Rect out_attached_frame;
    std::vector<float> out_size_compat_scale;

    session->add_to_display(window, nullptr, 0, 0, 0,
        out_input_channel, out_insets_state, out_active_controls,
        out_attached_frame, out_size_compat_scale);
    EXPECT_EQ(1u, session->registered_window_count());

    session->remove(window);
    EXPECT_EQ(0u, session->registered_window_count());
    EXPECT_FALSE(session->is_window_registered(window));
}

TEST(IWindowSessionTest, RelayoutUpdatesFrames) {
    auto session = std::make_shared<WindowSession>();
    auto window = std::make_shared<MockIWindow>();

    std::shared_ptr<WindowRelayoutResult> out_result;
    session->relayout(window, nullptr, 1080, 1920, 0, 0, 1, 0, out_result);

    EXPECT_EQ(1080, out_result->frames.right);
    EXPECT_EQ(1920, out_result->frames.bottom);
    EXPECT_EQ(1, out_result->seq);
}

TEST(IWindowSessionTest, RelayoutWithLayoutParams) {
    auto session = std::make_shared<WindowSession>();
    auto window = std::make_shared<MockIWindow>();
    auto attrs = std::make_shared<LayoutParams>(720, 1280);

    std::shared_ptr<WindowRelayoutResult> out_result;
    session->relayout(window, attrs, 1080, 1920, 0, 0, 1, 0, out_result);

    EXPECT_EQ(720, out_result->frames.right);
    EXPECT_EQ(1280, out_result->frames.bottom);
}

TEST(IWindowSessionTest, RelayoutWithInsetsState) {
    auto session = std::make_shared<WindowSession>();
    auto window = std::make_shared<MockIWindow>();

    std::shared_ptr<WindowRelayoutResult> out_result;
    session->relayout(window, nullptr, 1080, 1920, 0, 0, 3, 0, out_result);

    EXPECT_TRUE(out_result->insets_state.has_value());
    EXPECT_EQ(3, out_result->insets_state->seq);
    EXPECT_EQ(1080, out_result->insets_state->display_frame.right);
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

TEST(IWindowSessionTest, RelayoutCreatesSurface) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindow> window = std::make_shared<MockIWindow>();

    std::shared_ptr<WindowRelayoutResult> out_result;
    session->relayout(window, nullptr, 1080, 1920, 0, 0, 1, 0, out_result);

    EXPECT_TRUE(out_result->surface != nullptr);
    EXPECT_TRUE(out_result->surface->is_valid());
}

TEST(IWindowSessionTest, RelayoutSurfaceHasNativeHandle) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindow> window = std::make_shared<MockIWindow>();

    std::shared_ptr<WindowRelayoutResult> out_result;
    session->relayout(window, nullptr, 1080, 1920, 0, 0, 1, 0, out_result);

    EXPECT_NE(nullptr, out_result->surface->get_native_handle());
}

TEST(IWindowSessionTest, RelayoutSurfacePerWindow) {
    auto session = std::make_shared<WindowSession>();
    auto w1 = std::make_shared<MockIWindow>();
    auto w2 = std::make_shared<MockIWindow>();

    std::shared_ptr<WindowRelayoutResult> result1;
    std::shared_ptr<WindowRelayoutResult> result2;
    session->relayout(w1, nullptr, 1080, 1920, 0, 0, 1, 0, result1);
    session->relayout(w2, nullptr, 720, 1280, 0, 0, 2, 0, result2);

    EXPECT_TRUE(result1->surface->is_valid());
    EXPECT_TRUE(result2->surface->is_valid());
    // Each window gets its own surface (different native handles)
    EXPECT_NE(result1->surface->get_native_handle(),
              result2->surface->get_native_handle());
}

TEST(IWindowSessionTest, RelayoutSurfaceFrameConsistent) {
    auto session = std::make_shared<WindowSession>();
    std::shared_ptr<IWindow> window = std::make_shared<MockIWindow>();

    std::shared_ptr<WindowRelayoutResult> out_result;
    session->relayout(window, nullptr, 800, 600, 0, 0, 5, 0, out_result);

    EXPECT_EQ(800, out_result->frames.right);
    EXPECT_EQ(600, out_result->frames.bottom);
    EXPECT_EQ(5, out_result->seq);
    EXPECT_TRUE(out_result->surface->is_valid());
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
