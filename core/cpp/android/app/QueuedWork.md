# QueuedWork - Reverse Engineering Documentation

## Executive Summary
`QueuedWork` is an internal utility to track process-global asynchronous work, primarily for `SharedPreferences` writes. It ensures that outstanding work is finished (e.g., when an Activity pauses) to prevent data loss.

## Architecture Overview
*   **Pattern**: Work Queue / Barrier.
*   **Threading**: Uses a dedicated single-thread `HandlerThread` ("queued-work-looper").

## Detailed Functionality
*   **Queueing**: `queue(Runnable, shouldDelay)`. Adds work to list and posts to handler.
*   **Finishers**: `addFinisher`/`removeFinisher`. Finishers are runnables that verify completion.
*   **Wait**: `waitToFinish()`. Triggers immediate processing of pending work on the main thread (or current thread) and waits for finishers. This is a "force finish" mechanism.

## Java-to-C++ Translation Guide
*   **Synchronization**: Critical. Uses locks (`sLock`, `sProcessingWork`) to coordinate between the work thread and the wait thread.
*   **Optimization**: `SharedPreferences` relies on this heavily. Efficient implementation is key.

## Implementation Risks
*   **ANRs**: `waitToFinish` is a blocking call often made on the UI thread. If the queue is long, it causes jank/ANRs.
