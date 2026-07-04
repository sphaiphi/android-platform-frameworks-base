#include <gtest/gtest.h>
#include <android/view/View.h>
#include <android/graphics/Canvas.h>
#include <android/graphics/ColorDrawable.h>
#include <android/graphics/Color.h>

using namespace android::view;
using namespace android::graphics;

TEST(ViewRenderingTest, DrawWithColorDrawableBackground) {
    View view;
    view.layout(0, 0, 100, 50);

    auto bg = std::make_shared<ColorDrawable>(Color::RED);
    bg->setBounds(0, 0, 100, 50);
    view.set_background(bg);

    Canvas canvas(200, 200);
    view.draw(canvas);

    auto cmds = canvas.get_commands();
    EXPECT_EQ(1u, cmds.size());
}

TEST(ViewRenderingTest, DrawWithNoBackgroundProducesNoCommands) {
    View view;
    view.layout(0, 0, 100, 50);

    Canvas canvas(200, 200);
    view.draw(canvas);

    EXPECT_TRUE(canvas.get_commands().empty());
}

TEST(ViewRenderingTest, DrawBackgroundRespectsViewBounds) {
    View view;
    view.layout(10, 20, 110, 70);

    auto bg = std::make_shared<ColorDrawable>(Color::BLUE);
    bg->setBounds(10, 20, 110, 70);
    view.set_background(bg);

    Canvas canvas(200, 200);
    view.draw(canvas);

    auto cmds = canvas.get_commands();
    EXPECT_EQ(1u, cmds.size());
}

TEST(ViewRenderingTest, DrawBackgroundRespectsVisibility) {
    View view;
    view.layout(0, 0, 100, 50);

    auto bg = std::make_shared<ColorDrawable>(Color::GREEN);
    bg->setBounds(0, 0, 100, 50);
    view.set_background(bg);

    view.set_visibility(Visibility::Invisible);
    Canvas canvas(200, 200);
    view.draw(canvas);

    // INVISIBLE view should still draw
    EXPECT_EQ(1u, canvas.get_commands().size());
}

TEST(ViewRenderingTest, DrawGoneViewProducesNoCommands) {
    View view;
    view.layout(0, 0, 100, 50);

    auto bg = std::make_shared<ColorDrawable>(Color::WHITE);
    bg->setBounds(0, 0, 100, 50);
    view.set_background(bg);

    view.set_visibility(Visibility::Gone);
    Canvas canvas(200, 200);
    view.draw(canvas);

    EXPECT_TRUE(canvas.get_commands().empty());
}
