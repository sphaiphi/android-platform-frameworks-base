#pragma once

#include <string>
#include <android/content/ComponentName.h>
#include <android/app/ActivityManager.h>

namespace android::app {

/**
 * Helper class for receiving notifications about changes to the task stack.
 */
class TaskStackListener {
public:
    virtual ~TaskStackListener() = default;

    virtual void onTaskStackChanged() {}
    virtual void onActivityPinned(const std::string& packageName, int userId, int taskId, int stackId) {}
    virtual void onActivityUnpinned() {}
    virtual void onActivityRestartAttempt(const ActivityManager::RunningTaskInfo& task, bool homeTaskVisible, bool clearedTask, bool wasVisible) {}
    virtual void onActivityForcedResizable(const std::string& packageName, int taskId, int reason) {}
    virtual void onActivityDismissingDockedTask() {}
    virtual void onActivityLaunchOnSecondaryDisplayFailed(const ActivityManager::RunningTaskInfo& taskInfo, int requestedDisplayId) {}
    virtual void onActivityLaunchOnSecondaryDisplayRerouted(const ActivityManager::RunningTaskInfo& taskInfo, int requestedDisplayId) {}
    virtual void onTaskCreated(int taskId, const android::content::ComponentName& componentName) {}
    virtual void onTaskRemoved(int taskId) {}
    virtual void onTaskMovedToFront(const ActivityManager::RunningTaskInfo& taskInfo) {}
    virtual void onTaskDescriptionChanged(const ActivityManager::RunningTaskInfo& taskInfo) {}
    virtual void onActivityRequestedOrientationChanged(int taskId, int requestedOrientation) {}
    virtual void onTaskRemovalStarted(const ActivityManager::RunningTaskInfo& taskInfo) {}
    virtual void onTaskProfileLocked(const ActivityManager::RunningTaskInfo& taskInfo, int userId) {}
    virtual void onTaskSnapshotInvalidated(int taskId) {}
    virtual void onBackPressedOnTaskRoot(const ActivityManager::RunningTaskInfo& taskInfo) {}
    virtual void onTaskDisplayChanged(int taskId, int newDisplayId) {}
    virtual void onRecentTaskListUpdated() {}
    virtual void onRecentTaskListFrozenChanged(bool frozen) {}
    virtual void onRecentTaskRemovedForAddTask(int taskId) {}
    virtual void onTaskFocusChanged(int taskId, bool focused) {}
    virtual void onTaskRequestedOrientationChanged(int taskId, int requestedOrientation) {}
    virtual void onActivityRotation(int displayId) {}
    virtual void onTaskMovedToBack(const ActivityManager::RunningTaskInfo& taskInfo) {}
    virtual void onLockTaskModeChanged(int mode) {}
};

} // namespace android::app
