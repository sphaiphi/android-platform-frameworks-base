# AsyncNotedAppOp - Reverse Engineering Documentation

## Executive Summary
`AsyncNotedAppOp` is a parcelable class representing an App Operation note event that occurred asynchronously (e.g., from native code or a separate process) and needs to be reported back to the application's `OnOpNotedCallback`.

## Architecture Overview
*   **Type**: Immutable Data Class.
*   **Usage**: Passed from system server to app client.

## Detailed Functionality
*   **Fields**:
    *   `mOpCode`: Integer op code.
    *   `mNotingUid`: UID that noted the op.
    *   `mAttributionTag`: Attribution tag string.
    *   `mMessage`: Message describing the access.
    *   `mTime`: Timestamp.
*   **Methods**: Getters, `equals`, `hashCode`, `toString`, Parcelable methods.

## Java-to-C++ Translation Guide
*   Standard Parcelable mapping.
*   Immutable struct.
