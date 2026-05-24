# ProfilerInfo - Reverse Engineering Documentation

## Executive Summary
`ProfilerInfo` is a system-private data class used to pass profiling settings from the `ActivityManager` to a target application process. it specifies parameters for method tracing, sampling, and agent attachment (e.g., JVMTI agents). It is used to initiate profiling during app startup or while the app is already running.

## Architecture Overview
- **Structure**:
    - `profileFile`: String path to the output trace file.
    - `profileFd`: `ParcelFileDescriptor` for the output file (optional).
    - `samplingInterval`: Microseconds between samples (for sampling-based profiling).
    - `autoStopProfiler`: Flag to stop profiling when the app goes idle.
    - `streamingOutput`: Flag to stream data continuously instead of buffering.
    - `agent`: Parameters for attaching a profiling agent.
    - `attachAgentDuringBind`: Flag to control agent attachment timing (early vs. late).
    - `clockType`: Source of timestamps (`WALL`, `THREAD_CPU`, `DUAL`).
- **Inheritance**: Implements `Parcelable`.

## Detailed Functionality

### Clock Type Mapping
**Purpose**: Translates string-based user input into integer flags for the ART (Android Runtime) profiler.
**Mechanism**: `getClockTypeFromString(String type)` maps inputs like "thread-cpu" or "wall" to the corresponding `CLOCK_TYPE_...` constants.

### Agent Attachment
**Purpose**: Enables low-level profiling and instrumentation via external libraries.
**Logic**: If `attachAgentDuringBind` is true, the agent is loaded during the application binding phase, allowing it to see early setup. Otherwise, it is attached prior to binding.

### File Management
**Purpose**: Manages the lifecycle of the trace file.
**Logic**: Includes a `closeFd()` method to safely release the `ParcelFileDescriptor` once the settings have been passed to the target process.

## API Reference
- `public void closeFd()`: Releases the file resource.
- `public static int getClockTypeFromString(String type)`: Utility for parsing clock settings.
- `public ProfilerInfo setAgent(String agent, boolean attachAgentDuringBind)`: Returns a new instance with updated agent settings.

## Java-to-C++ Translation Guide
- **ART Integration**: The flags in `ProfilerInfo` map directly to `art::TraceFlag` and `art::runtime_globals.h` constants in the Android source.
- **File Descriptors**: Map `ParcelFileDescriptor` to a native file descriptor integer (`int fd`).
- **JNI Bridge**: The profiling commands are typically executed via `android.os.VMDebug` methods, which are native hooks into the ART profiler.

## Implementation Risks
- **File Permissions**: The output path (`profileFile`) must be writable by the application process. C++ implementation must ensure SELinux labels and UNIX permissions are correct.
- **Resource Leaks**: Failing to call `closeFd()` in the system server after passing the object to an app can lead to file descriptor exhaustion.
- **Performance**: High sampling intervals or dual-clock tracing can significantly impact app performance and increase the size of trace files.
