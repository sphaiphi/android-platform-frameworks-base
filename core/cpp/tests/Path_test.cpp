#include <gtest/gtest.h>
#include <android/graphics/Path.h>

using namespace android::graphics;

TEST(PathTest, DefaultIsEmpty) {
    Path path;
    EXPECT_TRUE(path.is_empty());
}

TEST(PathTest, MoveTo) {
    Path path;
    path.moveTo(10.0f, 20.0f);
    EXPECT_FALSE(path.is_empty());
}

TEST(PathTest, LineTo) {
    Path path;
    path.moveTo(0.0f, 0.0f);
    path.lineTo(10.0f, 20.0f);
    EXPECT_FALSE(path.is_empty());
}

TEST(PathTest, Close) {
    Path path;
    path.moveTo(0.0f, 0.0f);
    path.lineTo(10.0f, 0.0f);
    path.lineTo(10.0f, 10.0f);
    path.close();
    EXPECT_FALSE(path.is_empty());
}

TEST(PathTest, Reset) {
    Path path;
    path.moveTo(0.0f, 0.0f);
    path.lineTo(10.0f, 10.0f);
    path.reset();
    EXPECT_TRUE(path.is_empty());
}

TEST(PathTest, AddRect) {
    Path path;
    path.addRect(0.0f, 0.0f, 100.0f, 50.0f);
    EXPECT_FALSE(path.is_empty());
}

TEST(PathTest, AddCircle) {
    Path path;
    path.addCircle(50.0f, 50.0f, 40.0f);
    EXPECT_FALSE(path.is_empty());
}

TEST(PathTest, AddOval) {
    Path path;
    path.addOval(0.0f, 0.0f, 100.0f, 50.0f);
    EXPECT_FALSE(path.is_empty());
}

TEST(PathTest, FillType) {
    Path path;
    EXPECT_EQ(Path::FillType::WINDING, path.get_fill_type());

    path.set_fill_type(Path::FillType::EVEN_ODD);
    EXPECT_EQ(Path::FillType::EVEN_ODD, path.get_fill_type());

    path.set_fill_type(Path::FillType::INVERSE_WINDING);
    EXPECT_EQ(Path::FillType::INVERSE_WINDING, path.get_fill_type());

    path.set_fill_type(Path::FillType::INVERSE_EVEN_ODD);
    EXPECT_EQ(Path::FillType::INVERSE_EVEN_ODD, path.get_fill_type());
}

TEST(PathTest, ComputeBounds) {
    Path path;
    path.moveTo(10.0f, 20.0f);
    path.lineTo(90.0f, 80.0f);

    Rect bounds = path.computeBounds();
    EXPECT_EQ(10, bounds.left);
    EXPECT_EQ(20, bounds.top);
    EXPECT_EQ(90, bounds.right);
    EXPECT_EQ(80, bounds.bottom);
}

TEST(PathTest, ComputeBoundsEmpty) {
    Path path;
    Rect bounds = path.computeBounds();
    EXPECT_TRUE(bounds.isEmpty());
}

TEST(PathTest, MultipleOperations) {
    Path path;
    path.moveTo(0.0f, 0.0f);
    path.lineTo(10.0f, 0.0f);
    path.lineTo(10.0f, 10.0f);
    path.close();
    EXPECT_FALSE(path.is_empty());
}

TEST(PathTest, ArcTo) {
    Path path;
    path.arcTo(0.0f, 0.0f, 100.0f, 100.0f, 0.0f, 90.0f, false);
    EXPECT_FALSE(path.is_empty());
}

TEST(PathTest, AddArc) {
    Path path;
    path.addArc(0.0f, 0.0f, 100.0f, 100.0f, 0.0f, 180.0f);
    EXPECT_FALSE(path.is_empty());
}

TEST(PathTest, CopyConstructor) {
    Path original;
    original.moveTo(5.0f, 10.0f);
    original.lineTo(20.0f, 30.0f);
    original.set_fill_type(Path::FillType::EVEN_ODD);

    Path copy(original);
    EXPECT_FALSE(copy.is_empty());
    EXPECT_EQ(Path::FillType::EVEN_ODD, copy.get_fill_type());
}

TEST(PathTest, AssignmentOperator) {
    Path original;
    original.addCircle(0.0f, 0.0f, 50.0f);

    Path assigned;
    assigned = original;
    EXPECT_FALSE(assigned.is_empty());
}
