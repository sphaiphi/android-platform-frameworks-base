# WaitResult - Reverse Engineering Documentation

## Executive Summary
`WaitResult` is a data container used by the `ActivityTaskManager` to return the outcome of waiting for an activity to start (e.g., when using `am start -W`). It captures information about the launch success, whether a timeout occurred, which component was launched, the total time elapsed, and the specific type of launch (Cold, Warm, Hot, or Relaunch).

## Architecture Overview
- **Structure**:
    - `result`: The numerical outcome of the activity launch.
    - `timeout`: Boolean indicating if the wait timed out.
    - `who`: The `ComponentName` of the activity that actually launched.
    - `totalTime`: Milliseconds spent in the launch sequence.
    - `launchState`: Enum-like integer describing the process state during launch.
- **Launch States**:
    - `COLD` (1): New process started.
    - `WARM` (2): Process reused, activity created.
    - `HOT` (3): Process reused, activity brought to front.
    - `RELAUNCH` (4): Process reused, activity destroyed and recreated.
- **Inheritance**: Implements `Parcelable`.

## Detailed Functionality

### Launch Tracking
**Purpose**: Measuring app startup performance.
**Logic**: The `launchState` provides critical context for interpreting the `totalTime`. Cold starts are expected to take longer than hot starts.

### Serialization
**Mechanism**: 
- `writeToParcel`: Writes all fields, using `ComponentName.writeToParcel` for the `who` field.
- `readFromParcel`: Reconstructs the object.

## API Reference
- `public int result`: Outcome code.
- `public long totalTime`: Duration in ms.
- `public @LaunchState int launchState`: Launch category.
- `public static String launchStateToString(int type)`: Human-readable converter.

## Java-to-C++ Translation Guide
- **Data Struct**: Map to a simple C++ `class` or `struct`.
- **Enum Mapping**: Use a C++ `enum class` for `LaunchState`.
- **Parceling**: Implement standard `writeToParcel` and `readFromParcel` logic.

## Implementation Risks
- **Measurement Accuracy**: `totalTime` depends on precise instrumentation within the `ActivityStack` and `ProcessRecord` management logic. C++ implementation must match this timing exactly for consistent reports.
- **State Validity**: `who` may be null if the launch failed or was aborted before a component was identified.
