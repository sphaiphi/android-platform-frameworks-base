# HwParcel - Reverse Engineering Documentation

## Executive Summary
`HwParcel` is the container for HIDL transactions, analogous to `Parcel` for AIDL. It marshals data to be sent via `HwBinder`.

## Architecture Overview
-   **Role**: HIDL Serialization.
-   **Native Peer**: `hardware::Parcel`.
-   **Vectors**: Supports `writeStringVector`, `writeInt32Vector`, etc., which serialize as HIDL vectors (pointer + size).

## Detailed Functionality
-   **`writeInterfaceToken`**: Writes the interface descriptor string.
-   **`writeStrongBinder`**: Writes an `IHwBinder` object.
-   **`writeBuffer`**: Writes an `HwBlob`.
-   **`send()`**: Dispatches the parcel (used when it's a one-way interaction or reply?). *Correction*: `send()` is likely for sending the reply parcel.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::hardware::Parcel`.
-   **Difference**: `HwParcel` strictly follows HIDL serialization rules (vectors, strings as blobs), whereas `Parcel` uses a flatter, less structured format.

## Implementation Risks
-   **Lifecycle**: `release()` must be called to free native resources. `releaseTemporaryStorage()` can free buffers early.
