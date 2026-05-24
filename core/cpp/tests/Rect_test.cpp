#include <gtest/gtest.h>
#include <android/graphics/Rect.h>

using namespace android::graphics;

TEST(RectTest, DefaultConstructor) {
    Rect r;
    EXPECT_EQ(0, r.left);
    EXPECT_EQ(0, r.top);
    EXPECT_EQ(0, r.right);
    EXPECT_EQ(0, r.bottom);
}

TEST(RectTest, ParameterConstructor) {
    Rect r(1, 2, 3, 4);
    EXPECT_EQ(1, r.left);
    EXPECT_EQ(2, r.top);
    EXPECT_EQ(3, r.right);
    EXPECT_EQ(4, r.bottom);
}

TEST(RectTest, WidthAndHeight) {
    Rect r(10, 10, 20, 25);
    EXPECT_EQ(10, r.width());
    EXPECT_EQ(15, r.height());
}

TEST(RectTest, Set) {
    Rect r;
    r.set(5, 6, 7, 8);
    EXPECT_EQ(5, r.left);
    EXPECT_EQ(6, r.top);
    EXPECT_EQ(7, r.right);
    EXPECT_EQ(8, r.bottom);
}

TEST(RectTest, IsEmpty) {
    EXPECT_TRUE(Rect(10, 10, 10, 10).isEmpty());
    EXPECT_TRUE(Rect(10, 10, 5, 5).isEmpty());
    EXPECT_FALSE(Rect(10, 10, 20, 20).isEmpty());
}

TEST(RectTest, Contains) {
    Rect r(10, 10, 20, 20);
    EXPECT_TRUE(r.contains(15, 15));
    EXPECT_TRUE(r.contains(10, 10));
    EXPECT_FALSE(r.contains(20, 20));
    EXPECT_FALSE(r.contains(5, 5));
}

TEST(RectTest, Offset) {
    Rect r(10, 10, 20, 20);
    r.offset(5, -2);
    EXPECT_EQ(15, r.left);
    EXPECT_EQ(8, r.top);
    EXPECT_EQ(25, r.right);
    EXPECT_EQ(18, r.bottom);
}

TEST(RectTest, Inset) {
    Rect r(10, 10, 20, 20);
    r.inset(2, 3);
    EXPECT_EQ(12, r.left);
    EXPECT_EQ(13, r.top);
    EXPECT_EQ(18, r.right);
    EXPECT_EQ(17, r.bottom);
}

TEST(RectTest, Intersect) {
    Rect r1(0, 0, 10, 10);
    EXPECT_TRUE(r1.intersect(5, 5, 15, 15));
    EXPECT_EQ(5, r1.left);
    EXPECT_EQ(5, r1.top);
    EXPECT_EQ(10, r1.right);
    EXPECT_EQ(10, r1.bottom);
}

TEST(RectTest, Union) {
    Rect r(0, 0, 10, 10);
    r.union_with(15, 15, 20, 20);
    EXPECT_EQ(0, r.left);
    EXPECT_EQ(0, r.top);
    EXPECT_EQ(20, r.right);
    EXPECT_EQ(20, r.bottom);
}

TEST(RectTest, FlattenUnflatten) {
    Rect r(1, 2, 3, 4);
    std::string s = r.flattenToString();
    auto res = Rect::unflattenFromString(s);
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(r, res.value());
}
