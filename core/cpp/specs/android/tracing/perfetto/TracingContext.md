# TracingContext - Reverse Engineering Documentation

## Executive Summary
The context object provided to the tracing function. It allows creation of new trace packets and access to custom state (TLS and Incremental).

## Data Model
*   **`mDataSource`**: Reference to the parent DataSource.
*   **`mInstanceIndex`**: Index of the current instance.
*   **`mTracePackets`**: List of `ProtoOutputStream` objects representing packets written during this trace call.

## API Reference
*   **`newTracePacket()`**: Returns a `ProtoOutputStream` for writing a new trace packet.
*   **`getCustomTlsState()`**: Accessor for custom Thread Local State. Creates it if null via the DataSource.
*   **`getIncrementalState()`**: Accessor for custom Incremental State. Creates it if null via the DataSource.
*   **`getAndClearAllPendingTracePackets()`**: Helper to retrieve encoded packets for native writing.

## Java-to-C++ Translation Guide
*   **Perfetto Concept**: Maps to `perfetto::DataSource::TraceContext`.
*   **Trace Packets**: In Java, `ProtoOutputStream` is used. In C++, `ctx.NewTracePacket()` returns a protobufzero object.
