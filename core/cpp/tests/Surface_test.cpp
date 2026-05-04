#include <gtest/gtest.h>
#include <android/view/Surface.h>
#include <memory>

namespace android::view {

TEST(SurfaceTest, DefaultConstructorIsNull) {
    Surface surface;
    EXPECT_FALSE(surface.is_valid());
}

TEST(SurfaceTest, FromNativeHandle) {
    void* fake_handle = reinterpret_cast<void*>(0x1234);
    Surface surface(fake_handle);
    EXPECT_TRUE(surface.is_valid());
    EXPECT_EQ(fake_handle, surface.get_native_handle());
}

TEST(SurfaceTest, SharedPtrConstruction) {
    void* fake_handle = reinterpret_cast<void*>(0x5678);
    auto surface = std::make_shared<Surface>(fake_handle);
    EXPECT_TRUE(surface->is_valid());
}

TEST(SurfaceTest, NullHandleIsInvalid) {
    Surface surface(nullptr);
    EXPECT_FALSE(surface.is_valid());
}

TEST(SurfaceTest, CopyConstructor) {
    void* fake_handle = reinterpret_cast<void*>(0x9ABC);
    Surface a(fake_handle);
    Surface b(a);
    EXPECT_TRUE(b.is_valid());
    EXPECT_EQ(fake_handle, b.get_native_handle());
}

} // namespace android::view
