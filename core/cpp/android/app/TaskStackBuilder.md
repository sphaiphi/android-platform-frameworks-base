# TaskStackBuilder - Reverse Engineering Documentation

## Executive Summary
`TaskStackBuilder` is a utility class designed to construct synthetic back stacks for cross-task navigation. It allows an application to launch a new task with a predetermined history of activities, ensuring that when the user presses the "Back" key, they move through the expected hierarchy rather than jumping back to a different task or the launcher prematurely.

## Architecture Overview
- **Core Components**:
    - `mIntents`: An ordered list of `Intent` objects representing the activities in the stack (bottom to top).
    - `mSourceContext`: The context used to resolve components and launch the activities.
- **Workflow**: 
    1. Builder is created using `create(context)`.
    2. Parent stacks are added via `addParentStack(...)`.
    3. The leaf activity intent is added via `addNextIntent(...)`.
    4. The stack is launched using `startActivities()` or used to create a `PendingIntent`.

## Detailed Functionality

### Parent Stack Resolution (`addParentStack`)
**Purpose**: Automatically builds the hierarchy based on manifest metadata.
**Algorithm**: 
1. Uses `PackageManager.getActivityInfo` to look up the `parentActivityName` attribute for a given component.
2. Iterates up the chain of parents, adding their intents to the list.
3. If it's the root of the task, it configures the intent as a main activity (`Intent.makeMainActivity`).

### Stack Execution (`startActivities`)
**Purpose**: Launches all activities in the list simultaneously.
**Mechanism**: Calls `Context.startActivitiesAsUser`. The first activity in the list is automatically flagged with `FLAG_ACTIVITY_NEW_TASK`, `FLAG_ACTIVITY_CLEAR_TASK`, and `FLAG_ACTIVITY_TASK_ON_HOME` to establish the new task identity.

### PendingIntent Generation (`getPendingIntent`)
**Purpose**: Provides a way to trigger the stack creation from a remote source (e.g., a notification).
**Mechanism**: Proxies to `PendingIntent.getActivities`, ensuring that the entire array of intents is correctly marshalled.

## API Reference
- `public static TaskStackBuilder create(Context context)`: Factory method.
- `public TaskStackBuilder addNextIntent(Intent nextIntent)`: Adds a single activity.
- `public TaskStackBuilder addParentStack(ComponentName sourceActivityName)`: Resolves hierarchy.
- `public void startActivities()`: Executes the launch.
- `public PendingIntent getPendingIntent(...)`: Creates a trigger token.

## Java-to-C++ Translation Guide
- **Intent List**: Map `ArrayList<Intent>` to `std::vector<android::content::Intent>`.
- **Manifest Lookup**: Use the native `PackageManager` AIDL to query `ActivityInfo`.
- **Launch Logic**: Port the flag manipulation logic (`getIntents()`) to the C++ builder.

## Implementation Risks
- **Recursive Metadata**: Deep parent hierarchies can lead to long resolution times or cycles if the manifest is malformed.
- **Intent Matching**: Ensure that resolved components match exactly what the system server expects for task root identification.
- **Security**: Launching stacks across user boundaries requires special permissions (`INTERACT_ACROSS_USERS`).
