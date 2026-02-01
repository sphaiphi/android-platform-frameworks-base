#include <gtest/gtest.h>
#include <android/app/ActivityClient.h>
#include <android/os/Bundle.h>
#include <android/content/Intent.h>
#include <android/content/res/Configuration.h>
#include <memory>
#include <optional>
#include <vector>
#include <string>

using namespace android::app;
using namespace android::os;
using namespace android::content;
using namespace android::content::res;

class MockActivityClientController : public IActivityClientController {
public:
    std::vector<std::string> call_log;

    // Lifecycle Reporting
    auto activityIdle(const std::shared_ptr<IBinder>& token, const Configuration& config, bool stopProfiling) -> std::expected<void, ActivityError> override {
        call_log.push_back("activityIdle");
        return {};
    }
    auto activityResumed(const std::shared_ptr<IBinder>& token, bool handleSplashScreenExit) -> std::expected<void, ActivityError> override {
        call_log.push_back("activityResumed");
        return {};
    }
    auto activityRefreshed(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override {
        call_log.push_back("activityRefreshed");
        return {};
    }
    auto activityTopResumedStateLost() -> std::expected<void, ActivityError> override {
        call_log.push_back("activityTopResumedStateLost");
        return {};
    }
    auto activityPaused(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override {
        call_log.push_back("activityPaused");
        return {};
    }
    auto activityStopped(const std::shared_ptr<IBinder>& token, const Bundle& state, const PersistableBundle& persistentState, const std::string& description) -> std::expected<void, ActivityError> override {
        call_log.push_back("activityStopped");
        return {};
    }
    auto activityDestroyed(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override {
        call_log.push_back("activityDestroyed");
        return {};
    }
    auto activityLocalRelaunch(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override {
        call_log.push_back("activityLocalRelaunch");
        return {};
    }
    auto activityRelaunched(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override {
        call_log.push_back("activityRelaunched");
        return {};
    }

    // Task & Stack Management
    auto moveActivityTaskToBack(const std::shared_ptr<IBinder>& token, bool nonRoot) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("moveActivityTaskToBack");
        return true; 
    }
    auto shouldUpRecreateTask(const std::shared_ptr<IBinder>& token, const std::string& destAffinity) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("shouldUpRecreateTask");
        return true; 
    }
    auto navigateUpTo(const std::shared_ptr<IBinder>& token, const std::shared_ptr<Intent>& destIntent, const std::string& resolvedType, int resultCode, const std::shared_ptr<Intent>& resultData) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("navigateUpTo");
        return true; 
    }
    auto releaseActivityInstance(const std::shared_ptr<IBinder>& token) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("releaseActivityInstance");
        return true; 
    }
    auto finishActivity(const std::shared_ptr<IBinder>& token, int resultCode, const std::shared_ptr<Intent>& resultData, int finishTask) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("finishActivity");
        return true; 
    }
    auto finishActivityAffinity(const std::shared_ptr<IBinder>& token) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("finishActivityAffinity");
        return true; 
    }
    auto finishSubActivity(const std::shared_ptr<IBinder>& token, const std::string& resultWho, int requestCode) -> std::expected<void, ActivityError> override { 
        call_log.push_back("finishSubActivity");
        return {}; 
    }
    auto isTopOfTask(const std::shared_ptr<IBinder>& token) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("isTopOfTask");
        return true; 
    }
    auto willActivityBeVisible(const std::shared_ptr<IBinder>& token) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("willActivityBeVisible");
        return true; 
    }

    // Activity Information
    auto getDisplayId(const std::shared_ptr<IBinder>& token) -> std::expected<int, ActivityError> override { 
        call_log.push_back("getDisplayId");
        return 0; 
    }
    auto getTaskForActivity(const std::shared_ptr<IBinder>& token, bool onlyRoot) -> std::expected<int, ActivityError> override { 
        call_log.push_back("getTaskForActivity");
        return 0; 
    }
    auto getTaskConfiguration(const std::shared_ptr<IBinder>& token) -> std::expected<std::optional<Configuration>, ActivityError> override { 
        call_log.push_back("getTaskConfiguration");
        return std::optional<Configuration>{}; 
    }
    auto getActivityTokenBelow(const std::shared_ptr<IBinder>& token) -> std::expected<std::shared_ptr<IBinder>, ActivityError> override { 
        call_log.push_back("getActivityTokenBelow");
        return nullptr; 
    }
    auto getCallingActivity(const std::shared_ptr<IBinder>& token) -> std::expected<ComponentName, ActivityError> override { 
        call_log.push_back("getCallingActivity");
        return ComponentName{}; 
    }
    auto getCallingPackage(const std::shared_ptr<IBinder>& token) -> std::expected<std::string, ActivityError> override { 
        call_log.push_back("getCallingPackage");
        return ""; 
    }
    auto getLaunchedFromUid(const std::shared_ptr<IBinder>& token) -> std::expected<int, ActivityError> override { 
        call_log.push_back("getLaunchedFromUid");
        return 0; 
    }
    auto getLaunchedFromPackage(const std::shared_ptr<IBinder>& token) -> std::expected<std::string, ActivityError> override { 
        call_log.push_back("getLaunchedFromPackage");
        return ""; 
    }
    auto getActivityCallerUid(const std::shared_ptr<IBinder>& token, const std::shared_ptr<IBinder>& callerToken) -> std::expected<int, ActivityError> override { 
        call_log.push_back("getActivityCallerUid");
        return 0; 
    }
    auto getActivityCallerPackage(const std::shared_ptr<IBinder>& token, const std::shared_ptr<IBinder>& callerToken) -> std::expected<std::string, ActivityError> override { 
        call_log.push_back("getActivityCallerPackage");
        return ""; 
    }

    // Configuration & Windowing
    auto setRequestedOrientation(const std::shared_ptr<IBinder>& token, int requestedOrientation) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setRequestedOrientation");
        return {}; 
    }
    auto getRequestedOrientation(const std::shared_ptr<IBinder>& token) -> std::expected<int, ActivityError> override { 
        call_log.push_back("getRequestedOrientation");
        return 0; 
    }
    auto convertFromTranslucent(const std::shared_ptr<IBinder>& token) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("convertFromTranslucent");
        return true; 
    }
    auto convertToTranslucent(const std::shared_ptr<IBinder>& token, const Bundle& options) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("convertToTranslucent");
        return true; 
    }
    auto reportActivityFullyDrawn(const std::shared_ptr<IBinder>& token, bool restoredFromBundle) -> std::expected<void, ActivityError> override { 
        call_log.push_back("reportActivityFullyDrawn");
        return {}; 
    }
    auto isImmersive(const std::shared_ptr<IBinder>& token) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("isImmersive");
        return true; 
    }
    auto setImmersive(const std::shared_ptr<IBinder>& token, bool immersive) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setImmersive");
        return {}; 
    }
    auto enterPictureInPictureMode(const std::shared_ptr<IBinder>& token, const PictureInPictureParams& params) -> std::expected<bool, ActivityError> override { 
        call_log.push_back("enterPictureInPictureMode");
        return true; 
    }
    auto setPictureInPictureParams(const std::shared_ptr<IBinder>& token, const PictureInPictureParams& params) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setPictureInPictureParams");
        return {}; 
    }
    auto setShouldDockBigOverlays(const std::shared_ptr<IBinder>& token, bool shouldDockBigOverlays) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setShouldDockBigOverlays");
        return {}; 
    }
    auto toggleFreeformWindowingMode(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override { 
        call_log.push_back("toggleFreeformWindowingMode");
        return {}; 
    }
    auto startLockTaskModeByToken(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override { 
        call_log.push_back("startLockTaskModeByToken");
        return {}; 
    }
    auto stopLockTaskModeByToken(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override { 
        call_log.push_back("stopLockTaskModeByToken");
        return {}; 
    }
    auto showLockTaskEscapeMessage(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override { 
        call_log.push_back("showLockTaskEscapeMessage");
        return {}; 
    }
    auto setTaskDescription(const std::shared_ptr<IBinder>& token, const ActivityManager::TaskDescription& td) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setTaskDescription");
        return {}; 
    }
    auto setShowWhenLocked(const std::shared_ptr<IBinder>& token, bool showWhenLocked) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setShowWhenLocked");
        return {}; 
    }
    auto setInheritShowWhenLocked(const std::shared_ptr<IBinder>& token, bool inheritShowWhenLocked) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setInheritShowWhenLocked");
        return {}; 
    }
    auto setTurnScreenOn(const std::shared_ptr<IBinder>& token, bool turnScreenOn) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setTurnScreenOn");
        return {}; 
    }
    auto setAllowCrossUidActivitySwitchFromBelow(const std::shared_ptr<IBinder>& token, bool allowed) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setAllowCrossUidActivitySwitchFromBelow");
        return {}; 
    }
    auto setRecentsScreenshotEnabled(const std::shared_ptr<IBinder>& token, bool enabled) -> std::expected<void, ActivityError> override { 
        call_log.push_back("setRecentsScreenshotEnabled");
        return {}; 
    }
    auto invalidateHomeTaskSnapshot(const std::shared_ptr<IBinder>& homeToken) -> std::expected<void, ActivityError> override { 
        call_log.push_back("invalidateHomeTaskSnapshot");
        return {}; 
    }

    // Transitions & Animations
    auto overrideActivityTransition(const std::shared_ptr<IBinder>& token, bool open, int enterAnim, int exitAnim, int backgroundColor) -> std::expected<void, ActivityError> override { 
        call_log.push_back("overrideActivityTransition");
        return {}; 
    }
    auto clearOverrideActivityTransition(const std::shared_ptr<IBinder>& token, bool open) -> std::expected<void, ActivityError> override { 
        call_log.push_back("clearOverrideActivityTransition");
        return {}; 
    }
    auto overridePendingTransition(const std::shared_ptr<IBinder>& token, const std::string& packageName, int enterAnim, int exitAnim, int backgroundColor) -> std::expected<void, ActivityError> override { 
        call_log.push_back("overridePendingTransition");
        return {}; 
    }
    auto registerRemoteAnimations(const std::shared_ptr<IBinder>& token, const android::view::RemoteAnimationDefinition& definition) -> std::expected<void, ActivityError> override { 
        call_log.push_back("registerRemoteAnimations");
        return {}; 
    }
    auto unregisterRemoteAnimations(const std::shared_ptr<IBinder>& token) -> std::expected<void, ActivityError> override { 
        call_log.push_back("unregisterRemoteAnimations");
        return {}; 
    }
};

class ActivityClientTest : public ::testing::Test {
protected:
    ActivityClient& client = ActivityClient::getInstance();
    std::shared_ptr<MockActivityClientController> mock;

    void SetUp() override {
        mock = std::make_shared<MockActivityClientController>();
        client.set_interface(mock);
    }
};

TEST(ActivityClientStaticTest, SingletonInitialization) {
    auto& client = ActivityClient::getInstance();
    client.set_interface(nullptr);
    auto result = client.activityPaused(nullptr);
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), ActivityError::service_not_found);
}

TEST_F(ActivityClientTest, LifecycleReporting) {
    Configuration config;
    Bundle state;
    // PersistableBundle persistentState; // Need to ensure it's available or mocked
    
    EXPECT_TRUE(client.activityIdle(nullptr, config, false).has_value());
    EXPECT_TRUE(client.activityResumed(nullptr, false).has_value());
    EXPECT_TRUE(client.activityRefreshed(nullptr).has_value());
    EXPECT_TRUE(client.activityTopResumedStateLost().has_value());
    EXPECT_TRUE(client.activityPaused(nullptr).has_value());
    EXPECT_TRUE(client.activityStopped(nullptr, state, {}, "").has_value());
    EXPECT_TRUE(client.activityDestroyed(nullptr).has_value());
    EXPECT_TRUE(client.activityLocalRelaunch(nullptr).has_value());
    EXPECT_TRUE(client.activityRelaunched(nullptr).has_value());

    std::vector<std::string> expected = {
        "activityIdle", "activityResumed", "activityRefreshed",
        "activityTopResumedStateLost", "activityPaused", "activityStopped",
        "activityDestroyed", "activityLocalRelaunch", "activityRelaunched"
    };
    EXPECT_EQ(mock->call_log, expected);
}

TEST_F(ActivityClientTest, TaskManagement) {
    mock->call_log.clear();
    
    EXPECT_TRUE(client.moveActivityTaskToBack(nullptr, false).has_value());
    EXPECT_TRUE(client.shouldUpRecreateTask(nullptr, "").has_value());
    EXPECT_TRUE(client.navigateUpTo(nullptr, nullptr, "", 0, nullptr).has_value());
    EXPECT_TRUE(client.releaseActivityInstance(nullptr).has_value());
    EXPECT_TRUE(client.finishActivity(nullptr, 0, nullptr, 0).has_value());
    EXPECT_TRUE(client.finishActivityAffinity(nullptr).has_value());
    EXPECT_TRUE(client.finishSubActivity(nullptr, "", 0).has_value());
    EXPECT_TRUE(client.isTopOfTask(nullptr).has_value());
    EXPECT_TRUE(client.willActivityBeVisible(nullptr).has_value());

    std::vector<std::string> expected = {
        "moveActivityTaskToBack", "shouldUpRecreateTask", "navigateUpTo",
        "releaseActivityInstance", "finishActivity", "finishActivityAffinity",
        "finishSubActivity", "isTopOfTask", "willActivityBeVisible"
    };
    EXPECT_EQ(mock->call_log, expected);
}

TEST_F(ActivityClientTest, InformationRetrieval) {
    mock->call_log.clear();

    EXPECT_TRUE(client.getDisplayId(nullptr).has_value());
    EXPECT_TRUE(client.getTaskForActivity(nullptr, false).has_value());
    EXPECT_TRUE(client.getTaskConfiguration(nullptr).has_value());
    EXPECT_TRUE(client.getActivityTokenBelow(nullptr).has_value());
    EXPECT_TRUE(client.getCallingActivity(nullptr).has_value());
    EXPECT_TRUE(client.getCallingPackage(nullptr).has_value());
    EXPECT_TRUE(client.getLaunchedFromUid(nullptr).has_value());
    EXPECT_TRUE(client.getLaunchedFromPackage(nullptr).has_value());
    EXPECT_TRUE(client.getActivityCallerUid(nullptr, nullptr).has_value());
    EXPECT_TRUE(client.getActivityCallerPackage(nullptr, nullptr).has_value());

    std::vector<std::string> expected = {
        "getDisplayId", "getTaskForActivity", "getTaskConfiguration",
        "getActivityTokenBelow", "getCallingActivity", "getCallingPackage",
        "getLaunchedFromUid", "getLaunchedFromPackage", "getActivityCallerUid",
        "getActivityCallerPackage"
    };
    EXPECT_EQ(mock->call_log, expected);
}

TEST_F(ActivityClientTest, ConfigurationAndWindowing) {
    mock->call_log.clear();

    PictureInPictureParams pipParams;
    ActivityManager::TaskDescription td;
    Bundle options;

    EXPECT_TRUE(client.setRequestedOrientation(nullptr, 0).has_value());
    EXPECT_TRUE(client.getRequestedOrientation(nullptr).has_value());
    EXPECT_TRUE(client.convertFromTranslucent(nullptr).has_value());
    EXPECT_TRUE(client.convertToTranslucent(nullptr, options).has_value());
    EXPECT_TRUE(client.reportActivityFullyDrawn(nullptr, false).has_value());
    EXPECT_TRUE(client.isImmersive(nullptr).has_value());
    EXPECT_TRUE(client.setImmersive(nullptr, false).has_value());
    EXPECT_TRUE(client.enterPictureInPictureMode(nullptr, pipParams).has_value());
    EXPECT_TRUE(client.setPictureInPictureParams(nullptr, pipParams).has_value());
    EXPECT_TRUE(client.setShouldDockBigOverlays(nullptr, false).has_value());
    EXPECT_TRUE(client.toggleFreeformWindowingMode(nullptr).has_value());
    EXPECT_TRUE(client.startLockTaskModeByToken(nullptr).has_value());
    EXPECT_TRUE(client.stopLockTaskModeByToken(nullptr).has_value());
    EXPECT_TRUE(client.showLockTaskEscapeMessage(nullptr).has_value());
    EXPECT_TRUE(client.setTaskDescription(nullptr, td).has_value());
    EXPECT_TRUE(client.setShowWhenLocked(nullptr, false).has_value());
    EXPECT_TRUE(client.setInheritShowWhenLocked(nullptr, false).has_value());
    EXPECT_TRUE(client.setTurnScreenOn(nullptr, false).has_value());
    EXPECT_TRUE(client.setAllowCrossUidActivitySwitchFromBelow(nullptr, false).has_value());
    EXPECT_TRUE(client.setRecentsScreenshotEnabled(nullptr, false).has_value());
    EXPECT_TRUE(client.invalidateHomeTaskSnapshot(nullptr).has_value());

    std::vector<std::string> expected = {
        "setRequestedOrientation", "getRequestedOrientation", "convertFromTranslucent",
        "convertToTranslucent", "reportActivityFullyDrawn", "isImmersive",
        "setImmersive", "enterPictureInPictureMode", "setPictureInPictureParams",
        "setShouldDockBigOverlays", "toggleFreeformWindowingMode", "startLockTaskModeByToken",
        "stopLockTaskModeByToken", "showLockTaskEscapeMessage", "setTaskDescription",
        "setShowWhenLocked", "setInheritShowWhenLocked", "setTurnScreenOn",
        "setAllowCrossUidActivitySwitchFromBelow", "setRecentsScreenshotEnabled",
        "invalidateHomeTaskSnapshot"
    };
    EXPECT_EQ(mock->call_log, expected);
}

TEST_F(ActivityClientTest, TransitionsAndAnimations) {
    mock->call_log.clear();

    android::view::RemoteAnimationDefinition definition;

    EXPECT_TRUE(client.overrideActivityTransition(nullptr, false, 0, 0, 0).has_value());
    EXPECT_TRUE(client.clearOverrideActivityTransition(nullptr, false).has_value());
    EXPECT_TRUE(client.overridePendingTransition(nullptr, "", 0, 0, 0).has_value());
    EXPECT_TRUE(client.registerRemoteAnimations(nullptr, definition).has_value());
    EXPECT_TRUE(client.unregisterRemoteAnimations(nullptr).has_value());

    std::vector<std::string> expected = {
        "overrideActivityTransition", "clearOverrideActivityTransition",
        "overridePendingTransition", "registerRemoteAnimations",
        "unregisterRemoteAnimations"
    };
    EXPECT_EQ(mock->call_log, expected);
}

TEST_F(ActivityClientTest, ServiceNotFound) {
    client.set_interface(nullptr);
    auto result = client.activityPaused(nullptr);
    EXPECT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), ActivityError::service_not_found);
}