#include <gtest/gtest.h>
#include <android/view/InsetsSource.h>
#include <android/graphics/Rect.h>
#include <optional>
#include <vector>

namespace android::view {

TEST(InsetsSourceTest, DefaultConstructor) {
    InsetsSource s;
    EXPECT_EQ(0, s.id);
    EXPECT_EQ(0, s.type);
    EXPECT_TRUE(s.visible_frame.value_or(android::graphics::Rect{}).isEmpty());
    EXPECT_FALSE(s.visible);
    EXPECT_EQ(0, s.flags);
    EXPECT_EQ(0, s.side_hint);
    EXPECT_TRUE(s.bounding_rects.empty());
}

TEST(InsetsSourceTest, ConstructorWithValues) {
    android::graphics::Rect frame{0, 0, 1080, 1920};
    android::graphics::Rect visible_frame{8, 24, 1072, 1888};
    std::vector<android::graphics::Rect> bounding_rects;

    InsetsSource s{1, 0x01, frame, visible_frame, true, 0, android::view::InsetsSource::SIDE_TOP, bounding_rects};
    EXPECT_EQ(1, s.id);
    EXPECT_EQ(0x01, s.type);
    EXPECT_EQ(1080, s.frame.right);
    EXPECT_TRUE(s.visible_frame.has_value());
    EXPECT_EQ(24, s.visible_frame->top);
    EXPECT_TRUE(s.visible);
    EXPECT_EQ(android::view::InsetsSource::SIDE_TOP, s.side_hint);
}

TEST(InsetsSourceTest, NullVisibleFrame) {
    android::graphics::Rect frame{0, 0, 100, 200};
    std::vector<android::graphics::Rect> bounding_rects;
    InsetsSource s{2, 0x04, frame, std::nullopt, false, 0, 0, bounding_rects};
    EXPECT_FALSE(s.visible_frame.has_value());
}

TEST(InsetsSourceTest, BoundingRects) {
    android::graphics::Rect frame{0, 0, 100, 200};
    std::vector<android::graphics::Rect> rects{{10, 10, 20, 20}, {30, 30, 40, 40}};
    InsetsSource s{1, 0x01, frame, std::nullopt, true, 0, 0, rects};
    ASSERT_EQ(2u, s.bounding_rects.size());
    EXPECT_EQ(10, s.bounding_rects[0].left);
    EXPECT_EQ(30, s.bounding_rects[1].left);
}

} // namespace android::view
