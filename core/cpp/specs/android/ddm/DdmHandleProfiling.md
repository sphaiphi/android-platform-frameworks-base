# DdmHandleProfiling - Reverse Engineering Documentation

## Executive Summary
`DdmHandleProfiling` manages method tracing and sampling profiling requests from DDM. It interfaces with `android.os.Debug` to start/stop tracing and configure streaming output.

## Architecture Overview
- **Inheritance**: Extends `DdmHandle`.
- **Registration**:
    - `MPRS`: Method Profiling Start
    - `MPRE`: Method Profiling End
    - `MPSS`: Method Profiling Streaming Start
    - `MPSE`: Method Profiling Streaming End
    - `MPRQ`: Method Profiling Query
    - `SPSS`: Sample Profiling Streaming Start
    - `SPSE`: Sample Profiling Streaming End

## Detailed Functionality

### `handleMPRS` (Start File Tracing)
- **Input**: buffer size (int), flags (int), filename len (int), filename (string).
- **Action**: Calls `Debug.startMethodTracing`.
- **Response**: None (if successful) or Fail chunk.

### `handleMPRE` (Stop Tracing)
- **Input**: None.
- **Action**: Calls `Debug.stopMethodTracing`.
- **Response**: Byte 0 on success, 1 on failure.

### `handleMPSS` (Start Stream Tracing)
- **Input**: buffer size (int), flags (int).
- **Action**: Calls `Debug.startMethodTracingDdms` (streaming mode).

### `handleSPSS` (Start Sample Profiling)
- **Input**: buffer size (int), flags (int), interval (int).
- **Action**: Calls `Debug.startMethodTracingDdms` with `samplingEnabled=true` and specified interval.

### `handleMPRQ` (Query Status)
- **Action**: Checks `Debug.getMethodTracingMode()`.
- **Response**: Single byte containing the status.

## Java-to-C++ Translation Guide
- **Profiling Backend**: The core logic resides in `android.os.Debug` (likely bridging to ART internals). The C++ DDM handler should interact directly with the runtime's profiling API.
- **Streaming**: "MPSS" implies the trace data is sent back over the DDM connection (or a separate socket) rather than to a file.

## Data Structures
Request formats follow the standard `int` + `string` pattern.
