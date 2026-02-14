# Specification - App Module Implementation

## Overview
This track involves implementing the core components of the `android.app` module in C++. The goal is to provide native equivalents of the Java framework classes, enabling native applications to interact with the Android system lifecycle and management services with minimal overhead.

## Functional Requirements
- **Core Component Implementation**: Implement the following C++ classes based on their Java counterparts in `@core/java/android/app/` and the identified specifications:
    - `Activity`
    - `ActivityThread`
    - `Instrumentation`
    - `ActivityManager`
    - `TaskStackListener`
    - `IActivityClientController`
- **Specification Alignment**: The following components from `@core/cpp/specs/android/app/` are within the scope of this implementation track:
    - `SyncNotedAppOp.md`
    - `ServiceStartNotAllowedException.md`
    - `FullscreenRequestHandler.md`
    - `RecoverableSecurityException.md`
    - `ForegroundServiceStartNotAllowedException.md`
    - `Instrumentation.md`
    - `NotificationHistory.md`
    - `AnrController.md`
    - `ForegroundServiceDelegationOptions.md`
    - `ConfigurationChangedListenerController.md`
    - `TaskStackBuilder.md`
    - `TaskStackListener.md`
    - `WindowConfiguration.md`
    - `TaskInfo.md`
    - `ListFragment.md`
    - `QueuedWork.md`
    - `ListActivity.md`
    - `ApplicationLoaders.md`
    - `AliasActivity.md`
    - `ContentProviderHolder.md`
    - `Activity.md`
    - `ExpandableListActivity.md`
    - `WallpaperManager.md`
    - `TabActivity.md`
    - `FragmentTransition.md`
    - `AppCompatCallbacks.md`
    - `DialogFragment.md`
    - `ProfilerInfo.md`
    - `PendingIntentStats.md`
    - `NotificationChannelGroup.md`
    - `IntentService.md`
    - `StartForegroundCalledOnStoppedServiceException.md`
    - `ActivityManager.md`
    - `PictureInPictureParams.md`
    - `AuthenticationRequiredException.md`
    - `AppOpsManager.md`
    - `CameraCompatTaskInfo.md`
    - `KeyguardManager.md`
    - `AutomaticZenRule.md`
    - `ActivityTransitionState.md`
    - `ActionBar.md`
    - `FragmentManager.md`
    - `RemoteLockscreenValidationResult.md`
    - `ServiceStartArgs.md`
    - `PictureInPictureUiState.md`
    - `HomeVisibilityListener.md`
    - `SystemServiceRegistry.md`
    - `AlertDialog.md`
    - `ApplicationThreadConstants.md`
    - `BroadcastStickyCache.md`
    - `Service.md`
    - `ApplicationStartInfo.md`
    - `DirectAction.md`
    - `PendingIntent.md`
    - `AppDetailsActivity.md`
    - `ZygotePreload.md`
    - `SearchManager.md`
    - `FragmentTransaction.md`
    - `BackStackRecord.md`
    - `AppCompatTaskInfo.md`
    - `UiAutomationConnection.md`
    - `FragmentBreadCrumbs.md`
    - `LoadedApk.md`
    - `ProcessMemoryState.md`
    - `RemoteServiceException.md`
    - `GrantedUriPermission.md`
    - `MediaRouteButton.md`
    - `SearchDialog.md`
    - `AsyncNotedAppOp.md`
    - `AppOpInfo.md`
    - `LocaleConfig.md`
    - `DownloadManager.md`
    - `ApplicationExitInfo.md`
    - `UiAutomation.md`
    - `DatePickerDialog.md`
    - `StackTrace.md`
- **API Parity**:
    - Ensure full Public API parity with the Java SDK for the prioritized components.
    - Implement **Selective Internal Parity**: Include critical internal logic such as lifecycle state machines, thread management, and IPC proxying.
- **Build System Integration**:
    - Integrate AIDL interfaces directly into the `ndk-build` (`Android.mk`) system.

## Non-Functional Requirements
- **Modern C++**: Use C++23 standards and safety-first idioms.
- **Performance**: Ensure zero-cost abstractions and minimize memory footprint.
- **Testing**: Maintain >80% code coverage with unit tests.

## Acceptance Criteria
1.  C++ headers and source files created for the components.
2.  `Android.mk` updated to include and compile the new components and their AIDL dependencies.
3.  Unit tests implemented in `core/cpp/tests/` verifying behavior.
4.  All tests pass in the build environment.

## Out of Scope
- Manual review of the implementation.
