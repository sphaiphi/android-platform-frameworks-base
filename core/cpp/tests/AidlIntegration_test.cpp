#include <gtest/gtest.h>
#include <android/view/IWindowManager.h>
#include <android/view/IWindowSession.h>
#include <android/hardware/display/IDisplayManager.h>
#include <android/hardware/input/IInputManager.h>

TEST(AidlIntegration, HeadersExistAndCompile) {
    using namespace android::view;
    using namespace android::hardware::display;
    using namespace android::hardware::input;

    EXPECT_NE(nullptr, std::make_unique<IWindowManager>().get());
    EXPECT_NE(nullptr, std::make_unique<IWindowSession>().get());
    EXPECT_NE(nullptr, std::make_unique<IDisplayManager>().get());
    EXPECT_NE(nullptr, std::make_unique<IInputManager>().get());
}
