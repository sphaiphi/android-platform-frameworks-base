# DdmRegister - Reverse Engineering Documentation

## Executive Summary
`DdmRegister` is a utility class responsible for registering all the standard DDM chunk handlers defined in the `android.ddm` package. It acts as the initialization entry point for DDM support in the framework.

## Architecture Overview
- **Pattern**: Registry / Facade.
- **Usage**: Called by the application framework (typically during startup, e.g., in `ActivityThread` or `RuntimeInit`) to enable DDM support.

## Detailed Functionality

### `registerHandlers`
**Purpose**: Registers all specific handlers and notifies the DDM server that registration is complete.
**Algorithm**:
1.  Calls `register()` on:
    - `DdmHandleHello`
    - `DdmHandleHeap`
    - `DdmHandleNativeHeap`
    - `DdmHandleProfiling`
    - `DdmHandleExit`
    - `DdmHandleViewDebug`
2.  Calls `DdmServer.registrationComplete()`: This signals the Chunk Dispatcher that it can stop buffering packets and start processing them.

## Java-to-C++ Translation Guide
- **Initialization**: This function corresponds to an `Init()` or `RegisterAll()` function in the C++ DDM subsystem.
- **Timing**: The `registrationComplete` signal is crucial to avoid race conditions where the debugger sends packets before handlers are ready.

## API Reference
| Method | Description |
|--------|-------------|
| `registerHandlers()` | Registers all core DDM handlers. |
