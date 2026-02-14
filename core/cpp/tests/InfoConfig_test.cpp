#include <gtest/gtest.h>
#include <android/app/WindowConfiguration.h>
#include <android/app/ApplicationStartInfo.h>
#include <android/app/TaskInfo.h>
#include <android/app/ApplicationErrorReport.h>
#include <android/graphics/Rect.h>

using namespace android::app;
using namespace android::graphics;

TEST(InfoConfigTest, WindowConfiguration) {
    WindowConfiguration config;
    Rect bounds(0, 0, 1080, 1920);
    config.set_bounds(bounds);
    config.set_windowing_mode(WindowConfiguration::WINDOWING_MODE_FULLSCREEN);
    config.set_activity_type(WindowConfiguration::ACTIVITY_TYPE_STANDARD);

    EXPECT_EQ(config.get_bounds().left, 0);
    EXPECT_EQ(config.get_bounds().width(), 1080);
    EXPECT_EQ(config.get_windowing_mode(), WindowConfiguration::WINDOWING_MODE_FULLSCREEN);
    EXPECT_EQ(config.get_activity_type(), WindowConfiguration::ACTIVITY_TYPE_STANDARD);
}

TEST(InfoConfigTest, ApplicationStartInfo) {
    ApplicationStartInfo info;
    info.set_startup_state(ApplicationStartInfo::STARTUP_STATE_STARTED);
    info.set_pid(1234);
    info.set_package_name("com.test.app");
    info.set_reason(ApplicationStartInfo::START_REASON_LAUNCHER);
    info.set_start_type(ApplicationStartInfo::START_TYPE_COLD);
    info.add_startup_timestamp(1, 1000000000L);

    EXPECT_EQ(info.get_startup_state(), ApplicationStartInfo::STARTUP_STATE_STARTED);
    EXPECT_EQ(info.get_pid(), 1234);
    EXPECT_EQ(info.get_package_name(), "com.test.app");
    EXPECT_EQ(info.get_reason(), ApplicationStartInfo::START_REASON_LAUNCHER);
    EXPECT_EQ(info.get_start_type(), ApplicationStartInfo::START_TYPE_COLD);
    EXPECT_EQ(info.get_startup_timestamps().at(1), 1000000000L);
}

TEST(InfoConfigTest, TaskInfo) {
    TaskInfo info;
    info.set_task_id(10);
    info.set_visible(true);
    info.get_window_configuration_mutable().set_windowing_mode(WindowConfiguration::WINDOWING_MODE_FREEFORM);
    
    EXPECT_EQ(info.get_task_id(), 10);
    EXPECT_TRUE(info.is_visible());
    EXPECT_EQ(info.get_window_configuration().get_windowing_mode(), WindowConfiguration::WINDOWING_MODE_FREEFORM);
}

TEST(InfoConfigTest, ApplicationErrorReport) {
    ApplicationErrorReport report;
    report.type = ApplicationErrorReport::TYPE_CRASH;
    report.packageName = "com.test.app";
    report.crashInfo = std::make_unique<ApplicationErrorReport::CrashInfo>();
    report.crashInfo->exceptionMessage = "NullPointerException";

    EXPECT_EQ(report.type, ApplicationErrorReport::TYPE_CRASH);
    EXPECT_EQ(report.packageName, "com.test.app");
    ASSERT_NE(report.crashInfo, nullptr);
    EXPECT_EQ(report.crashInfo->exceptionMessage, "NullPointerException");
}
