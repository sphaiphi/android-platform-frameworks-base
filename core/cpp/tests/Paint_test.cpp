#include <gtest/gtest.h>
#include <android/graphics/Paint.h>

using namespace android::graphics;

TEST(PaintTest, DefaultValues) {
    Paint paint;
    EXPECT_EQ(Paint::Style::FILL, paint.get_style());
    EXPECT_EQ(0xFF000000, paint.get_color());
    EXPECT_EQ(255, paint.get_alpha());
    EXPECT_EQ(0.0f, paint.get_stroke_width());
    EXPECT_EQ(Paint::StrokeCap::BUTT, paint.get_stroke_cap());
    EXPECT_EQ(Paint::StrokeJoin::MITER, paint.get_stroke_join());
    EXPECT_EQ(4.0f, paint.get_stroke_miter());
    EXPECT_EQ(0.0f, paint.get_text_size());
    EXPECT_EQ(Paint::TextAlign::LEFT, paint.get_text_align());
    EXPECT_FALSE(paint.is_anti_alias());
    EXPECT_FALSE(paint.is_dither());
    EXPECT_FALSE(paint.is_filter_bitmap());
}

TEST(PaintTest, Style) {
    Paint paint;
    paint.set_style(Paint::Style::STROKE);
    EXPECT_EQ(Paint::Style::STROKE, paint.get_style());
    paint.set_style(Paint::Style::FILL_AND_STROKE);
    EXPECT_EQ(Paint::Style::FILL_AND_STROKE, paint.get_style());
    paint.set_style(Paint::Style::FILL);
    EXPECT_EQ(Paint::Style::FILL, paint.get_style());
}

TEST(PaintTest, Color) {
    Paint paint;
    paint.set_color(Color::RED);
    EXPECT_EQ(Color::RED, paint.get_color());
    paint.set_color(Color::BLUE);
    EXPECT_EQ(Color::BLUE, paint.get_color());
}

TEST(PaintTest, Alpha) {
    Paint paint;
    paint.set_alpha(128);
    EXPECT_EQ(128, paint.get_alpha());
    paint.set_alpha(0);
    EXPECT_EQ(0, paint.get_alpha());
    paint.set_alpha(255);
    EXPECT_EQ(255, paint.get_alpha());
}

TEST(PaintTest, StrokeWidth) {
    Paint paint;
    paint.set_stroke_width(2.0f);
    EXPECT_FLOAT_EQ(2.0f, paint.get_stroke_width());
    paint.set_stroke_width(10.5f);
    EXPECT_FLOAT_EQ(10.5f, paint.get_stroke_width());
}

TEST(PaintTest, StrokeCap) {
    Paint paint;
    paint.set_stroke_cap(Paint::StrokeCap::ROUND);
    EXPECT_EQ(Paint::StrokeCap::ROUND, paint.get_stroke_cap());
    paint.set_stroke_cap(Paint::StrokeCap::SQUARE);
    EXPECT_EQ(Paint::StrokeCap::SQUARE, paint.get_stroke_cap());
}

TEST(PaintTest, StrokeJoin) {
    Paint paint;
    paint.set_stroke_join(Paint::StrokeJoin::ROUND);
    EXPECT_EQ(Paint::StrokeJoin::ROUND, paint.get_stroke_join());
    paint.set_stroke_join(Paint::StrokeJoin::BEVEL);
    EXPECT_EQ(Paint::StrokeJoin::BEVEL, paint.get_stroke_join());
}

TEST(PaintTest, StrokeMiter) {
    Paint paint;
    paint.set_stroke_miter(2.0f);
    EXPECT_FLOAT_EQ(2.0f, paint.get_stroke_miter());
}

TEST(PaintTest, TextSize) {
    Paint paint;
    paint.set_text_size(16.0f);
    EXPECT_FLOAT_EQ(16.0f, paint.get_text_size());
}

TEST(PaintTest, TextAlign) {
    Paint paint;
    paint.set_text_align(Paint::TextAlign::CENTER);
    EXPECT_EQ(Paint::TextAlign::CENTER, paint.get_text_align());
    paint.set_text_align(Paint::TextAlign::RIGHT);
    EXPECT_EQ(Paint::TextAlign::RIGHT, paint.get_text_align());
}

TEST(PaintTest, AntiAlias) {
    Paint paint;
    paint.set_anti_alias(true);
    EXPECT_TRUE(paint.is_anti_alias());
    paint.set_anti_alias(false);
    EXPECT_FALSE(paint.is_anti_alias());
}

TEST(PaintTest, Dither) {
    Paint paint;
    paint.set_dither(true);
    EXPECT_TRUE(paint.is_dither());
}

TEST(PaintTest, FilterBitmap) {
    Paint paint;
    paint.set_filter_bitmap(true);
    EXPECT_TRUE(paint.is_filter_bitmap());
}

TEST(PaintTest, MeasureText) {
    Paint paint;
    paint.set_text_size(16.0f);
    auto width = paint.measureText("Hello");
    EXPECT_GT(width, 0.0f);
    EXPECT_EQ(0.0f, paint.measureText(""));
}

TEST(PaintTest, CopyConstructor) {
    Paint original;
    original.set_color(Color::GREEN);
    original.set_style(Paint::Style::STROKE);
    original.set_anti_alias(true);

    Paint copy(original);
    EXPECT_EQ(Color::GREEN, copy.get_color());
    EXPECT_EQ(Paint::Style::STROKE, copy.get_style());
    EXPECT_TRUE(copy.is_anti_alias());
}

TEST(PaintTest, AssignmentOperator) {
    Paint original;
    original.set_color(Color::CYAN);
    original.set_text_size(24.0f);

    Paint assigned;
    assigned = original;
    EXPECT_EQ(Color::CYAN, assigned.get_color());
    EXPECT_FLOAT_EQ(24.0f, assigned.get_text_size());
}
