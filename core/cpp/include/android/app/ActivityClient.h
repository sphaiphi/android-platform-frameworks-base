#pragma once

#include <android/os/IBinder.h>
#include <android/content/res/Configuration.h>
#include <android/content/Intent.h>
#include <android/content/ComponentName.h>
#include <android/app/ActivityManager.h>
#include <android/app/ActivityCommon.h>
#include <android/app/PictureInPictureParams.h>
#include <android/view/RemoteAnimationDefinition.h>
#include <android/os/Bundle.h>
#include <android/os/PersistableBundle.h>
#include <memory>
#include <string>
#include <expected_shim.h>
#include <optional>

namespace android::app {

class IActivityClientController {
public:
    virtual ~IActivityClientController() = default;

    // Lifecycle Reporting
    virtual auto activityIdle(const std::shared_ptr<android::os::IBinder>& token, const android::content::res::Configuration& config, bool stopProfiling) -> std::expected<void, ActivityError> = 0;
    virtual auto activityResumed(const std::shared_ptr<android::os::IBinder>& token, bool handleSplashScreenExit) -> std::expected<void, ActivityError> = 0;
    virtual auto activityRefreshed(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;
    virtual auto activityTopResumedStateLost() -> std::expected<void, ActivityError> = 0;
    virtual auto activityPaused(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;
    virtual auto activityStopped(const std::shared_ptr<android::os::IBinder>& token, const android::os::Bundle& state, const android::os::PersistableBundle& persistentState, const std::string& description) -> std::expected<void, ActivityError> = 0;
    virtual auto activityDestroyed(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;
    virtual auto activityLocalRelaunch(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;
    virtual auto activityRelaunched(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;

    // Task & Stack Management
    virtual auto moveActivityTaskToBack(const std::shared_ptr<android::os::IBinder>& token, bool nonRoot) -> std::expected<bool, ActivityError> = 0;
    virtual auto shouldUpRecreateTask(const std::shared_ptr<android::os::IBinder>& token, const std::string& destAffinity) -> std::expected<bool, ActivityError> = 0;
    virtual auto navigateUpTo(const std::shared_ptr<android::os::IBinder>& token, const std::shared_ptr<android::content::Intent>& destIntent, const std::string& resolvedType, int resultCode, const std::shared_ptr<android::content::Intent>& resultData) -> std::expected<bool, ActivityError> = 0;
    virtual auto releaseActivityInstance(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError> = 0;
    virtual auto finishActivity(const std::shared_ptr<android::os::IBinder>& token, int resultCode, const std::shared_ptr<android::content::Intent>& resultData, int finishTask) -> std::expected<bool, ActivityError> = 0;
    virtual auto finishActivityAffinity(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError> = 0;
    virtual auto finishSubActivity(const std::shared_ptr<android::os::IBinder>& token, const std::string& resultWho, int requestCode) -> std::expected<void, ActivityError> = 0;
    virtual auto isTopOfTask(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError> = 0;
    virtual auto willActivityBeVisible(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError> = 0;

    // Activity Information
    virtual auto getDisplayId(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<int, ActivityError> = 0;
    virtual auto getTaskForActivity(const std::shared_ptr<android::os::IBinder>& token, bool onlyRoot) -> std::expected<int, ActivityError> = 0;
    virtual auto getTaskConfiguration(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<std::optional<android::content::res::Configuration>, ActivityError> = 0;
    virtual auto getActivityTokenBelow(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<std::shared_ptr<android::os::IBinder>, ActivityError> = 0;
    virtual auto getCallingActivity(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<android::content::ComponentName, ActivityError> = 0;
    virtual auto getCallingPackage(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<std::string, ActivityError> = 0;
    virtual auto getLaunchedFromUid(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<int, ActivityError> = 0;
    virtual auto getLaunchedFromPackage(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<std::string, ActivityError> = 0;
    virtual auto getActivityCallerUid(const std::shared_ptr<android::os::IBinder>& token, const std::shared_ptr<android::os::IBinder>& callerToken) -> std::expected<int, ActivityError> = 0;
    virtual auto getActivityCallerPackage(const std::shared_ptr<android::os::IBinder>& token, const std::shared_ptr<android::os::IBinder>& callerToken) -> std::expected<std::string, ActivityError> = 0;

    // Configuration & Windowing
    virtual auto setRequestedOrientation(const std::shared_ptr<android::os::IBinder>& token, int requestedOrientation) -> std::expected<void, ActivityError> = 0;
    virtual auto getRequestedOrientation(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<int, ActivityError> = 0;
    virtual auto convertFromTranslucent(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError> = 0;
    virtual auto convertToTranslucent(const std::shared_ptr<android::os::IBinder>& token, const android::os::Bundle& options) -> std::expected<bool, ActivityError> = 0;
    virtual auto reportActivityFullyDrawn(const std::shared_ptr<android::os::IBinder>& token, bool restoredFromBundle) -> std::expected<void, ActivityError> = 0;
    virtual auto isImmersive(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError> = 0;
    virtual auto setImmersive(const std::shared_ptr<android::os::IBinder>& token, bool immersive) -> std::expected<void, ActivityError> = 0;
    virtual auto enterPictureInPictureMode(const std::shared_ptr<android::os::IBinder>& token, const android::app::PictureInPictureParams& params) -> std::expected<bool, ActivityError> = 0;
    virtual auto setPictureInPictureParams(const std::shared_ptr<android::os::IBinder>& token, const android::app::PictureInPictureParams& params) -> std::expected<void, ActivityError> = 0;
    virtual auto setShouldDockBigOverlays(const std::shared_ptr<android::os::IBinder>& token, bool shouldDockBigOverlays) -> std::expected<void, ActivityError> = 0;
    virtual auto toggleFreeformWindowingMode(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;
    virtual auto startLockTaskModeByToken(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;
    virtual auto stopLockTaskModeByToken(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;
    virtual auto showLockTaskEscapeMessage(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;
    virtual auto setTaskDescription(const std::shared_ptr<android::os::IBinder>& token, const android::app::ActivityManager::TaskDescription& td) -> std::expected<void, ActivityError> = 0;
    virtual auto setShowWhenLocked(const std::shared_ptr<android::os::IBinder>& token, bool showWhenLocked) -> std::expected<void, ActivityError> = 0;
    virtual auto setInheritShowWhenLocked(const std::shared_ptr<android::os::IBinder>& token, bool inheritShowWhenLocked) -> std::expected<void, ActivityError> = 0;
    virtual auto setTurnScreenOn(const std::shared_ptr<android::os::IBinder>& token, bool turnScreenOn) -> std::expected<void, ActivityError> = 0;
    virtual auto setAllowCrossUidActivitySwitchFromBelow(const std::shared_ptr<android::os::IBinder>& token, bool allowed) -> std::expected<void, ActivityError> = 0;
    virtual auto setRecentsScreenshotEnabled(const std::shared_ptr<android::os::IBinder>& token, bool enabled) -> std::expected<void, ActivityError> = 0;
    virtual auto invalidateHomeTaskSnapshot(const std::shared_ptr<android::os::IBinder>& homeToken) -> std::expected<void, ActivityError> = 0;

    // Transitions & Animations
    virtual auto overrideActivityTransition(const std::shared_ptr<android::os::IBinder>& token, bool open, int enterAnim, int exitAnim, int backgroundColor) -> std::expected<void, ActivityError> = 0;
    virtual auto clearOverrideActivityTransition(const std::shared_ptr<android::os::IBinder>& token, bool open) -> std::expected<void, ActivityError> = 0;
    virtual auto overridePendingTransition(const std::shared_ptr<android::os::IBinder>& token, const std::string& packageName, int enterAnim, int exitAnim, int backgroundColor) -> std::expected<void, ActivityError> = 0;
    virtual auto registerRemoteAnimations(const std::shared_ptr<android::os::IBinder>& token, const android::view::RemoteAnimationDefinition& definition) -> std::expected<void, ActivityError> = 0;
    virtual auto unregisterRemoteAnimations(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError> = 0;
};

class ActivityClient {
public:
    static auto getInstance() -> ActivityClient&;

    // Lifecycle Reporting
    auto activityIdle(const std::shared_ptr<android::os::IBinder>& token, const android::content::res::Configuration& config, bool stopProfiling) -> std::expected<void, ActivityError>;
    auto activityResumed(const std::shared_ptr<android::os::IBinder>& token, bool handleSplashScreenExit) -> std::expected<void, ActivityError>;
    auto activityRefreshed(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;
    auto activityTopResumedStateLost() -> std::expected<void, ActivityError>;
    auto activityPaused(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;
    auto activityStopped(const std::shared_ptr<android::os::IBinder>& token, const android::os::Bundle& state, const android::os::PersistableBundle& persistentState, const std::string& description) -> std::expected<void, ActivityError>;
    auto activityDestroyed(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;
    auto activityLocalRelaunch(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;
    auto activityRelaunched(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;

    // Task & Stack Management
    auto moveActivityTaskToBack(const std::shared_ptr<android::os::IBinder>& token, bool nonRoot) -> std::expected<bool, ActivityError>;
    auto shouldUpRecreateTask(const std::shared_ptr<android::os::IBinder>& token, const std::string& destAffinity) -> std::expected<bool, ActivityError>;
    auto navigateUpTo(const std::shared_ptr<android::os::IBinder>& token, const std::shared_ptr<android::content::Intent>& destIntent, const std::string& resolvedType, int resultCode, const std::shared_ptr<android::content::Intent>& resultData) -> std::expected<bool, ActivityError>;
    auto releaseActivityInstance(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError>;
    auto finishActivity(const std::shared_ptr<android::os::IBinder>& token, int resultCode, const std::shared_ptr<android::content::Intent>& resultData, int finishTask) -> std::expected<bool, ActivityError>;
    auto finishActivityAffinity(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError>;
    auto finishSubActivity(const std::shared_ptr<android::os::IBinder>& token, const std::string& resultWho, int requestCode) -> std::expected<void, ActivityError>;
    auto isTopOfTask(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError>;
    auto willActivityBeVisible(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError>;

    // Activity Information
    auto getDisplayId(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<int, ActivityError>;
    auto getTaskForActivity(const std::shared_ptr<android::os::IBinder>& token, bool onlyRoot) -> std::expected<int, ActivityError>;
    auto getTaskConfiguration(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<std::optional<android::content::res::Configuration>, ActivityError>;
    auto getActivityTokenBelow(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<std::shared_ptr<android::os::IBinder>, ActivityError>;
    auto getCallingActivity(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<android::content::ComponentName, ActivityError>;
    auto getCallingPackage(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<std::string, ActivityError>;
    auto getLaunchedFromUid(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<int, ActivityError>;
    auto getLaunchedFromPackage(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<std::string, ActivityError>;
    auto getActivityCallerUid(const std::shared_ptr<android::os::IBinder>& token, const std::shared_ptr<android::os::IBinder>& callerToken) -> std::expected<int, ActivityError>;
    auto getActivityCallerPackage(const std::shared_ptr<android::os::IBinder>& token, const std::shared_ptr<android::os::IBinder>& callerToken) -> std::expected<std::string, ActivityError>;

    // Configuration & Windowing
    auto setRequestedOrientation(const std::shared_ptr<android::os::IBinder>& token, int requestedOrientation) -> std::expected<void, ActivityError>;
    auto getRequestedOrientation(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<int, ActivityError>;
    auto convertFromTranslucent(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError>;
    auto convertToTranslucent(const std::shared_ptr<android::os::IBinder>& token, const android::os::Bundle& options) -> std::expected<bool, ActivityError>;
    auto reportActivityFullyDrawn(const std::shared_ptr<android::os::IBinder>& token, bool restoredFromBundle) -> std::expected<void, ActivityError>;
    auto isImmersive(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<bool, ActivityError>;
    auto setImmersive(const std::shared_ptr<android::os::IBinder>& token, bool immersive) -> std::expected<void, ActivityError>;
    auto enterPictureInPictureMode(const std::shared_ptr<android::os::IBinder>& token, const android::app::PictureInPictureParams& params) -> std::expected<bool, ActivityError>;
    auto setPictureInPictureParams(const std::shared_ptr<android::os::IBinder>& token, const android::app::PictureInPictureParams& params) -> std::expected<void, ActivityError>;
    auto setShouldDockBigOverlays(const std::shared_ptr<android::os::IBinder>& token, bool shouldDockBigOverlays) -> std::expected<void, ActivityError>;
    auto toggleFreeformWindowingMode(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;
    auto startLockTaskModeByToken(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;
    auto stopLockTaskModeByToken(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;
    auto showLockTaskEscapeMessage(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;
    auto setTaskDescription(const std::shared_ptr<android::os::IBinder>& token, const android::app::ActivityManager::TaskDescription& td) -> std::expected<void, ActivityError>;
    auto setShowWhenLocked(const std::shared_ptr<android::os::IBinder>& token, bool showWhenLocked) -> std::expected<void, ActivityError>;
    auto setInheritShowWhenLocked(const std::shared_ptr<android::os::IBinder>& token, bool inheritShowWhenLocked) -> std::expected<void, ActivityError>;
    auto setTurnScreenOn(const std::shared_ptr<android::os::IBinder>& token, bool turnScreenOn) -> std::expected<void, ActivityError>;
    auto setAllowCrossUidActivitySwitchFromBelow(const std::shared_ptr<android::os::IBinder>& token, bool allowed) -> std::expected<void, ActivityError>;
    auto setRecentsScreenshotEnabled(const std::shared_ptr<android::os::IBinder>& token, bool enabled) -> std::expected<void, ActivityError>;
    auto invalidateHomeTaskSnapshot(const std::shared_ptr<android::os::IBinder>& homeToken) -> std::expected<void, ActivityError>;

    // Transitions & Animations
    auto overrideActivityTransition(const std::shared_ptr<android::os::IBinder>& token, bool open, int enterAnim, int exitAnim, int backgroundColor) -> std::expected<void, ActivityError>;
    auto clearOverrideActivityTransition(const std::shared_ptr<android::os::IBinder>& token, bool open) -> std::expected<void, ActivityError>;
    auto overridePendingTransition(const std::shared_ptr<android::os::IBinder>& token, const std::string& packageName, int enterAnim, int exitAnim, int backgroundColor) -> std::expected<void, ActivityError>;
    auto registerRemoteAnimations(const std::shared_ptr<android::os::IBinder>& token, const android::view::RemoteAnimationDefinition& definition) -> std::expected<void, ActivityError>;
    auto unregisterRemoteAnimations(const std::shared_ptr<android::os::IBinder>& token) -> std::expected<void, ActivityError>;

    auto set_interface(std::shared_ptr<IActivityClientController> interface) -> void {
        interface_ = std::move(interface);
    }

private:
    ActivityClient() = default;
    void ensure_interface_selected();
    std::shared_ptr<IActivityClientController> interface_;
};

} // namespace android::app