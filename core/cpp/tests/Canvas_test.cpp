#include <gtest/gtest.h>
#include <android/graphics/Canvas.h>
#include <android/graphics/Paint.h>
#include <android/graphics/Path.h>
#include <android/graphics/Color.h>

using namespace android::graphics;

TEST(CanvasTest, ConstructorSetsSize) {
    Canvas canvas(100, 200);
    EXPECT_EQ(100, canvas.width());
    EXPECT_EQ(200, canvas.height());
}

TEST(CanvasTest, DrawRectRecordsCommand) {
    Canvas canvas(100, 100);
    Paint paint;
    paint.set_color(Color::RED);
    canvas.drawRect(10.0f, 20.0f, 50.0f, 60.0f, paint);

    auto cmds = canvas.get_commands();
    EXPECT_EQ(1u, cmds.size());
}

TEST(CanvasTest, DrawCircleRecordsCommand) {
    Canvas canvas(100, 100);
    Paint paint;
    canvas.drawCircle(50.0f, 50.0f, 30.0f, paint);
    EXPECT_EQ(1u, canvas.get_commands().size());
}

TEST(CanvasTest, DrawLineRecordsCommand) {
    Canvas canvas(100, 100);
    Paint paint;
    canvas.drawLine(0.0f, 0.0f, 100.0f, 100.0f, paint);
    EXPECT_EQ(1u, canvas.get_commands().size());
}

TEST(CanvasTest, DrawPathRecordsCommand) {
    Canvas canvas(100, 100);
    Paint paint;
    Path path;
    path.moveTo(0, 0);
    path.lineTo(50, 50);
    canvas.drawPath(path, paint);
    EXPECT_EQ(1u, canvas.get_commands().size());
}

TEST(CanvasTest, DrawTextRecordsCommand) {
    Canvas canvas(200, 100);
    Paint paint;
    canvas.drawText("Hi", 10.0f, 20.0f, paint);
    EXPECT_EQ(1u, canvas.get_commands().size());
}

TEST(CanvasTest, DrawColorRecordsCommand) {
    Canvas canvas(100, 100);
    canvas.drawColor(Color::WHITE);
    EXPECT_EQ(1u, canvas.get_commands().size());
}

TEST(CanvasTest, SaveAndRestore) {
    Canvas canvas(100, 100);
    auto count = canvas.save();
    EXPECT_EQ(2, count); // initial + 1 saved

    canvas.translate(10.0f, 0.0f);
    canvas.restore();
    EXPECT_EQ(1, canvas.getSaveCount());
}

TEST(CanvasTest, MultipleSaveRestore) {
    Canvas canvas(100, 100);
    canvas.save();
    canvas.save();
    EXPECT_EQ(3, canvas.getSaveCount());

    canvas.restore();
    EXPECT_EQ(2, canvas.getSaveCount());
    canvas.restore();
    EXPECT_EQ(1, canvas.getSaveCount());
}

TEST(CanvasTest, Translate) {
    Canvas canvas(100, 100);
    canvas.translate(10.0f, 20.0f);
    auto cmds = canvas.get_commands();
    EXPECT_GE(cmds.size(), 1u);
}

TEST(CanvasTest, Scale) {
    Canvas canvas(100, 100);
    canvas.scale(2.0f, 0.5f);
    EXPECT_EQ(1, canvas.getSaveCount());
}

TEST(CanvasTest, Rotate) {
    Canvas canvas(100, 100);
    canvas.rotate(45.0f);
    EXPECT_EQ(1, canvas.getSaveCount());
}

TEST(CanvasTest, ClipRect) {
    Canvas canvas(100, 100);
    canvas.clipRect(10.0f, 10.0f, 90.0f, 90.0f);
    EXPECT_EQ(1, canvas.getSaveCount());
}

TEST(CanvasTest, ClipPath) {
    Canvas canvas(100, 100);
    Path path;
    path.addCircle(50, 50, 40);
    canvas.clipPath(path);
    EXPECT_EQ(1, canvas.getSaveCount());
}

TEST(CanvasTest, MultipleCommands) {
    Canvas canvas(200, 200);
    Paint paint;
    paint.set_color(Color::RED);
    canvas.drawRect(0.0f, 0.0f, 50.0f, 50.0f, paint);

    paint.set_color(Color::BLUE);
    canvas.drawCircle(100.0f, 100.0f, 20.0f, paint);

    canvas.drawLine(0.0f, 0.0f, 200.0f, 200.0f, paint);
    EXPECT_EQ(3u, canvas.get_commands().size());
}

TEST(CanvasTest, SaveLayer) {
    Canvas canvas(100, 100);
    Paint paint;
    auto count = canvas.saveLayer(0.0f, 0.0f, 100.0f, 100.0f, &paint);
    EXPECT_GT(count, 0);
    canvas.restore();
}

TEST(CanvasTest, TransformAppliesToDrawCommands) {
    Canvas canvas(200, 200);
    canvas.translate(50.0f, 50.0f);
    Paint paint;
    canvas.drawRect(0.0f, 0.0f, 10.0f, 10.0f, paint);

    auto cmds = canvas.get_commands();
    EXPECT_EQ(2u, cmds.size()); // translate + drawRect
}
