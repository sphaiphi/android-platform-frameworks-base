# StateTracker - Reverse Engineering Documentation

## Executive Summary
`StateTracker` maintains the registry of UI widget states. It tracks "active" states (currently happening) and "previous" states (happened recently but ended). It associates every state change with VSYNC IDs (start and end), enabling the `JankDataProcessor` to correlate subsequent frame timing reports with the exact state of the UI at that moment.

## Architecture Overview
- **Dependencies**:
    - `Choreographer`: Used to obtain the current VSYNC ID.
    - `SimplePool`: Manages reuse of `StateData` objects.
- **Concurrency**: Thread-safe design. Uses `ConcurrentHashMap` for active states and `synchronized` blocks for the history list.

## Detailed Functionality

### 1. State Lifecycle
- **Put (Start)**: `putState`.
    - Checks limits (`MAX_CONCURRENT_STATE_COUNT`).
    - Acquires `StateData` from pool.
    - Sets `mVsyncIdStart = mChoreographer.getVsyncId()`.
    - Sets `mVsyncIdEnd = Long.MAX_VALUE`.
    - Stores in `mActiveStates` (Map).
- **Remove (End)**: `removeState`.
    - Removes from `mActiveStates`.
    - Sets `mVsyncIdEnd = mChoreographer.getVsyncId()`.
    - Adds to `mPreviousStates` (List) for later processing.
- **Update**: `updateState`.
    - Atomic-like `removeState` (old) + `putState` (new).

### 2. State Retrieval & Cleanup
- **Retrieve**: `retrieveAllStates`.
    - Returns a snapshot list containing ALL previous states + ALL active states.
    - Used by the processor to match frames against all possible relevant states.
- **Complete**: `stateProcessingComplete`.
    - Iterates `mPreviousStates`.
    - If `state.mProcessed` is true, removes from list and releases back to pool.

### 3. Pooling
- `MAX_POOL_SIZE` = 500.
- `StateData` objects are heavy enough to warrant pooling to avoid allocation churn during high-frequency UI events (scroll start/stop).

## Data Model

### Constants
- `MAX_CONCURRENT_STATE_COUNT` = 25.
- `MAX_PREVIOUSLY_ACTIVE_STATE_COUNT` = 1000.

### Inner Class: StateData
Mutable POJO representing a state interval.
- `mStateDataKey` (String): Composite key.
- `mVsyncIdStart` (long): Inclusive.
- `mVsyncIdEnd` (long): Inclusive (logic in processor implies inclusive range check).
- `mProcessed` (boolean): Flag to mark for cleanup.

## Java-Specific Features

### 1. Synchronization
- **Active States**: `ConcurrentHashMap`. Allows lock-free reads/writes for active states (mostly).
- **Previous States**: `ArrayList` guarded by `synchronized(mLock)`.
- **C++ Translation**:
    - Use `std::mutex` to protect `std::vector` (previous states).
    - Use `std::shared_mutex` (read/write lock) or `std::mutex` for the active states map.

### 2. Choreographer
**Concept**: `mChoreographer.getVsyncId()`.
**C++ Translation**:
- Need access to `AChoreographer` or internal `DisplayEventReceiver` to get the latest VSYNC ID matching the frame timeline.

## API Reference

### Public Methods
- `updateState(...)`
- `removeState(...)`
- `putState(...)`
- `retrieveAllStates(...)`: Populates a provided list.
- `stateProcessingComplete()`: Cleanup trigger.

## Java-to-C++ Translation Guide

### State Key Generation
`getStateKey` concatenates strings.
- **C++**: Avoid string concatenation for map keys. Use a `struct Key { string category; string id; string state; }` with a custom `std::hash` specialization.

### Memory Management
The `SimplePool` manages manual memory reuse.
- **C++**: This is less critical if using value semantics (`std::vector<StateData>`), but if `StateData` is allocated on heap, use a custom allocator or object pool. Given the max count (1000), a `std::vector` of objects (contiguous memory) is likely more performant than a pool of pointers.

## Edge Cases
- **Duplicate States**: `putState` returns early if key exists (idempotent).
- **Missing States**: `removeState` returns early if key not found.
- **Overflow**: If limits (25 active, 1000 previous) are reached, new data is dropped to preserve system stability.

## Implementation Risks
- **Vsync ID Synchronization**: Ensure the VSYNC ID source in C++ matches the one used by SurfaceFlinger/Java to ensure `start <= frame_vsync <= end` logic holds true.
