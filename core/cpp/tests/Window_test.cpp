#include <gtest/gtest.h>
#include <android/view/Window.h>
#include <android/view/View.h>
#include <memory>

using namespace android::view;

class MockWindowCallback : public Window::Callback {
public:
    bool content_changed = false;
    void on_content_changed() override {
        content_changed = true;
    }
    
    bool dispatch_key_event(int /*keycode*/) override { return false; }
    bool dispatch_touch_event(int /*action*/, float /*x*/, float /*y*/) override { return false; }
};

class TestWindow : public Window {
public:
    void set_content_view(int /*layout_res_id*/) override {
        if (get_callback()) {
            get_callback()->on_content_changed();
        }
    }
    
    void set_content_view(const std::shared_ptr<View>& view) override {
        content_view_ = view;
        if (get_callback()) {
            get_callback()->on_content_changed();
        }
    }
    
    std::shared_ptr<View> get_content_view() const { return content_view_; }

private:
    std::shared_ptr<View> content_view_;
};

class WindowTest : public ::testing::Test {
protected:
    std::shared_ptr<TestWindow> window;
    std::shared_ptr<MockWindowCallback> callback;
    
    void SetUp() override {
        window = std::make_shared<TestWindow>();
        callback = std::make_shared<MockWindowCallback>();
        window->set_callback(callback);
    }
};

TEST_F(WindowTest, CallbackOnContentChange) {
    auto view = std::make_shared<View>();
    EXPECT_FALSE(callback->content_changed);
    
    window->set_content_view(view);
    
    EXPECT_TRUE(callback->content_changed);
    EXPECT_EQ(view, window->get_content_view());
}

TEST_F(WindowTest, CallbackOnLayoutResId) {
    EXPECT_FALSE(callback->content_changed);
    
    window->set_content_view(123);
    
    EXPECT_TRUE(callback->content_changed);
}
