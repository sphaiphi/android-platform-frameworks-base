# ApplicationExitInfo - Reverse Engineering Documentation

## Executive Summary
`ApplicationExitInfo` describes the reason and state of an application process's death. It provides detailed diagnostic information such as the exit reason (crash, ANR, lmk), status code, importance at death, PSS/RSS memory usage, and access to trace files (tombstones).

## Architecture Overview
*   **Type**: Parcelable Data Class.
*   **Features**:
    *   Protobuf serialization (`writeToProto`, `readFromProto`).
    *   Trace file retrieval (`IAppTraceRetriever`, `IParcelFileDescriptorRetriever`).

## Detailed Functionality

### Exit Reasons
*   Defines constants: `REASON_EXIT_SELF`, `REASON_SIGNALED`, `REASON_LOW_MEMORY`, `REASON_CRASH`, `REASON_ANR`, etc.
*   Sub-reasons for finer granularity (e.g., `SUBREASON_WAIT_FOR_DEBUGGER`, `SUBREASON_TOO_MANY_CACHED`).

### Data Fields
*   `pid`, `realUid`, `packageUid`, `definingUid`.
*   `processName`, `packageName`.
*   `timestamp`.
*   `importance` (process state).
*   `pss`, `rss` (memory).
*   `description` (human readable).
*   `state` (custom state blob).

### Trace Retrieval
*   `getTraceInputStream()`: Retrieves the trace via binder calls to `mAppTraceRetriever` or `mNativeTombstoneRetriever`. Handles GZIP decompression.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard mapping.
*   **Protobuf**: Maps to `ApplicationExitInfoProto` definition.
*   **Binder Interfaces**: Requires C++ proxies for `IAppTraceRetriever` etc.

## Implementation Risks
*   **Binder Latency**: Trace retrieval involves IPC and file descriptor transfer.
*   **File Handling**: Handling `ParcelFileDescriptor` ownership and streams.
