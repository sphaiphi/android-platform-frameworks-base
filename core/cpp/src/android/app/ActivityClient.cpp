#include <android/app/ActivityClient.h>

namespace android::app {

auto ActivityClient::getInstance() -> ActivityClient& {
    static ActivityClient instance;
    instance.ensure_interface_selected();
    return instance;
}

void ActivityClient::ensure_interface_selected() {
    if (interface_) return;
    // TBD: Fetch from ServiceManager
    // interface_ = ActivityTaskManager::getService()->getActivityClientController();
}

// Lifecycle Reporting
auto ActivityClient::activityIdle(const std::shared_ptr<os::IBinder>& token, const content::res::Configuration& config, bool stopProfiling) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->activityIdle(token, config, stopProfiling);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::activityResumed(const std::shared_ptr<os::IBinder>& token, bool handleSplashScreenExit) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->activityResumed(token, handleSplashScreenExit);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::activityRefreshed(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->activityRefreshed(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::activityTopResumedStateLost() -> std::expected<void, ActivityError> {
    if (interface_) return interface_->activityTopResumedStateLost();
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::activityPaused(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->activityPaused(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::activityStopped(const std::shared_ptr<os::IBinder>& token, const os::Bundle& state, const os::PersistableBundle& persistentState, const std::string& description) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->activityStopped(token, state, persistentState, description);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::activityDestroyed(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->activityDestroyed(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::activityLocalRelaunch(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->activityLocalRelaunch(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::activityRelaunched(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->activityRelaunched(token);
    return std::unexpected(ActivityError::service_not_found);
}

// Task & Stack Management
auto ActivityClient::moveActivityTaskToBack(const std::shared_ptr<os::IBinder>& token, bool nonRoot) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->moveActivityTaskToBack(token, nonRoot);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::shouldUpRecreateTask(const std::shared_ptr<os::IBinder>& token, const std::string& destAffinity) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->shouldUpRecreateTask(token, destAffinity);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::navigateUpTo(const std::shared_ptr<os::IBinder>& token, const std::shared_ptr<content::Intent>& destIntent, const std::string& resolvedType, int resultCode, const std::shared_ptr<content::Intent>& resultData) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->navigateUpTo(token, destIntent, resolvedType, resultCode, resultData);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::releaseActivityInstance(const std::shared_ptr<os::IBinder>& token) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->releaseActivityInstance(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::finishActivity(const std::shared_ptr<os::IBinder>& token, int resultCode, const std::shared_ptr<content::Intent>& resultData, int finishTask) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->finishActivity(token, resultCode, resultData, finishTask);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::finishActivityAffinity(const std::shared_ptr<os::IBinder>& token) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->finishActivityAffinity(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::finishSubActivity(const std::shared_ptr<os::IBinder>& token, const std::string& resultWho, int requestCode) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->finishSubActivity(token, resultWho, requestCode);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::isTopOfTask(const std::shared_ptr<os::IBinder>& token) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->isTopOfTask(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::willActivityBeVisible(const std::shared_ptr<os::IBinder>& token) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->willActivityBeVisible(token);
    return std::unexpected(ActivityError::service_not_found);
}

// Activity Information
auto ActivityClient::getDisplayId(const std::shared_ptr<os::IBinder>& token) -> std::expected<int, ActivityError> {
    if (interface_) return interface_->getDisplayId(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getTaskForActivity(const std::shared_ptr<os::IBinder>& token, bool onlyRoot) -> std::expected<int, ActivityError> {
    if (interface_) return interface_->getTaskForActivity(token, onlyRoot);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getTaskConfiguration(const std::shared_ptr<os::IBinder>& token) -> std::expected<std::optional<content::res::Configuration>, ActivityError> {
    if (interface_) return interface_->getTaskConfiguration(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getActivityTokenBelow(const std::shared_ptr<os::IBinder>& token) -> std::expected<std::shared_ptr<os::IBinder>, ActivityError> {
    if (interface_) return interface_->getActivityTokenBelow(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getCallingActivity(const std::shared_ptr<os::IBinder>& token) -> std::expected<content::ComponentName, ActivityError> {
    if (interface_) return interface_->getCallingActivity(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getCallingPackage(const std::shared_ptr<os::IBinder>& token) -> std::expected<std::string, ActivityError> {
    if (interface_) return interface_->getCallingPackage(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getLaunchedFromUid(const std::shared_ptr<os::IBinder>& token) -> std::expected<int, ActivityError> {
    if (interface_) return interface_->getLaunchedFromUid(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getLaunchedFromPackage(const std::shared_ptr<os::IBinder>& token) -> std::expected<std::string, ActivityError> {
    if (interface_) return interface_->getLaunchedFromPackage(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getActivityCallerUid(const std::shared_ptr<os::IBinder>& token, const std::shared_ptr<os::IBinder>& callerToken) -> std::expected<int, ActivityError> {
    if (interface_) return interface_->getActivityCallerUid(token, callerToken);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getActivityCallerPackage(const std::shared_ptr<os::IBinder>& token, const std::shared_ptr<os::IBinder>& callerToken) -> std::expected<std::string, ActivityError> {
    if (interface_) return interface_->getActivityCallerPackage(token, callerToken);
    return std::unexpected(ActivityError::service_not_found);
}

// Configuration & Windowing
auto ActivityClient::setRequestedOrientation(const std::shared_ptr<os::IBinder>& token, int requestedOrientation) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setRequestedOrientation(token, requestedOrientation);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::getRequestedOrientation(const std::shared_ptr<os::IBinder>& token) -> std::expected<int, ActivityError> {
    if (interface_) return interface_->getRequestedOrientation(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::convertFromTranslucent(const std::shared_ptr<os::IBinder>& token) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->convertFromTranslucent(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::convertToTranslucent(const std::shared_ptr<os::IBinder>& token, const os::Bundle& options) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->convertToTranslucent(token, options);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::reportActivityFullyDrawn(const std::shared_ptr<os::IBinder>& token, bool restoredFromBundle) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->reportActivityFullyDrawn(token, restoredFromBundle);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::isImmersive(const std::shared_ptr<os::IBinder>& token) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->isImmersive(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::setImmersive(const std::shared_ptr<os::IBinder>& token, bool immersive) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setImmersive(token, immersive);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::enterPictureInPictureMode(const std::shared_ptr<os::IBinder>& token, const PictureInPictureParams& params) -> std::expected<bool, ActivityError> {
    if (interface_) return interface_->enterPictureInPictureMode(token, params);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::setPictureInPictureParams(const std::shared_ptr<os::IBinder>& token, const PictureInPictureParams& params) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setPictureInPictureParams(token, params);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::setShouldDockBigOverlays(const std::shared_ptr<os::IBinder>& token, bool shouldDockBigOverlays) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setShouldDockBigOverlays(token, shouldDockBigOverlays);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::toggleFreeformWindowingMode(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->toggleFreeformWindowingMode(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::startLockTaskModeByToken(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->startLockTaskModeByToken(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::stopLockTaskModeByToken(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->stopLockTaskModeByToken(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::showLockTaskEscapeMessage(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->showLockTaskEscapeMessage(token);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::setTaskDescription(const std::shared_ptr<os::IBinder>& token, const ActivityManager::TaskDescription& td) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setTaskDescription(token, td);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::setShowWhenLocked(const std::shared_ptr<os::IBinder>& token, bool showWhenLocked) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setShowWhenLocked(token, showWhenLocked);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::setInheritShowWhenLocked(const std::shared_ptr<os::IBinder>& token, bool inheritShowWhenLocked) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setInheritShowWhenLocked(token, inheritShowWhenLocked);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::setTurnScreenOn(const std::shared_ptr<os::IBinder>& token, bool turnScreenOn) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setTurnScreenOn(token, turnScreenOn);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::setAllowCrossUidActivitySwitchFromBelow(const std::shared_ptr<os::IBinder>& token, bool allowed) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setAllowCrossUidActivitySwitchFromBelow(token, allowed);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::setRecentsScreenshotEnabled(const std::shared_ptr<os::IBinder>& token, bool enabled) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->setRecentsScreenshotEnabled(token, enabled);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::invalidateHomeTaskSnapshot(const std::shared_ptr<os::IBinder>& homeToken) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->invalidateHomeTaskSnapshot(homeToken);
    return std::unexpected(ActivityError::service_not_found);
}

// Transitions & Animations
auto ActivityClient::overrideActivityTransition(const std::shared_ptr<os::IBinder>& token, bool open, int enterAnim, int exitAnim, int backgroundColor) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->overrideActivityTransition(token, open, enterAnim, exitAnim, backgroundColor);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::clearOverrideActivityTransition(const std::shared_ptr<os::IBinder>& token, bool open) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->clearOverrideActivityTransition(token, open);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::overridePendingTransition(const std::shared_ptr<os::IBinder>& token, const std::string& packageName, int enterAnim, int exitAnim, int backgroundColor) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->overridePendingTransition(token, packageName, enterAnim, exitAnim, backgroundColor);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::registerRemoteAnimations(const std::shared_ptr<os::IBinder>& token, const view::RemoteAnimationDefinition& definition) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->registerRemoteAnimations(token, definition);
    return std::unexpected(ActivityError::service_not_found);
}

auto ActivityClient::unregisterRemoteAnimations(const std::shared_ptr<os::IBinder>& token) -> std::expected<void, ActivityError> {
    if (interface_) return interface_->unregisterRemoteAnimations(token);
    return std::unexpected(ActivityError::service_not_found);
}

} // namespace android::app