#include <gtest/gtest.h>
#include <android/graphics/Drawable.h>
#include <android/graphics/Canvas.h>
#include <android/graphics/ColorDrawable.h>
#include <android/graphics/Color.h>

using namespace android::graphics;

// Concrete Drawable subclass for testing base class
class TestDrawable : public Drawable {
public:
    bool draw_called = false;
    void draw(Canvas*) override { draw_called = true; }
};

TEST(DrawableTest, DefaultBounds) {
    TestDrawable d;
    auto bounds = d.getBounds();
    EXPECT_EQ(0, bounds.left);
    EXPECT_EQ(0, bounds.top);
    EXPECT_EQ(0, bounds.right);
    EXPECT_EQ(0, bounds.bottom);
}

TEST(DrawableTest, SetBounds) {
    TestDrawable d;
    d.setBounds(10, 20, 110, 120);
    auto bounds = d.getBounds();
    EXPECT_EQ(10, bounds.left);
    EXPECT_EQ(20, bounds.top);
    EXPECT_EQ(110, bounds.right);
    EXPECT_EQ(120, bounds.bottom);
}

TEST(DrawableTest, SetBoundsInPlace) {
    TestDrawable d;
    Rect r{5, 10, 55, 60};
    d.setBoundsInPlace(r);
    auto bounds = d.getBounds();
    EXPECT_EQ(5, bounds.left);
    EXPECT_EQ(10, bounds.top);
    EXPECT_EQ(55, bounds.right);
    EXPECT_EQ(60, bounds.bottom);
}

TEST(DrawableTest, DefaultIntrinsicSize) {
    TestDrawable d;
    EXPECT_EQ(-1, d.getIntrinsicWidth());
    EXPECT_EQ(-1, d.getIntrinsicHeight());
}

TEST(DrawableTest, DefaultAlpha) {
    TestDrawable d;
    EXPECT_EQ(255, d.getAlpha());
}

TEST(DrawableTest, SetAlpha) {
    TestDrawable d;
    d.setAlpha(128);
    EXPECT_EQ(128, d.getAlpha());
    d.setAlpha(0);
    EXPECT_EQ(0, d.getAlpha());
}

TEST(DrawableTest, DrawCalled) {
    TestDrawable d;
    Canvas canvas(100, 100);
    EXPECT_FALSE(d.draw_called);
    d.draw(&canvas);
    EXPECT_TRUE(d.draw_called);
}

TEST(DrawableTest, DefaultLevel) {
    TestDrawable d;
    EXPECT_EQ(0, d.getLevel());
}

TEST(DrawableTest, SetLevel) {
    TestDrawable d;
    d.setLevel(100);
    EXPECT_EQ(100, d.getLevel());
}

TEST(DrawableTest, DefaultState) {
    TestDrawable d;
    auto state = d.getState();
    EXPECT_TRUE(state->empty());
}

TEST(DrawableTest, GetMinimumHeight) {
    TestDrawable d;
    EXPECT_EQ(0, d.getMinimumHeight());
    EXPECT_EQ(0, d.getMinimumWidth());
}

// --- ColorDrawable Tests ---

TEST(ColorDrawableTest, ConstructorSetsColor) {
    ColorDrawable d(Color::RED);
    EXPECT_EQ(Color::RED, d.getColor());
}

TEST(ColorDrawableTest, DrawRecordsRectCommand) {
    ColorDrawable d(Color::BLUE);
    d.setBounds(0, 0, 100, 50);
    Canvas canvas(200, 200);
    d.draw(&canvas);
    EXPECT_EQ(1u, canvas.get_commands().size());
}

TEST(ColorDrawableTest, IntrinsicSize) {
    ColorDrawable d(Color::GREEN);
    EXPECT_EQ(0, d.getIntrinsicWidth());
    EXPECT_EQ(0, d.getIntrinsicHeight());
}

TEST(ColorDrawableTest, AlphaAppliesToDraw) {
    ColorDrawable d(Color::WHITE);
    d.setAlpha(128);
    EXPECT_EQ(128, d.getAlpha());
}

TEST(ColorDrawableTest, DefaultColorIsBlack) {
    ColorDrawable d;
    EXPECT_EQ(Color::BLACK, d.getColor());
}
