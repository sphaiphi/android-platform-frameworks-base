# FileObserver - Reverse Engineering Documentation

## Executive Summary
`FileObserver` allows monitoring file system events (create, delete, modify) on a specific file or directory. It wraps the Linux `inotify` subsystem via JNI.

## Architecture Overview
-   **Mechanism**: `inotify`.
-   **Components**:
    -   `ObserverThread`: A static singleton thread that reads from the `inotify` file descriptor.
    -   `FileObserver` (Abstract Base): Clients subclass this and implement `onEvent`.
    -   `mRealObservers` (SparseArray): Maps inotify watch descriptors (WFD) to `WeakReference<FileObserver>`.

## Detailed Functionality

### The Observer Thread
-   **Loop**: Infinite loop calling `nativeWaitForNextEvent()`.
-   **Dispatch**: When an event arrives (WFD + mask + path), it looks up the observer in `mRealObservers` and calls `onEvent`.

### Registration
-   **`startWatching()`**: Calls `s_observerThread.startWatching()`, which calls `nativeAddMatch` / `inotify_add_watch`.
-   **`stopWatching()`**: Calls `nativeRemoveMatch` / `inotify_rm_watch`.

## Data Model
-   **Events**: Integer constants mirroring `inotify.h` (`ACCESS`, `MODIFY`, `ATTRIB`, `CLOSE_WRITE`, etc.).

## Java-to-C++ Translation Guide
-   **Native**: This class is a wrapper *around* C++ functionality (`android_util_FileObserver.cpp`).
-   **Usage**: In C++, use `inotify` directly (`sys/inotify.h`).
-   **Thread Model**: You need a dedicated thread to block on `read(inotify_fd)`. The Java implementation's pattern of a single thread dispatching to multiple listeners is a good pattern to copy for a C++ service.

## Implementation Risks
-   **Overflow**: `inotify` queues can overflow if events come faster than read.
-   **Garbage Collection**: The Java implementation uses `WeakReference`. If the `FileObserver` object is GC'd, it stops getting events. In C++, use `std::shared_ptr` or explicit lifetime management.
