#include <gtest/gtest.h>
#include <android/app/Activity.h>
#include <android/os/Bundle.h>
#include <android/content/Context.h>
#include <vector>
#include <string>

using namespace android::app;
using namespace android::os;
using namespace android::content;

class MockContext : public Context {
public:
    auto get_system_service(std::string_view name) -> std::expected<void*, ContextError> override {
        if (name == "test_service") {
            return reinterpret_cast<void*>(0x1234);
        }
        return std::unexpected(ContextError::service_not_found);
    }
    auto get_package_name() const -> std::string override {
        return "com.test.app";
    }
    auto get_files_dir() const -> std::string override {
        return "/data/user/0/com.test.app/files";
    }
    auto get_cache_dir() const -> std::string override {
        return "/data/user/0/com.test.app/cache";
    }
};

class TestActivity : public Activity {
public:
    using Activity::Activity;
    std::vector<std::string> lifecycle_log;

protected:
    auto on_create(const Bundle& /*saved_instance_state*/) -> void override {
        lifecycle_log.push_back("on_create");
    }
    auto on_start() -> void override {
        lifecycle_log.push_back("on_start");
    }
    auto on_resume() -> void override {
        lifecycle_log.push_back("on_resume");
    }
    auto on_pause() -> void override {
        lifecycle_log.push_back("on_pause");
    }
    auto on_stop() -> void override {
        lifecycle_log.push_back("on_stop");
    }
    auto on_destroy() -> void override {
        lifecycle_log.push_back("on_destroy");
    }
};

class ActivityTest : public ::testing::Test {
protected:
    TestActivity activity;
    Bundle empty_bundle;
};

TEST_F(ActivityTest, InitialState) {
    EXPECT_EQ(activity.get_state(), ActivityState::initialized);
}

TEST_F(ActivityTest, PerformCreate) {
    activity.perform_create(empty_bundle);
    EXPECT_EQ(activity.get_state(), ActivityState::created);
    ASSERT_EQ(activity.lifecycle_log.size(), 1);
    EXPECT_EQ(activity.lifecycle_log[0], "on_create");
}

TEST_F(ActivityTest, FullLifecycleSequence) {
    activity.perform_create(empty_bundle);
    activity.perform_start();
    activity.perform_resume();
    
    EXPECT_EQ(activity.get_state(), ActivityState::resumed);
    
    activity.perform_pause();
    activity.perform_stop();
    activity.perform_destroy();
    
    EXPECT_EQ(activity.get_state(), ActivityState::destroyed);
    
    std::vector<std::string> expected = {
        "on_create", "on_start", "on_resume", "on_pause", "on_stop", "on_destroy"
    };
    EXPECT_EQ(activity.lifecycle_log, expected);
}

TEST_F(ActivityTest, FinishTransition) {
    activity.perform_create(empty_bundle);
    activity.perform_start();
    activity.perform_resume();
    
    activity.finish();
    
    // In a real system, finish() might trigger lifecycle via ActivityThread.
    // For this unit test, we just check if it can be called.
    EXPECT_EQ(activity.get_state(), ActivityState::resumed);
}

TEST_F(ActivityTest, ContextDelegation) {
    auto mock_context = std::make_shared<MockContext>();
    activity.attach_base_context(mock_context);
    
    EXPECT_EQ(activity.get_package_name(), "com.test.app");
    
    auto service = activity.get_system_service("test_service");
    ASSERT_TRUE(service.has_value());
    EXPECT_EQ(service.value(), reinterpret_cast<void*>(0x1234));
    
    auto missing = activity.get_system_service("non_existent");
    ASSERT_FALSE(missing.has_value());
    EXPECT_EQ(missing.error(), ContextError::service_not_found);
}

TEST_F(ActivityTest, IntentHandling) {
    auto intent = std::make_shared<Intent>("android.intent.action.VIEW");
    activity.set_intent(intent);
    
    auto retrieved = activity.get_intent();
    ASSERT_NE(retrieved, nullptr);
    auto action = retrieved->getAction();
    ASSERT_TRUE(action.has_value());
    EXPECT_EQ(action.value(), "android.intent.action.VIEW");
}

TEST_F(ActivityTest, ThemeManagement) {
    activity.set_theme(123);
    EXPECT_EQ(activity.get_theme_res_id(), 123);
}
