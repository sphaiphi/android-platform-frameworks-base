#include <gtest/gtest.h>
#include <android/view/InsetsSourceControl.h>
#include <android/view/InsetsSourceControlArray.h>
#include <android/view/Surface.h>
#include <android/graphics/Insets.h>
#include <android/graphics/Point.h>
#include <memory>
#include <vector>

namespace android::view {

TEST(InsetsSourceControlTest, BuilderBasic) {
    auto control = std::move(InsetsSourceControl::builder(1, 0x01)
        .set_initially_visible(true))
        .build();
    EXPECT_EQ(1, control->id);
    EXPECT_EQ(0x01, control->type);
    EXPECT_TRUE(control->initially_visible);
    EXPECT_FALSE(control->skip_animation_once);
}

TEST(InsetsSourceControlTest, BuilderWithLeash) {
    void* fake_surface = reinterpret_cast<void*>(0x42);
    auto control = std::move(InsetsSourceControl::builder(2, 0x04)
        .set_leash(std::make_shared<Surface>(fake_surface))
        .set_surface_position(android::graphics::Point{100, 200})
        .set_insets_hint(android::graphics::Insets::of(5, 10, 5, 20))
        .set_skip_animation_once(true))
        .build();
    EXPECT_TRUE(control->leash != nullptr);
    EXPECT_EQ(100, control->surface_position.x);
    EXPECT_EQ(200, control->surface_position.y);
    EXPECT_TRUE(control->insets_hint.has_value());
    EXPECT_EQ(10, control->insets_hint->top);
    EXPECT_TRUE(control->skip_animation_once);
}

TEST(InsetsSourceControlTest, BuilderDefaults) {
    auto control = std::move(InsetsSourceControl::builder(3, 0x08)).build();
    EXPECT_FALSE(control->initially_visible);
    EXPECT_FALSE(control->leash != nullptr);
    EXPECT_FALSE(control->insets_hint.has_value());
    EXPECT_EQ(0, control->surface_position.x);
    EXPECT_EQ(0, control->surface_position.y);
}

TEST(InsetsSourceControlArrayTest, DefaultConstructor) {
    InsetsSourceControlArray arr;
    EXPECT_TRUE(arr.controls.empty());
    EXPECT_EQ(0, arr.seq);
}

TEST(InsetsSourceControlArrayTest, WithControls) {
    auto c1 = std::move(InsetsSourceControl::builder(1, 0x01)).build();
    auto c2 = std::move(InsetsSourceControl::builder(2, 0x04)).build();
    std::vector<std::shared_ptr<InsetsSourceControl>> controls{c1, c2};

    InsetsSourceControlArray arr{controls, 42};
    ASSERT_EQ(2u, arr.controls.size());
    EXPECT_EQ(1, arr.controls[0]->id);
    EXPECT_EQ(2, arr.controls[1]->id);
    EXPECT_EQ(42, arr.seq);
}

TEST(InsetsSourceControlArrayTest, EmptyControls) {
    std::vector<std::shared_ptr<InsetsSourceControl>> controls;
    InsetsSourceControlArray arr{controls, 7};
    EXPECT_TRUE(arr.controls.empty());
    EXPECT_EQ(7, arr.seq);
}

} // namespace android::view
