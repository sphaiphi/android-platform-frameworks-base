#include <gtest/gtest.h>
#include <android/graphics/Insets.h>

namespace android::graphics {

TEST(InsetsTest, DefaultConstructor) {
    Insets i;
    EXPECT_EQ(0, i.left);
    EXPECT_EQ(0, i.top);
    EXPECT_EQ(0, i.right);
    EXPECT_EQ(0, i.bottom);
}

TEST(InsetsTest, ParameterizedConstructor) {
    Insets i(8, 16, 8, 32);
    EXPECT_EQ(8, i.left);
    EXPECT_EQ(16, i.top);
    EXPECT_EQ(8, i.right);
    EXPECT_EQ(32, i.bottom);
}

TEST(InsetsTest, CopyConstructor) {
    Insets a(1, 2, 3, 4);
    Insets b(a);
    EXPECT_EQ(1, b.left);
    EXPECT_EQ(2, b.top);
    EXPECT_EQ(3, b.right);
    EXPECT_EQ(4, b.bottom);
}

TEST(InsetsTest, OfStatic) {
    Insets i = Insets::of(10, 20, 30, 40);
    EXPECT_EQ(10, i.left);
    EXPECT_EQ(20, i.top);
    EXPECT_EQ(30, i.right);
    EXPECT_EQ(40, i.bottom);
}

TEST(InsetsTest, OfZeroStatic) {
    Insets i = Insets::ofZero();
    EXPECT_EQ(0, i.left);
    EXPECT_EQ(0, i.top);
    EXPECT_EQ(0, i.right);
    EXPECT_EQ(0, i.bottom);
}

TEST(InsetsTest, IsEmpty) {
    EXPECT_TRUE(Insets::ofZero().is_empty());
    EXPECT_FALSE(Insets::of(1, 0, 0, 0).is_empty());
    EXPECT_FALSE(Insets::of(0, 5, 0, 0).is_empty());
}

TEST(InsetsTest, Equality) {
    EXPECT_TRUE(Insets::of(1, 2, 3, 4) == Insets::of(1, 2, 3, 4));
    EXPECT_FALSE(Insets::of(1, 2, 3, 4) == Insets::of(4, 3, 2, 1));
}

TEST(InsetsTest, Inequality) {
    EXPECT_FALSE(Insets::of(1, 2, 3, 4) != Insets::of(1, 2, 3, 4));
    EXPECT_TRUE(Insets::of(1, 2, 3, 4) != Insets::of(0, 0, 0, 0));
}

TEST(InsetsTest, PlusInsets) {
    Insets a = Insets::of(1, 2, 3, 4);
    Insets b = Insets::of(5, 6, 7, 8);
    Insets c = a + b;
    EXPECT_EQ(6, c.left);
    EXPECT_EQ(8, c.top);
    EXPECT_EQ(10, c.right);
    EXPECT_EQ(12, c.bottom);
}

TEST(InsetsTest, MinusInsets) {
    Insets a = Insets::of(6, 8, 10, 12);
    Insets b = Insets::of(1, 2, 3, 4);
    Insets c = a - b;
    EXPECT_EQ(5, c.left);
    EXPECT_EQ(6, c.top);
    EXPECT_EQ(7, c.right);
    EXPECT_EQ(8, c.bottom);
}

TEST(InsetsTest, Intersect) {
    Insets a = Insets::of(10, 20, 10, 20);
    Insets b = Insets::of(5, 30, 5, 10);
    Insets c = Insets::intersect(a, b);
    EXPECT_EQ(10, c.left);   // max(10, 5) → 10? no, intersect takes max
    EXPECT_EQ(30, c.top);
    EXPECT_EQ(10, c.right);
    EXPECT_EQ(20, c.bottom);
}

TEST(InsetsTest, IntersectSelf) {
    Insets a = Insets::ofZero();
    Insets b = Insets::intersect(a, a);
    EXPECT_TRUE(b.is_empty());
}

} // namespace android::graphics
