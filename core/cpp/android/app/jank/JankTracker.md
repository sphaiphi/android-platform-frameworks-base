# JankTracker - Reverse Engineering Documentation

## Executive Summary
`JankTracker` is the primary controller for the app jank metrics system. It orchestrates the lifecycle of jank tracking, manages the background processing thread, registers with the system's `SurfaceControl` to receive frame timing data (`JankData`), and acts as the facade for UI components to report their state.

## Architecture Overview
- **Pattern**: Controller / Facade.
- **Threading Model**:
    - **Main Thread**: Creation, state updates (`addUiState`, `updateUiState`), lifecycle methods.
    - **Background Thread (`AppJankTracker`)**: Processing of `JankData` (via `JankDataProcessor`).
- **Components**:
    - `StateTracker`: Manages widget state history.
    - `JankDataProcessor`: Correlates frames to states.
    - `HandlerThread`: Dedicated thread for processing callbacks.

## Detailed Functionality

### 1. Initialization & Lifecycle
**Constructor**: `JankTracker(Choreographer, View)` or `JankTracker(View)`.
- Starts `HandlerThread` ("AppJankTracker").
- Registers `OnWindowAttachListener` on the `DecorView`.

**Window Attachment (`initializeJankTrackingComponents`)**:
- Triggered when window is attached.
- Delayed by `REGISTRATION_DELAY_MS` (1000ms).
- Initializes `StateTracker` (needs `Choreographer`) and `JankDataProcessor`.
- Registers `OnJankDataListener` with `SurfaceControl`.

### 2. State Management API
**Methods**: `addUiState`, `removeUiState`, `updateUiState`.
**Logic**:
- Checks `shouldTrack()` (tracking enabled AND listeners registered).
- Delegates to `mStateTracker`.
- These are the methods called by UI widgets (e.g., RecyclerView) to say "I am scrolling now".

### 3. Jank Data Reception
**Callback**: `SurfaceControl.OnJankDataListener`.
**Flow**:
- System calls `onJankDataAvailable` on the background thread executor.
- Delegates to `mJankDataProcessor.processJankData`.

### 4. External Stat Merging
**Method**: `mergeAppJankStats`.
- Posts a runnable to the background handler to merge stats safely.
- Validates UID matches the app UID.

## Data Model
- **Core Fields**:
    - `mStateTracker`: `StateTracker` instance.
    - `mJankDataProcessor`: `JankDataProcessor` instance.
    - `mSurfaceControl`: `AttachedSurfaceControl` handle.
    - `mTrackingEnabled`: Boolean flag for app-level control.
    - `mListenersRegistered`: Boolean flag indicating active system link.

## Java-Specific Features

### 1. HandlerThread & Handler
**Concept**: Android specific mechanism for a thread with a Looper (message queue).
**C++ Translation**:
- Use `std::thread` with a message queue (Looper equivalent) or `ALooper` if using NDK.
- All tasks posted via `mHandler.post(...)` must be serialized onto this worker thread.

### 2. SurfaceControl Listener
**Concept**: `SurfaceControl.registerOnJankDataListener`.
**C++ Translation**:
- This maps to NDK `ASurfaceControl` or internal native `SurfaceControl` APIs to register for frame metrics/jank data.

### 3. ViewTreeObserver
**Concept**: `addOnWindowAttachListener`.
**C++ Translation**:
- In a native context, you might not have a `View` system. You usually hook into the NativeActivity or `ANativeWindow` lifecycle events.

## API Reference

### Public Methods
- `enableAppJankTracking()`: Starts tracking, registers listener.
- `disableAppJankTracking()`: Stops tracking, unregisters.
- `addUiState(...)`, `removeUiState(...)`, `updateUiState(...)`: State reporting APIs.
- `mergeAppJankStats(...)`: Injection API.

## Java-to-C++ Translation Guide

### Synchronization
The class mixes main thread state updates with background thread data processing.
- `mStateTracker` is accessed from both. `StateTracker` uses `ConcurrentHashMap` and `synchronized` blocks internally.
- **C++**: Ensure the C++ `StateTracker` equivalent is thread-safe (mutexes on state maps).

### Delayed Registration
**Logic**: `REGISTRATION_DELAY_MS` (1s) delay before registering listener.
**Reason**: To avoid missing data during warm starts (bug workaround).
**C++**: Implement a similar delayed task mechanism if the underlying system behavior is the same.

## Implementation Risks
- **Lifecycle Races**: Window detachment vs Background thread processing. Ensure the background thread doesn't access the `StateTracker` after it has been destroyed.
- **Callback Overhead**: `onJankDataAvailable` can receive large batches. Ensure processing doesn't block the thread too long if it shares duties.
