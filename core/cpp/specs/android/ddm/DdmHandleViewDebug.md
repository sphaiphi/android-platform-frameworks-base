# DdmHandleViewDebug - Reverse Engineering Documentation

## Executive Summary
`DdmHandleViewDebug` facilitates remote debugging of the Android View system. It handles requests to list windows, dump view hierarchies, capture view screenshots, profile view performance, and invoke methods on Views via reflection.

## Architecture Overview
- **Inheritance**: Extends `DdmHandle`.
- **Dependencies**: `ViewDebug`, `WindowManagerGlobal`, `ViewRootImpl`.
- **Registration**:
    - `VULW` (`0x56554C57`): View List Windows
    - `VURT` (`0x56555254`): View Root Operations
    - `VUOP` (`0x56554F50`): View Operations

## Detailed Functionality

### `listWindows` (VULW)
**Purpose**: Lists all active window names in the process.
**Response Format**:
```
[4 bytes] Count (N)
For i = 0 to N-1:
    [4 bytes] Name Length
    [Name Len * 2 bytes] Window Name
```

### `VURT` Operations
1.  **Parse Root View**: Reads root view name from input.
2.  **Dispatch**:
    - `DUMP_HIERARCHY` (1): dumps view tree.
    - `CAPTURE_LAYERS` (2): captures layer details.
    - `DUMP_THEME` (3): dumps theme attributes.

### `VUOP` Operations
1.  **Parse Root & Target View**: Reads root name, then target view name. Finds target view object.
2.  **Dispatch**:
    - `CAPTURE_VIEW` (1): Captures bitmap of specific view.
    - `DUMP_DISPLAYLIST` (2): Outputs hardware display list.
    - `PROFILE_VIEW` (3): Profiles view draw performance.
    - `INVOKE_VIEW_METHOD` (4): Calls arbitrary method.
    - `SET_LAYOUT_PARAMETER` (5): Modifies layout params.

### `invokeViewMethod`
**Purpose**: Reflection-based method invocation via DDM.
**Input Format**:
```
[4 bytes] Method Name Length
[L * 2 bytes] Method Name
[4 bytes] Number of Args
For each Arg:
    [1 byte] Type Signature (I, Z, F, R for String, etc.)
    [Value] (Size depends on type)
```
**Return Value**: Serialized same as argument (Type + Value).
**Supported Types**:
- Array (`[`): Only `byte[]` supported.
- String (`R`): Special encoding (len as unsigned short, then UTF-8 bytes). **Note**: Different from `DdmHandle.getString`.

## Java-to-C++ Translation Guide

### View System Interaction
This class is tightly coupled to the Java UI toolkit (`android.view`).
- **C++ UI**: If the C++ framework has a UI layer, this handler needs to hook into that layer's object graph.
- **Reflection**: C++ lacks Java-style reflection. `INVOKE_VIEW_METHOD` would require a custom registry of invokable methods or a metadata system if dynamic invocation is needed.

### Serialization Differences
- **Strings in `invokeViewMethod`**: Uses a custom format (UTF-8, short length) compared to the standard DDM (UTF-16, int length). Be careful implementing the parser.

## Implementation Risks
- **Thread Safety**: View operations (like `dumpDisplayLists`) often post Runnables to the UI thread. The C++ handler must respect the UI thread threading model.
- **Security**: `invokeViewMethod` exposes the entire View API to the debugger. Ensure this is only enabled in debuggable builds.
