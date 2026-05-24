#include <gtest/gtest.h>
#include <android/graphics/Point.h>

namespace android::graphics {

TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_EQ(0, p.x);
    EXPECT_EQ(0, p.y);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(3, 7);
    EXPECT_EQ(3, p.x);
    EXPECT_EQ(7, p.y);
}

TEST(PointTest, CopyConstructor) {
    Point a(5, 10);
    Point b(a);
    EXPECT_EQ(5, b.x);
    EXPECT_EQ(10, b.y);
}

TEST(PointTest, Set) {
    Point p;
    p.set(42, 99);
    EXPECT_EQ(42, p.x);
    EXPECT_EQ(99, p.y);
}

TEST(PointTest, Equality) {
    EXPECT_TRUE(Point(1, 2) == Point(1, 2));
    EXPECT_FALSE(Point(1, 2) == Point(2, 1));
    EXPECT_FALSE(Point(1, 2) == Point(1, 3));
}

TEST(PointTest, Inequality) {
    EXPECT_FALSE(Point(1, 2) != Point(1, 2));
    EXPECT_TRUE(Point(1, 2) != Point(2, 1));
}

TEST(PointTest, WriteToParcel) {
    // Tested via integration with binder parcel mock
}

} // namespace android::graphics
