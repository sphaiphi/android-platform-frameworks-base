# DisplayManagerInternal - Reverse Engineering Documentation

## Executive Summary
`DisplayManagerInternal` is an abstract class defining the local system service interface for DisplayManager. It is exposed only within the system server process (to WindowManager, PowerManager, etc.).

## Architecture Overview
- **Scope**: System Server Internal.
- **Purpose**: Low-latency, trusted, intra-process communication between system services.

## Detailed Functionality
- **Power Management**: `initPowerManagement`, `requestPowerState` (controls screen on/off/doze).
- **Window Management Integration**:
    - `setDisplayInfoOverrideFromWindowManager`: WM tells DM about display size/logical changes.
    - `setDisplayProperties`: WM tells DM about content requirements (HDR, Refresh Rate).
    - `performTraversal`: Transaction synchronization with SurfaceFlinger.
- **Virtual Displays**: `createVirtualDisplay` (internal variant for VirtualDeviceManager).
- **Direct Access**: `getDisplayInfo`, `getDisplayPosition`, `systemScreenshot`.

## Java-to-C++ Translation Guide
- This is a Java-only internal interface.
- Equivalent concepts in C++ (if accessing from native system services) would be direct calls or internal framework headers, not exposed via NDK.
