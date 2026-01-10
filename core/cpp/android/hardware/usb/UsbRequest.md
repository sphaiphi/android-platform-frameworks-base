# UsbRequest.java - Reverse Engineering Documentation

## Executive Summary
`UsbRequest` represents an asynchronous USB transfer request (URB). It is used to send or receive data on Bulk and Interrupt endpoints. It wraps the native `usb_request` structure and provides a mechanism to queue requests and wait for their completion via `UsbDeviceConnection`.

## Architecture Overview
- **Type**: IO / wrapper class
- **Package**: `android.hardware.usb`
- **Dependencies**: 
  - `UsbDeviceConnection`: The context.
  - `UsbEndpoint`: The target.
  - `ByteBuffer`: Data buffer.

## Detailed Functionality

### Lifecycle
1.  **Initialize**: `initialize(UsbDeviceConnection, UsbEndpoint)`. allocating native resources (`native_init`).
2.  **Queue**: `queue(ByteBuffer, int)` (Deprecated) or `queue(ByteBuffer)`. Submits the request to the kernel.
3.  **Wait**: `UsbDeviceConnection.requestWait()` returns the `UsbRequest` when complete.
4.  **Dequeue**: `dequeue()`. Updates the buffer position based on bytes transferred.
5.  **Close**: `close()`. Frees native resources.

### Buffer Handling
- Supports both **Direct ByteBuffers** and **Heap ByteBuffers** (Arrays).
- **Direct**: Passed directly to native code (`native_queue_direct`).
- **Heap**:
  - If SDK < P: Copies data to a temporary direct buffer if needed? No, logic handles array locking in JNI.
  - Logic in `queueIfConnectionOpen`:
    - If buffer is read-only and receiving: Throw exception.
    - If buffer is not direct: Allocates a temporary direct buffer `mTempBuffer`, copies data (if send), queues the temp buffer.
- **Dequeue**: Copies data back from `mTempBuffer` to the original heap buffer if necessary.

### Native State
- `mNativeContext`: Pointer to the native `usb_request` struct.
- `MAX_USBFS_BUFFER_SIZE`: 16KB limit for legacy compatibility (SDK < P).

## Data Model
- `mBuffer`: Reference to current buffer.
- `mLength`: Length of transfer.
- `mClientData`: User object attached to request.
- `mIsUsingNewQueue`: Flag to track which queue method was called (affects dequeue logic).

## Java-to-C++ Translation Guide

### Native Wrapper
This class corresponds to `struct usb_request` in `libusbhost`.
- `native_init`: `usb_request_new`
- `native_close`: `usb_request_free`
- `native_queue`: `usb_request_queue`
- `native_cancel`: `usb_request_cancel`

### Async Model
In C++, this maps to submitting an async IO request.
- The `queue` method submits.
- The `requestWait` on the *Connection* reaps.

### Buffer Management
Java handles the complexity of Direct vs Heap buffers. In C++, you typically provide a raw pointer (`void*`) and length.
- **Suggestion**: The C++ API should likely take `std::span<uint8_t>` or `void*` + size.

### Locking
`mLock` synchronizes queue/dequeue/close.

## Implementation Risks
- **Double Free**: Ensure `close` handles the native pointer safely.
- **Buffer Lifetime**: In C++, the caller must ensure the data buffer remains valid until the request completes (Reaped). Java ensures this by holding a reference to `mBuffer`. C++ API needs to document this ownership requirement clearly.
