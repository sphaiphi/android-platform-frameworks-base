# SyncFence - Reverse Engineering Documentation

## Executive Summary
`SyncFence` represents a hardware synchronization primitive. It signals when a specific task submitted to a hardware unit (like the GPU or Display) has completed. It is a critical component for zero-copy buffer sharing and high-performance graphics.

## Architecture Overview
`SyncFence` is a Java wrapper around the Linux `dma-buf` sync file mechanism. It is `AutoCloseable` and `Parcelable`. It can be associated with an `Image` or `HardwareBuffer`.

## Detailed Functionality

### Signal States
- **Unsignaled**: Initial state.
- **Signaled**: Task completed successfully.
- **Error**: Task failed.

### Operations
- `isValid()`: Checks if the fence is associated with a valid open sync file.
- `await(Duration)`: Blocks the calling thread until the fence signals or the timeout expires.
- `getSignalTime()`: Returns the timestamp (nanoseconds, `CLOCK_MONOTONIC`) when the fence signaled.
- `SIGNAL_TIME_PENDING`: Indicates the fence hasn't signaled yet (`Long.MAX_VALUE`).

### Lifecycle
- `close()`: Releases the underlying file descriptor.
- `NativeAllocationRegistry`: Ensures the native `libui` Fence object is destroyed.

## Data Model
- `mNativePtr`: Native pointer to `android::Fence` (from `libui`).

## API Reference
- `public boolean await(Duration timeout)`
- `public long getSignalTime()`
- `public void close()`

## Java-to-C++ Translation Guide
- **Native Object**: Maps directly to `android::Fence`.
- **Parceling**: Uses `writeFileDescriptor`. C++ uses `Fence::flatten`.
- **Timing**: Use `clock_gettime(CLOCK_MONOTONIC, ...)` comparison.

## Implementation Risks
- Thread safety: While the Java class adds some locking, the underlying sync file operations are generally thread-safe at the kernel level.
- Deadlocks: Waiting on a fence that will never signal (though the documentation states fences always make forward progress).
