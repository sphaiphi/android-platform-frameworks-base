# MetricsReader - Reverse Engineering Documentation

## Executive Summary
`MetricsReader` is a utility class designed to read, filter, and sessionize platform metric logs. It interfaces with the underlying system's `EventLog` to retrieve raw events and converts them into structured `LogMaker` objects. It supports "checkpointing," allowing clients to ignore events that occurred before a specific point in time, and provides a queue-based iterator interface for consuming logs.

## Architecture Overview
- **Data Source**: Android `EventLog` (native system logging).
- **Data Transformation**: Converts `EventLog.Event` -> `MetricsReader.Event` -> `LogMaker`.
- **Session Management**: Maintains two queues:
    - `mPendingQueue`: Events read but not yet consumed by the client.
    - `mSeenQueue`: Events already consumed (kept for `reset()` capability).
- **Synchronization**: Uses a "checkpoint" tag (written to the log itself) to synchronize the reader with a specific timeline marker.

## Detailed Functionality

### Log Reading Process (`read(long horizonMs)`)
1.  **Fetch**: Calls `LogReader.readEvents` to get raw logs from the system (blocking up to `horizonMs` if needed).
2.  **Reset**: Clears existing internal queues (`mPendingQueue`, `mSeenQueue`).
3.  **Process**: Iterates through fetched native events:
    - Wraps scalar data in an array if necessary.
    - Constructs a `LogMaker` from the event data.
    - Populates metadata (Timestamp, UID, PID) into the `LogMaker`.
4.  **Filter/Checkpoint**:
    - Checks if the event is a `METRICS_CHECKPOINT`.
    - If it matches the current `mCheckpointTag`, the pending queue is cleared (effective reset).
    - Otherwise, the log is added to `mPendingQueue`.

### Checkpointing (`checkpoint()`)
- **Purpose**: To mark a "start fresh" point.
- **Mechanism**:
    1.  Generates a new random-ish tag: `(System.currentTimeMillis() % 0x7fffffff)`.
    2.  Writes this tag to the system log via `MetricsLogger.action(METRICS_CHECKPOINT, tag)`.
    3.  Clears local queues.
- **Effect**: Subsequent reads will encounter this checkpoint event. When `read()` encounters it, it discards all events preceding it in that batch.

### Replay (`reset()`)
- Moves all items from `mSeenQueue` back to `mPendingQueue` to allow re-processing of the current session's logs.

## Data Model

### `Event` (Inner Class)
An intermediate wrapper around `EventLog.Event` to facilitate unit testing (decoupling from static Android APIs).
- `mTimeMillis`: Event timestamp (ms).
- `mPid`: Process ID.
- `mUid`: User ID.
- `mData`: The payload (Object or Object[]).

### State Variables
- `mPendingQueue`: `Queue<LogMaker>` - Logs waiting to be consumed.
- `mSeenQueue`: `Queue<LogMaker>` - Logs already consumed.
- `mCheckpointTag`: `int` - Current active checkpoint ID.
- `LOGTAGS`: `int[]` - List of log tags to subscribe to (defaults to `MetricsLogger.LOGTAG`).

## API Reference

### Public Methods
- **`read(long horizonMs)`**: Blocks until the log buffer wraps `horizonMs` (or returns immediately if 0). Populates queues.
- **`checkpoint()`**: Writes a marker to the log and clears local state.
- **`reset()`**: Rewinds the current session.
- **`hasNext()`**: Returns `true` if `mPendingQueue` is not empty.
- **`next()`**: Returns the next `LogMaker` and moves it to `mSeenQueue`.

### Test Support
- **`setLogReader(LogReader reader)`**: Inject a mock reader for testing.

## Java-to-C++ Translation Guide

### Dependencies
- **`EventLog`**: C++ will need to use the native Android logging reader API (`<log/log_read.h>` or `liblog`).
- **`MetricsLogger`**: The C++ implementation needs a way to write the checkpoint to the log.

### Queues
- **Java**: `LinkedList<LogMaker>`.
- **C++**: `std::deque` or `std::list` of `LogMaker` instances (or smart pointers `std::unique_ptr<LogMaker>`).

### Time Units
- **Java**: Uses `TimeUnit` conversions (Nanos to Millis).
- **C++**: Use `std::chrono` for precise time conversions.

### Concurrency
- The Java implementation doesn't appear explicitly thread-safe (uses standard `LinkedList`). If the C++ reader is intended for multi-threaded access, `std::mutex` protection for the queues is required.

## Implementation Risks
- **Blocking Behavior**: The `read(horizonMs)` method relies on `EventLog.readEventsOnWrapping`. Replicating this "block until overwritten" behavior in C++ might require interacting with specific `liblog` blocking read modes or polling.
- **Data Ownership**: When wrapping raw log data into `LogMaker`, ensure deep copies are made if the raw log buffer is transient.

## Questions for C++ Team
1.  **Blocking Read**: Does `liblog` expose the exact "wait until timestamp overwritten" semantic used in `readEventsOnWrapping`?
2.  **Checkpointing**: Is writing a log event purely for synchronization acceptable in the native layer, or is there a lighter-weight synchronization mechanism available?
