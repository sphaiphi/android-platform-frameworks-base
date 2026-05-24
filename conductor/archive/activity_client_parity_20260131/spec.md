# Specification - ActivityClient Parity Update

## Overview
This track aims to bring the C++ `ActivityClient` implementation into parity with its Java counterpart (`ActivityClient.java`). The current C++ implementation is a skeleton with only a few lifecycle methods. This update will expand the API to support task management, activity info retrieval, configuration overrides, and windowing hooks, following the `JAVA.md` guidelines and C++23 standards.

## Functional Requirements
- **Comprehensive API Expansion**: Implement the following method categories:
    - **Lifecycle Reporting**: `activityIdle`, `activityRefreshed`, `activityTopResumedStateLost`, `activityLocalRelaunch`, `activityRelaunched`.
    - **Task & Stack Management**: `moveActivityTaskToBack`, `shouldUpRecreateTask`, `navigateUpTo`, `releaseActivityInstance`, `finishActivityAffinity`, `finishSubActivity`, `isTopOfTask`, `willActivityBeVisible`.
    - **Activity Information**: `getDisplayId`, `getTaskForActivity`, `getTaskConfiguration`, `getActivityTokenBelow`, `getCallingActivity`, `getCallingPackage`, `getLaunchedFromUid`, `getLaunchedFromPackage`, `getActivityCallerUid`, `getActivityCallerPackage`.
    - **Configuration & Windowing**: `setRequestedOrientation`, `getRequestedOrientation`, `convertFromTranslucent`, `convertToTranslucent`, `reportActivityFullyDrawn`, `isImmersive`, `setImmersive`, `enterPictureInPictureMode`, `setPictureInPictureParams`, `setShouldDockBigOverlays`, `toggleFreeformWindowingMode`, `startLockTaskModeByToken`, `stopLockTaskModeByToken`, `showLockTaskEscapeMessage`, `setTaskDescription`, `setShowWhenLocked`, `setInheritShowWhenLocked`, `setTurnScreenOn`, `setAllowCrossUidActivitySwitchFromBelow`, `setRecentsScreenshotEnabled`, `invalidateHomeTaskSnapshot`.
    - **Transitions & Animations**: `overrideActivityTransition`, `clearOverrideActivityTransition`, `overridePendingTransition`, `registerRemoteAnimations`, `unregisterRemoteAnimations`.
- **Error Handling**: Every Binder-proxying method must return `std::expected<T, ActivityError>` to handle `RemoteException` equivalents.
- **Singleton Implementation**: Refine the singleton pattern to be thread-safe and lazily initialize the `IActivityClientController` binder interface.

## Non-Functional Requirements
- **C++23 Standards**: Use modern C++ features and safety idioms.
- **Minimal Overhead**: Ensure the proxying logic adds negligible latency compared to the raw Binder transaction.
- **Memory Safety**: Use `std::shared_ptr` for `IBinder` and other shared resources.

## Acceptance Criteria
- `ActivityClient.h` contains method signatures for all scoped Java counterparts.
- `ActivityClient.cpp` implements the proxy logic for these methods.
- Unit tests in `ActivityClient_test.cpp` verify that each method correctly calls the mock `IActivityClientController`.
- The implementation builds successfully with the Android NDK.

## Out of Scope
- **Voice Interaction**: `startLocalVoiceInteraction`, `stopLocalVoiceInteraction`, `isRootVoiceInteraction`, `showAssistFromActivity`.
- **VR Mode**: `setVrMode`.
- **Media Projection**: `setForceSendResultForMediaProjection`.
- **Miscellaneous**: `reportSizeConfigurations`, `requestMultiwindowFullscreen`, `dismissKeyguard`, `onBackPressed`, `reportSplashScreenAttached`, `enableTaskLocaleOverride`, `isRequestedToLaunchInTaskFragment`, `setActivityRecordInputSinkEnabled`.
