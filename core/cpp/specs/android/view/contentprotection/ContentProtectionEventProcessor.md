# ContentProtectionEventProcessor - Reverse Engineering Documentation

## Executive Summary
This class processes `ContentCaptureEvent`s to detect login scenarios for content protection. It buffers events and, upon detecting specific patterns (groups of strings) indicating a login attempt, flushes the event buffer to the `ContentCaptureManager` service.

## Architecture
*   **Event Buffer**: Uses `RingBuffer<ContentCaptureEvent>` to store recent events.
*   **Detection Logic**: Matches text content of events against configured "search groups" (sets of strings).
*   **State Management**: Tracks found groups (`mGroupsAll`) and resets detection state after a certain number of events if a full login pattern isn't matched.
*   **IPC**: Calls `mContentCaptureManager.onLoginDetected()` when a login is identified.

## Key Algorithms
*   **`processEvent`**:
    1.  Stores relevant events (APPEARED, DISAPPEARED, TEXT_CHANGED) in the buffer.
    2.  For `TYPE_VIEW_APPEARED`, extracts text/hint from the event.
    3.  Checks extracted text against search groups.
    4.  If a group is matched, marks it as found.
    5.  Checks if the combination of found groups satisfies the login condition (all required groups + threshold of optional groups).
    6.  If login detected -> `flush()` -> reset state.
    7.  If not detected but some group found -> decrement counter -> potential reset.

## Java-to-C++ Translation Guide
*   **RingBuffer**: `android.util.RingBuffer` likely needs a C++ equivalent (e.g., circular buffer over a `std::vector` or `std::deque`).
*   **Stream API**: Uses Java Streams (`stream().filter()...`). C++20 ranges or simple loops are the alternative.
*   **Time/Duration**: `java.time` -> `std::chrono`.
