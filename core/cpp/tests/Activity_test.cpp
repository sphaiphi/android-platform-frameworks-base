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
    bool call_super = true;

    auto on_create(const Bundle& icicle) -> void override {
        if (call_super) Activity::on_create(icicle);
        lifecycle_log.push_back("on_create");
    }
    auto on_start() -> void override {
        if (call_super) Activity::on_start();
        lifecycle_log.push_back("on_start");
    }
    auto on_restart() -> void override {
        if (call_super) Activity::on_restart();
        lifecycle_log.push_back("on_restart");
    }
    auto on_resume() -> void override {
        if (call_super) Activity::on_resume();
        lifecycle_log.push_back("on_resume");
    }
    auto on_pause() -> void override {
        if (call_super) Activity::on_pause();
        lifecycle_log.push_back("on_pause");
    }
    auto on_stop() -> void override {
        if (call_super) Activity::on_stop();
        lifecycle_log.push_back("on_stop");
    }
    auto on_destroy() -> void override {
        if (call_super) Activity::on_destroy();
        lifecycle_log.push_back("on_destroy");
    }
    auto on_activity_result(int32_t requestCode, int32_t resultCode, const std::optional<android::content::Intent>& data) -> void override {
        lifecycle_log.push_back("on_activity_result");
    }
    auto on_configuration_changed(const android::content::res::Configuration& /*new_config*/) -> void override {
        lifecycle_log.push_back("on_configuration_changed");
    }
    auto on_low_memory() -> void override {
        lifecycle_log.push_back("on_low_memory");
    }
    auto on_trim_memory(int32_t /*level*/) -> void override {
        lifecycle_log.push_back("on_trim_memory");
    }

    void set_window_for_test(std::shared_ptr<android::view::Window> window) {
        window_ = std::move(window);
    }
    void set_window_manager_for_test(std::shared_ptr<android::view::WindowManager> wm) {
        window_manager_ = std::move(wm);
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

TEST_F(ActivityTest, PerformCreateSuccess) {
    auto result = activity.perform_create(empty_bundle);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(activity.get_state(), ActivityState::created);
    ASSERT_EQ(activity.lifecycle_log.size(), 1);
    EXPECT_EQ(activity.lifecycle_log[0], "on_create");
}

TEST_F(ActivityTest, PerformCreateSuperNotCalled) {
    activity.call_super = false;
    auto result = activity.perform_create(empty_bundle);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), ActivityError::super_not_called);
}

TEST_F(ActivityTest, FullLifecycleSequence) {
    EXPECT_TRUE(activity.perform_create(empty_bundle).has_value());
    EXPECT_TRUE(activity.perform_start().has_value());
    EXPECT_TRUE(activity.perform_resume().has_value());
    
    EXPECT_EQ(activity.get_state(), ActivityState::resumed);
    
    EXPECT_TRUE(activity.perform_pause().has_value());
    EXPECT_TRUE(activity.perform_stop().has_value());
    EXPECT_TRUE(activity.perform_destroy().has_value());
    
    EXPECT_EQ(activity.get_state(), ActivityState::destroyed);
    
    std::vector<std::string> expected = {
        "on_create", "on_start", "on_resume", "on_pause", "on_stop", "on_destroy"
    };
    EXPECT_EQ(activity.lifecycle_log, expected);
}

TEST_F(ActivityTest, PerformRestart) {

    activity.perform_create(empty_bundle);

    activity.perform_start();

    activity.perform_stop();

    activity.lifecycle_log.clear();

    

    auto result = activity.perform_restart();

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(activity.get_state(), ActivityState::started);

    

    std::vector<std::string> expected = {"on_start"};

    EXPECT_EQ(activity.lifecycle_log, expected);

}



TEST_F(ActivityTest, ResultHandling) {



    activity.perform_create(empty_bundle);



    activity.lifecycle_log.clear();







    Intent result_data("result_action");



    activity.dispatch_activity_result("", 1, 100, result_data);



    



    ASSERT_EQ(activity.lifecycle_log.size(), 1);



    EXPECT_EQ(activity.lifecycle_log[0], "on_activity_result");



}







TEST_F(ActivityTest, SystemCallbacks) {







    android::content::res::Configuration config;







    activity.on_configuration_changed(config);







    activity.on_low_memory();







    activity.on_trim_memory(20);







    







    ASSERT_EQ(activity.lifecycle_log.size(), 3);







    EXPECT_EQ(activity.lifecycle_log[0], "on_configuration_changed");







    EXPECT_EQ(activity.lifecycle_log[1], "on_low_memory");







    EXPECT_EQ(activity.lifecycle_log[2], "on_trim_memory");







}















class MockWindow : public android::view::Window {







public:







    int last_layout_res_id = -1;







    void set_content_view(int layout_res_id) override {







        last_layout_res_id = layout_res_id;







    }







};















TEST_F(ActivityTest, WindowAndContentView) {















    auto mock_window = std::make_shared<MockWindow>();















    activity.set_window_for_test(mock_window);















    















    EXPECT_EQ(activity.get_window(), mock_window);















    















    activity.set_content_view(456);















    EXPECT_EQ(mock_window->last_layout_res_id, 456);















    















    auto mock_wm = std::make_shared<android::view::WindowManager>();















    activity.set_window_manager_for_test(mock_wm);















    EXPECT_EQ(activity.get_window_manager(), mock_wm);















}



class ActivityResultTest : public Activity {
public:
    using Activity::Activity;
    auto get_result_code() const { return result_code_; }
    auto get_result_data() const { return result_data_; }
};

TEST(ActivityResultTest, SetResult) {
    ActivityResultTest activity;
    Intent data("com.example.RESULT");
    activity.set_result(100, data);
    
    EXPECT_EQ(activity.get_result_code(), 100);
    ASSERT_TRUE(activity.get_result_data().has_value());
    EXPECT_EQ(activity.get_result_data()->getAction(), "com.example.RESULT");
}
































