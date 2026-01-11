# StackTrace - Reverse Engineering Documentation

## Executive Summary
`StackTrace` is an internal helper class that extends `Exception`. It is explicitly designed not to be thrown as a fatal error, but rather to be used as a container for capturing and logging current stack traces. This is particularly useful for diagnostic purposes, such as tracking where a specific API was called (e.g., `startForegroundService`) to provide context in case of a later failure.

## Architecture Overview
- **Inheritance**: Extends `Exception`.
- **Visibility**: Marked as `@hide`, intended for internal framework use only.

## Detailed Functionality

### Usage Pattern
**Purpose**: Capturing call history.
**Logic**: Instantiated at a specific point in code to capture the snapshot of the execution stack. It is then stored (e.g., in `Service.sStartForegroundServiceStackTraces`) and attached as a "cause" to future exceptions or logged for debugging.

### Constructors
- `StackTrace(String message)`: Creates a trace with a custom label.
- `StackTrace(String message, Throwable innerStackTrace)`: Allows nesting traces to show a chain of events.

## API Reference
- `public StackTrace(String message)`: Public (hidden) constructor.

## Java-to-C++ Translation Guide
- **Trace Capture**: Use the NDK `<android/log.h>` and `<unwind.h>` or the native `android::CallStack` class to capture backtraces in C++.
- **Exception Mapping**: Map to a C++ class that stores a `std::vector<void*>` of instruction pointers.

## Implementation Risks
- **Performance**: Frequent stack trace capture is expensive. C++ implementation should be mindful of the overhead, especially in performance-critical sections of the framework.
- **Symbolication**: Captured instruction pointers must be symbolized (mapped to function names) either at capture time or during logging, which requires access to the system's ELF symbols.
