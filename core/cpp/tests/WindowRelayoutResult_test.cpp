#include <gtest/gtest.h>
#include <android/view/WindowRelayoutResult.h>
#include <android/graphics/Rect.h>
#include <android/view/InsetsState.h>
#include <android/view/Surface.h>
#include <memory>

namespace android::view {

TEST(WindowRelayoutResultTest, DefaultConstructor) {
    WindowRelayoutResult result;
    EXPECT_TRUE(result.frames.isEmpty());
    EXPECT_FALSE(result.surface != nullptr);
    EXPECT_EQ(0, result.seq);
    EXPECT_FALSE(result.insets_state.has_value());
}

TEST(WindowRelayoutResultTest, WithFrames) {
    WindowRelayoutResult result;
    result.frames = android::graphics::Rect{0, 0, 1080, 1920};
    EXPECT_EQ(1080, result.frames.right);
}

TEST(WindowRelayoutResultTest, WithSurface) {
    WindowRelayoutResult result;
    void* fake_handle = reinterpret_cast<void*>(0xDEAD);
    result.surface = std::make_shared<Surface>(fake_handle);
    EXPECT_TRUE(result.surface != nullptr);
    EXPECT_TRUE(result.surface->is_valid());
}

TEST(WindowRelayoutResultTest, WithInsetsState) {
    WindowRelayoutResult result;
    InsetsState state;
    state.display_frame = android::graphics::Rect{0, 0, 1080, 1920};
    result.insets_state = state;
    result.seq = 3;
    EXPECT_TRUE(result.insets_state.has_value());
    EXPECT_EQ(1080, result.insets_state->display_frame.right);
    EXPECT_EQ(3, result.seq);
}

TEST(WindowRelayoutResultTest, FullRelayoutResult) {
    WindowRelayoutResult result;
    result.frames = android::graphics::Rect{0, 0, 1080, 1920};
    void* fake_handle = reinterpret_cast<void*>(0xBEEF);
    result.surface = std::make_shared<Surface>(fake_handle);
    result.seq = 7;

    InsetsState state;
    state.display_frame = android::graphics::Rect{0, 0, 1080, 1920};
    state.seq = 7;
    result.insets_state = state;

    EXPECT_EQ(1080, result.frames.right);
    EXPECT_TRUE(result.surface->is_valid());
    EXPECT_EQ(7, result.seq);
    EXPECT_TRUE(result.insets_state.has_value());
}

} // namespace android::view
