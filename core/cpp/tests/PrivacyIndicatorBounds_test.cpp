#include <gtest/gtest.h>
#include <android/view/PrivacyIndicatorBounds.h>
#include <android/graphics/Rect.h>

namespace android::view {

TEST(PrivacyIndicatorBoundsTest, DefaultConstructor) {
    PrivacyIndicatorBounds bounds;
    EXPECT_TRUE(bounds.bounds.isEmpty());
    EXPECT_EQ(0, bounds.rotation);
    EXPECT_EQ(0, bounds.display_id);
}

TEST(PrivacyIndicatorBoundsTest, ConstructorWithValues) {
    android::graphics::Rect r{100, 200, 150, 250};
    PrivacyIndicatorBounds bounds{r, 90, 1};
    EXPECT_EQ(100, bounds.bounds.left);
    EXPECT_EQ(200, bounds.bounds.top);
    EXPECT_EQ(150, bounds.bounds.right);
    EXPECT_EQ(250, bounds.bounds.bottom);
    EXPECT_EQ(90, bounds.rotation);
    EXPECT_EQ(1, bounds.display_id);
}

TEST(PrivacyIndicatorBoundsTest, EmptyBounds) {
    android::graphics::Rect empty;
    PrivacyIndicatorBounds bounds{empty, 0, 0};
    EXPECT_TRUE(bounds.bounds.isEmpty());
}

} // namespace android::view
