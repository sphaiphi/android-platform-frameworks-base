# DeviceStateManagerInternal - Reverse Engineering Documentation

## Executive Summary
`DeviceStateManagerInternal` is an abstract class defining the local system service interface for `DeviceStateManager`. It allows other system server components (internal to the system process) to query device state information without going through Binder IPC.

## Architecture Overview
- **Scope**: Local Service (System Server internal).
- **Function**: Exposes low-level state data to other services (like WindowManager).

## Detailed Functionality
- `getSupportedStateIdentifiers()`: Returns `int[]`.

## Java-to-C++ Translation Guide
- This is likely part of the **System Server** implementation details.
- In C++, if this service exists in the native layer, it would be a plain C++ interface (pure virtual class) used for dependency injection or local service registries.
