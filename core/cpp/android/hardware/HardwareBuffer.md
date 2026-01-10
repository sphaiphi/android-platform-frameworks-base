# HardwareBuffer - Reverse Engineering Documentation

## Executive Summary
`HardwareBuffer` is a Java wrapper around the native `AHardwareBuffer` object. it represents a low-level memory buffer that can be accessed by various hardware units, such as the GPU, camera, or sensors. It allows for efficient buffer sharing across different application processes and hardware subsystems.

## Architecture Overview
`HardwareBuffer` implements `Parcelable` and `AutoCloseable`. It holds a native pointer (`mNativeObject`) to the underlying C++ `AHardwareBuffer`. It uses `NativeAllocationRegistry` for automated lifecycle management and `CloseGuard` to detect resource leaks.

## Detailed Functionality

### Buffer Creation
- `create(width, height, format, layers, usage)`: Allocates a new hardware buffer with specified dimensions, pixel format, and usage flags.
- `nCreateHardwareBuffer`: Native JNI call to allocate the memory.

### Usage Flags
Usage flags indicate how the buffer will be accessed (e.g., `USAGE_CPU_READ_OFTEN`, `USAGE_GPU_SAMPLED_IMAGE`, `USAGE_SENSOR_DIRECT_DATA`). These flags help the system determine the optimal memory type and alignment.

### Lifecycle Management
- `close()`: Explicitly releases the native buffer resources.
- `finalize()`: Fallback to ensure resources are freed if `close()` wasn't called.
- `NativeAllocationRegistry`: Registers the native allocation to be freed when the Java object is garbage collected.

### Parceling
- `writeToParcel`: Writes the native file descriptor and metadata into a parcel.
- `createFromParcel`: Reconstructs the `HardwareBuffer` from a parcel, allowing cross-process buffer sharing.

## Data Model
- **Format (int)**: `RGBA_8888`, `RGBA_FP16`, `BLOB`, `YCBCR_420_888`, `D_24`, etc.
- **Usage (long)**: Bitmask of flags like `USAGE_CPU_READ_RARELY`, `USAGE_GPU_COLOR_OUTPUT`, etc.

## API Reference
- `public static HardwareBuffer create(...)`
- `public int getWidth()`, `public int getHeight()`, `public int getFormat()`
- `public long getUsage()`, `public int getLayers()`
- `public void close()`
- `public boolean isClosed()`

## Java-to-C++ Translation Guide
- **Native Handle**: `mNativeObject` (long) should map directly to `AHardwareBuffer*`.
- **Memory Management**: Use `AHardwareBuffer_acquire()` and `AHardwareBuffer_release()` for reference counting.
- **JNI Optimization**: Methods like `nGetWidth`, `nGetHeight` are marked with `@FastNative` or `@CriticalNative` for performance. C++ implementations should respect these calling conventions.

## Implementation Risks
- Memory leaks if `close()` is not called and GC is delayed.
- Platform-specific support: Not all combinations of formats and usage flags are supported on all hardware. `isSupported()` should be used to verify.
- Direct memory access (DMA) mapping complexities.
