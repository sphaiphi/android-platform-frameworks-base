# ViewDebug - Reverse Engineering Documentation

## Executive Summary
`ViewDebug` is a comprehensive suite of debugging and tracing tools for the Android View hierarchy. it provides functionality for counting view instances, capturing view layers as bitmaps, profiling layout/measure/draw passes, and remotely invoking methods on views for inspection.

## Architecture Overview
*   **Role**: UI diagnostic toolkit.
*   **Interfaces**: Includes `HierarchyHandler` for views that manage their own internal trees (like `WebView`).
*   **Annotations**: Uses `@ExportedProperty` and `@CapturedViewProperty` to mark fields/methods that should be visible to debugger tools.

## Detailed Functionality

### 1. Introspection
*   **`getViewInstanceCount()`**: Returns the total number of `View` objects alive in the process.
*   **`dumpv2()`**: Exports the entire view tree to a binary `ViewHierarchyEncoder` stream.

### 2. Capturing
*   **`capture()`** / **`captureLayers()`**: Renders a view or its entire subtree into a PNG stream for remote inspection.
*   **`startRenderingCommandsCapture()`**: Streams a sequence of `Picture` objects (SKP) representing the raw GPU commands for a window.

### 3. Profiling
*   **`profileViewOperation()`**: Measures the CPU time spent in measure, layout, and draw for a specific view.

### 4. Remote Control
*   **`invokeViewMethod()`**: Allows a debugger to call a Java method on a view instance via reflection.

## Java-to-C++ Translation Guide
*   **Reflection**: In C++, this requires a manual property registry or a specialized metadata system.
*   **Rendering Capture**: Uses `android::uirenderer::HardwareRenderer` callbacks to intercept the frame pipeline.

## Implementation Risks
*   **Performance**: Most methods in this class are extremely heavy and should only be used in non-production builds.
*   **Security**: `invokeViewMethod` is a powerful tool that must be strictly guarded to prevent arbitrary code execution via compromised debugger connections.
