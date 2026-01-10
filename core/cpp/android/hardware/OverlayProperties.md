# OverlayProperties - Reverse Engineering Documentation

## Executive Summary
`OverlayProperties` provides information about the supported hardware overlay capabilities of the device. Hardware overlays allow the system to composite buffers directly to the screen using display hardware instead of the GPU, which is more power-efficient.

## Architecture Overview
The class interfaces with the native display system via JNI. It uses `NativeAllocationRegistry` for lifecycle management. It can be used to check if specific combinations of `DataSpace` and `HardwareBuffer.Format` are supported for hardware composition.

## Detailed Functionality

### Capability Checks
- `isCombinationSupported(dataspace, format)`: Checks if the hardware can efficiently composite a buffer with the given color space and pixel format.
- `isMixedColorSpacesSupported()`: Checks if the hardware can composite multiple overlays with different color spaces simultaneously.

### LUT Properties
- `getLutProperties()`: Retrieves an array of `LutProperties` describing the device's LUT capabilities.

### Virtual Displays
- `getDefault()`: Provides a default set of properties for virtual displays (typically supporting RGBA_8888, sRGB, and mixed color spaces).

## Data Model
- `mNativeObject`: Native pointer to the underlying C++ property structure.
- `mLutProperties`: Cached array of LUT property objects.

## API Reference
- `public static OverlayProperties getDefault()`
- `public LutProperties[] getLutProperties()`
- `public boolean isCombinationSupported(int dataspace, int format)`
- `public boolean isMixedColorSpacesSupported()`

## Java-to-C++ Translation Guide
- **Native State**: `mNativeObject` maps to a C++ object that likely queries the `SurfaceFlinger` or `Composer` service.
- **Lifecycle**: Ensure the native destructor is correctly registered with the C++ wrapper.

## Implementation Risks
- The properties returned might change if external displays are connected/disconnected.
- Over-reliance on hardware overlays by apps can lead to GPU fallbacks if overlay limits are exceeded.
