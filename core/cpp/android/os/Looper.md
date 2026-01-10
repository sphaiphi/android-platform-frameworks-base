# Looper - Reverse Engineering Documentation

## Executive Summary
`Looper` manages the message loop for a thread. It owns a `MessageQueue` and continuously pulls messages from it (`loop()`), dispatching them to the appropriate `Handler`.

## Architecture Overview
-   **Pattern**: Event Loop.
-   **Storage**: `ThreadLocal<Looper>` ensures one Looper per thread.
-   **Main Looper**: A special static instance (`sMainLooper`) for the application's main (UI) thread.

## Detailed Functionality

### The Loop (`loop()`)
1.  Get `myLooper()`.
2.  Infinite Loop:
    -   `queue.next()`: Blocking call to get next message.
    -   **Logging**: Optional `Printer` logging start/end of dispatch.
    -   **Trace**: `Trace.traceBegin` with message target name.
    -   **Dispatch**: `msg.target.dispatchMessage(msg)`.
    -   **Recycle**: `msg.recycleUnchecked()`.

### Setup
-   **`prepare()`**: Creates the Looper and Queue, sets ThreadLocal.
-   **`prepareMainLooper()`**: Sets the global static main looper.

### Monitoring
-   **Slow Dispatch**: Can be configured (`setSlowLogThresholdMs`) to log warnings if dispatch takes too long.
-   **Observer**: `Looper.Observer` interface for fine-grained telemetry.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::Looper` (native).
-   **Difference**:
    -   Java `Looper` handles Java objects (`Message`, `Handler`).
    -   Native `Looper` handles File Descriptors (epoll) and generic `Message` structs.
    -   The Java `MessageQueue` uses the Native `Looper` for the low-level blocking (`nativePollOnce`).
-   **Integration**: A C++ `Looper` can be associated with a Java `Looper` via JNI (see `android_os_MessageQueue.cpp`).
