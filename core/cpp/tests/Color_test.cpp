#include <gtest/gtest.h>
#include <android/graphics/Color.h>

using namespace android::graphics;

// --- Factory Methods ---

TEST(ColorTest, ArgbCreatesCorrectPackedValue) {
    EXPECT_EQ(0xFF000000, Color::argb(255, 0, 0, 0));
    EXPECT_EQ(0xFF0000FF, Color::argb(255, 0, 0, 255));
    EXPECT_EQ(0xFFFFFFFF, Color::argb(255, 255, 255, 255));
    EXPECT_EQ(0x00FF0000, Color::argb(0, 255, 0, 0));
    EXPECT_EQ(0x80008000, Color::argb(128, 0, 128, 0));
}

TEST(ColorTest, RgbCreatesWithFullAlpha) {
    EXPECT_EQ(0xFFFF0000, Color::rgb(255, 0, 0));
    EXPECT_EQ(0xFF00FF00, Color::rgb(0, 255, 0));
    EXPECT_EQ(0xFF0000FF, Color::rgb(0, 0, 255));
    EXPECT_EQ(0xFFFFFFFF, Color::rgb(255, 255, 255));
    EXPECT_EQ(0xFF000000, Color::rgb(0, 0, 0));
}

// --- Component Accessors ---

TEST(ColorTest, GetRed) {
    EXPECT_EQ(255, Color::getRed(0xFFFF0000));
    EXPECT_EQ(0, Color::getRed(0xFF00FF00));
    EXPECT_EQ(128, Color::getRed(0xFF808000));
}

TEST(ColorTest, GetGreen) {
    EXPECT_EQ(0, Color::getGreen(0xFFFF0000));
    EXPECT_EQ(255, Color::getGreen(0xFF00FF00));
    EXPECT_EQ(64, Color::getGreen(0xFF004000));
}

TEST(ColorTest, GetBlue) {
    EXPECT_EQ(0, Color::getBlue(0xFFFF0000));
    EXPECT_EQ(255, Color::getBlue(0xFF0000FF));
    EXPECT_EQ(192, Color::getBlue(0xFF0000C0));
}

TEST(ColorTest, GetAlpha) {
    EXPECT_EQ(255, Color::getAlpha(0xFF000000));
    EXPECT_EQ(0, Color::getAlpha(0x00FF0000));
    EXPECT_EQ(128, Color::getAlpha(0x80000000));
}

// --- Color Manipulation ---

TEST(ColorTest, SetColorAlpha) {
    EXPECT_EQ(0x8000FF00, Color::setColorAlpha(0xFF00FF00, 128));
    EXPECT_EQ(0xFF00FF00, Color::setColorAlpha(0x8000FF00, 255));
}

TEST(ColorTest, SetAlphaColor) {
    // setAlphaColor(alpha, color) sets the alpha component of color to alpha
    EXPECT_EQ(0x80FF0000, Color::setAlphaColor(128, 0xFFFF0000));
    EXPECT_EQ(0xFF000000, Color::setAlphaColor(255, 0x00000000));
    EXPECT_EQ(0x4000FF00, Color::setAlphaColor(64, 0xFF00FF00));
}

// --- parseColor ---

TEST(ColorTest, ParseColorHexRrggbb) {
    auto result = Color::parseColor("#FF0000");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(0xFFFF0000, result.value());
}

TEST(ColorTest, ParseColorHexAarrggbb) {
    auto result = Color::parseColor("#80FF0000");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(0x80FF0000, result.value());
}

TEST(ColorTest, ParseColorHexLowercase) {
    auto result = Color::parseColor("#aabbcc");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(0xFFAABBCC, result.value());
}

TEST(ColorTest, ParseColorWith0xPrefix) {
    auto result = Color::parseColor("0xFF00FF00");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(0xFF00FF00, result.value());
}

TEST(ColorTest, ParseColorAndroidRed) {
    auto result = Color::parseColor("#android:red");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(0xFFFF0000, result.value());
}

TEST(ColorTest, ParseColorTransparent) {
    auto result = Color::parseColor("transparent");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(0x00000000, result.value());
}

TEST(ColorTest, ParseColorInvalid) {
    auto result = Color::parseColor("not-a-color");
    EXPECT_FALSE(result.has_value());
}

TEST(ColorTest, ParseColorEmpty) {
    auto result = Color::parseColor("");
    EXPECT_FALSE(result.has_value());
}

// --- Constants ---

TEST(ColorTest, Black) {
    EXPECT_EQ(0xFF000000, Color::BLACK);
}

TEST(ColorTest, White) {
    EXPECT_EQ(0xFFFFFFFF, Color::WHITE);
}

TEST(ColorTest, Red) {
    EXPECT_EQ(0xFFFF0000, Color::RED);
}

TEST(ColorTest, Green) {
    EXPECT_EQ(0xFF00FF00, Color::GREEN);
}

TEST(ColorTest, Blue) {
    EXPECT_EQ(0xFF0000FF, Color::BLUE);
}

TEST(ColorTest, Cyan) {
    EXPECT_EQ(0xFF00FFFF, Color::CYAN);
}

TEST(ColorTest, Magenta) {
    EXPECT_EQ(0xFFFF00FF, Color::MAGENTA);
}

TEST(ColorTest, Yellow) {
    EXPECT_EQ(0xFFFFFF00, Color::YELLOW);
}

TEST(ColorTest, Transparent) {
    EXPECT_EQ(0x00000000, Color::TRANSPARENT);
}

// --- Formatting ---

TEST(ColorTest, ToArgbString) {
    EXPECT_EQ("#FF000000", Color::toArgbString(0xFF000000));
    EXPECT_EQ("#FF00FF00", Color::toArgbString(0xFF00FF00));
    EXPECT_EQ("#80AABBCC", Color::toArgbString(0x80AABBCC));
}
