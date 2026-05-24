#include <gtest/gtest.h>
#include <android/view/InsetsState.h>
#include <android/graphics/Rect.h>
#include <vector>

namespace android::view {

TEST(InsetsStateTest, DefaultConstructor) {
    InsetsState state;
    EXPECT_TRUE(state.display_frame.isEmpty());
    EXPECT_EQ(0, state.seq);
    EXPECT_TRUE(state.sources.empty());
}

TEST(InsetsStateTest, WithDisplayFrame) {
    InsetsState state;
    state.display_frame = android::graphics::Rect{0, 0, 1080, 1920};
    EXPECT_EQ(1080, state.display_frame.right);
    EXPECT_EQ(1920, state.display_frame.bottom);
}

TEST(InsetsStateTest, WithSources) {
    InsetsState state;
    state.seq = 5;
    android::graphics::Rect frame{0, 0, 100, 200};
    std::vector<android::graphics::Rect> rects;
    state.sources.push_back(android::view::InsetsSource{1, 0x01, frame, std::nullopt, true, 0, 0, rects});
    ASSERT_EQ(1u, state.sources.size());
    EXPECT_EQ(1, state.sources[0].id);
    EXPECT_EQ(5, state.seq);
}

TEST(InsetsStateTest, WithPrivacyIndicatorBounds) {
    InsetsState state;
    android::graphics::Rect r{10, 10, 20, 20};
    state.privacy_indicator_bounds = android::view::PrivacyIndicatorBounds{r, 0, 0};
    EXPECT_TRUE(state.privacy_indicator_bounds.has_value());
    EXPECT_EQ(10, state.privacy_indicator_bounds->bounds.left);
}

TEST(InsetsStateTest, NoPrivacyIndicatorBounds) {
    InsetsState state;
    EXPECT_FALSE(state.privacy_indicator_bounds.has_value());
}

} // namespace android::view
