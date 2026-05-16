#include <gtest/gtest.h>
#include <android/view/WindowManagerImpl.h>
#include <android/view/WindowLayoutParams.h>
#include <android/view/DisplayInfo.h>
#include <android/view/View.h>
#include <android/view/ViewRootImpl.h>
#include <android/view/WindowManagerGlobal.h>
#include <memory>

using namespace android::view;

class WindowManagerAddViewTest : public ::testing::Test {
protected:
    DisplayInfo default_display{1080, 1920, 0};

    void TearDown() override {
        // Clean up singleton state between tests
        WindowManagerGlobal::getInstance().clearForTesting();
    }
};

TEST_F(WindowManagerAddViewTest, AddViewSuccessCreatesViewRootImpl) {
    WindowManagerImpl wm(default_display);
    auto view = std::make_shared<View>();
    auto params = std::make_shared<WindowLayoutParams>(
        WindowLayoutParams::MATCH_PARENT,
        WindowLayoutParams::MATCH_PARENT
    );

    auto result = wm.addView(view, params);

    ASSERT_TRUE(static_cast<bool>(result));
    // View should be registered in WindowManagerGlobal
    auto& global = WindowManagerGlobal::getInstance();
    auto* rootImpl = global.findView(view);
    ASSERT_NE(rootImpl, nullptr);
}

TEST_F(WindowManagerAddViewTest, AddViewDuplicateRejected) {
    WindowManagerImpl wm(default_display);
    auto view = std::make_shared<View>();
    auto params = std::make_shared<WindowLayoutParams>(
        WindowLayoutParams::MATCH_PARENT,
        WindowLayoutParams::MATCH_PARENT
    );

    // First add should succeed
    auto result1 = wm.addView(view, params);
    ASSERT_TRUE(static_cast<bool>(result1));

    // Second add of same view should fail
    auto result2 = wm.addView(view, params);
    ASSERT_FALSE(static_cast<bool>(result2));
    EXPECT_EQ(result2.error(), "view already added to another window");
}

TEST_F(WindowManagerAddViewTest, AddViewWithNullViewRejected) {
    WindowManagerImpl wm(default_display);
    auto params = std::make_shared<WindowLayoutParams>(
        WindowLayoutParams::MATCH_PARENT,
        WindowLayoutParams::MATCH_PARENT
    );

    auto result = wm.addView(nullptr, params);
    ASSERT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.error(), "view is null");
}

TEST_F(WindowManagerAddViewTest, AddViewWithNullParamsRejected) {
    WindowManagerImpl wm(default_display);
    auto view = std::make_shared<View>();

    auto result = wm.addView(view, nullptr);
    ASSERT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.error(), "layout params is null");
}

TEST_F(WindowManagerAddViewTest, AddViewTriggersTraversal) {
    WindowManagerImpl wm(default_display);
    auto view = std::make_shared<View>();
    auto params = std::make_shared<WindowLayoutParams>(
        WindowLayoutParams::MATCH_PARENT,
        WindowLayoutParams::MATCH_PARENT
    );

    auto result = wm.addView(view, params);
    ASSERT_TRUE(static_cast<bool>(result));

    auto& global = WindowManagerGlobal::getInstance();
    auto* rootImpl = global.findView(view);
    ASSERT_NE(rootImpl, nullptr);
    // ViewRootImpl was created and set_view was called
    EXPECT_EQ(rootImpl->get_view(), view);
}

// --- User Story 2: Update a View's Layout ---

TEST_F(WindowManagerAddViewTest, UpdateViewLayoutSuccess) {
    WindowManagerImpl wm(default_display);
    auto view = std::make_shared<View>();
    auto params = std::make_shared<WindowLayoutParams>(
        WindowLayoutParams::MATCH_PARENT,
        WindowLayoutParams::MATCH_PARENT
    );

    auto addResult = wm.addView(view, params);
    ASSERT_TRUE(static_cast<bool>(addResult));

    // Update with new dimensions
    auto newParams = std::make_shared<WindowLayoutParams>(500, 800);
    auto updateResult = wm.updateViewLayout(view, newParams);

    ASSERT_TRUE(static_cast<bool>(updateResult));
    // Params should be updated in the registration
    auto& global = WindowManagerGlobal::getInstance();
    auto* rootImpl = global.findView(view);
    ASSERT_NE(rootImpl, nullptr);
}

TEST_F(WindowManagerAddViewTest, UpdateViewLayoutViewNotAttachedRejected) {
    WindowManagerImpl wm(default_display);
    auto view = std::make_shared<View>();
    auto params = std::make_shared<WindowLayoutParams>(
        WindowLayoutParams::MATCH_PARENT,
        WindowLayoutParams::MATCH_PARENT
    );

    // Never added the view — should fail
    auto updateResult = wm.updateViewLayout(view, params);
    ASSERT_FALSE(static_cast<bool>(updateResult));
    EXPECT_EQ(updateResult.error(), "view is not added to this window");
}

TEST_F(WindowManagerAddViewTest, UpdateViewLayoutWithNullViewRejected) {
    WindowManagerImpl wm(default_display);
    auto params = std::make_shared<WindowLayoutParams>(
        WindowLayoutParams::MATCH_PARENT,
        WindowLayoutParams::MATCH_PARENT
    );

    auto result = wm.updateViewLayout(nullptr, params);
    ASSERT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.error(), "view is null");
}

TEST_F(WindowManagerAddViewTest, UpdateViewLayoutWithNullParamsRejected) {
    WindowManagerImpl wm(default_display);
    auto view = std::make_shared<View>();

    auto result = wm.updateViewLayout(view, nullptr);
    ASSERT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.error(), "layout params is null");
}

// --- User Story 3: Remove a View from a Window ---

TEST_F(WindowManagerAddViewTest, RemoveViewSuccess) {
    WindowManagerImpl wm(default_display);
    auto view = std::make_shared<View>();
    auto params = std::make_shared<WindowLayoutParams>(
        WindowLayoutParams::MATCH_PARENT,
        WindowLayoutParams::MATCH_PARENT
    );

    auto addResult = wm.addView(view, params);
    ASSERT_TRUE(static_cast<bool>(addResult));

    // Verify view is registered
    auto& global = WindowManagerGlobal::getInstance();
    ASSERT_NE(global.findView(view), nullptr);

    // Remove the view
    auto removeResult = wm.removeView(view);
    ASSERT_TRUE(static_cast<bool>(removeResult));

    // View should no longer be registered
    ASSERT_EQ(global.findView(view), nullptr);
}

TEST_F(WindowManagerAddViewTest, RemoveViewNotAttachedRejected) {
    WindowManagerImpl wm(default_display);
    auto view = std::make_shared<View>();

    // Never added the view — should fail
    auto removeResult = wm.removeView(view);
    ASSERT_FALSE(static_cast<bool>(removeResult));
    EXPECT_EQ(removeResult.error(), "view is not added to this window");
}

TEST_F(WindowManagerAddViewTest, RemoveViewWithNullViewRejected) {
    WindowManagerImpl wm(default_display);

    auto result = wm.removeView(nullptr);
    ASSERT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.error(), "view is null");
}

// --- User Story 4: Query Display Information ---

TEST_F(WindowManagerAddViewTest, GetDefaultDisplayReturnsCorrectInfo) {
    DisplayInfo expected{1440, 2560, 90};
    WindowManagerImpl wm(expected);

    DisplayInfo actual = wm.getDefaultDisplay();

    EXPECT_EQ(actual.logicalWidth, expected.logicalWidth);
    EXPECT_EQ(actual.logicalHeight, expected.logicalHeight);
    EXPECT_EQ(actual.rotation, expected.rotation);
}
