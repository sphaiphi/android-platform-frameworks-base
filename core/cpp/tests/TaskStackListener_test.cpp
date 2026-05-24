#include <gtest/gtest.h>
#include <android/app/TaskStackListener.h>

using namespace android::app;

class TestTaskStackListener : public TaskStackListener {
public:
    bool stack_changed = false;
    int last_task_id = -1;

    void onTaskStackChanged() override {
        stack_changed = true;
    }

    void onTaskCreated(int taskId, const android::content::ComponentName& componentName) override {
        last_task_id = taskId;
    }
};

TEST(TaskStackListenerTest, CallbackOverrides) {
    TestTaskStackListener listener;
    
    listener.onTaskStackChanged();
    EXPECT_TRUE(listener.stack_changed);
    
    android::content::ComponentName cn("pkg", "cls");
    listener.onTaskCreated(123, cn);
    EXPECT_EQ(listener.last_task_id, 123);
}

TEST(TaskStackListenerTest, DefaultNoOps) {
    TaskStackListener listener;
    // Should not crash
    listener.onTaskStackChanged();
    ActivityManager::RunningTaskInfo info{456};
    listener.onTaskMovedToFront(info);
}
