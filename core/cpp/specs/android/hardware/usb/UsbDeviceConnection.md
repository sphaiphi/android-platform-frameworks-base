# UsbDeviceConnection.java - Reverse Engineering Documentation

## Executive Summary
`UsbDeviceConnection` allows sending and receiving data to/from a `UsbDevice`. It is the handle to an open USB device file descriptor. It wraps synchronous and asynchronous IO operations (Control, Bulk) and manages Interface claiming.

## Architecture Overview
- **Type**: IO / wrapper class
- **Package**: `android.hardware.usb`
- **Dependencies**: 
  - `UsbDevice`: The target device.
  - `UsbRequest`: For asynchronous operations.
  - `Context`: For permission/target SDK checks.
  - `CloseGuard`: Leak detection.

## Detailed Functionality

### Lifecycle
1.  **Open**: `open(String name, ParcelFileDescriptor pfd, Context context)`. Called by `UsbManager`. Stores the file descriptor and context.
2.  **Usage**: IO transfers.
3.  **Close**: `close()`. Closes the native file descriptor.

### IO Methods
-   **Control Transfer**: `controlTransfer(...)`. Synchronous. Wraps `native_control_request`.
-   **Bulk Transfer**: `bulkTransfer(...)`. Synchronous. Wraps `native_bulk_request`.
-   **Request Wait**: `requestWait()`. Waits for an asynchronous `UsbRequest` to complete. Wraps `native_request_wait`.

### Configuration Management
-   `claimInterface(UsbInterface, boolean force)`
-   `releaseInterface(UsbInterface)`
-   `setInterface(UsbInterface)` (Alternate setting)
-   `setConfiguration(UsbConfiguration)`

### Raw Access
-   `getFileDescriptor()`: Returns the integer FD.
-   `getRawDescriptors()`: Returns the raw byte array of USB descriptors.

## C++ Implementation Guidance

### Native Mapping
This class is a thin wrapper around JNI calls. The underlying implementation likely uses `libusbhost` (Android specific) or standard Linux `usbdev` ioctls (`USBDEVFS_CONTROL`, `USBDEVFS_BULK`, `USBDEVFS_CLAIMINTERFACE`, etc.).

### Key Native Functions to Implement/Wrap
-   `native_open`: `open(path, O_RDWR)`
-   `native_close`: `close(fd)`
-   `native_control_request`: `ioctl(fd, USBDEVFS_CONTROL, ...)`
-   `native_bulk_request`: `ioctl(fd, USBDEVFS_BULK, ...)`
-   `native_claim_interface`: `ioctl(fd, USBDEVFS_CLAIMINTERFACE, ...)`
-   `native_request_wait`: `ioctl(fd, USBDEVFS_REAPURB, ...)` (Standard Linux AIO for USB).

### Locking
-   `mLock`: Used to synchronize `close()` against `queueRequest` and `cancelRequest` to prevent use-after-close race conditions.
-   **Translation Note**: C++ implementation must ensure thread safety when closing the FD while other threads might be submitting URBs.

### Buffer Bounds Checking
Java performs strict bounds checking (`checkBounds`) on byte arrays before passing to native. C++ should emulate this if wrapping safe containers (e.g., `std::span` or `std::vector`), or rely on size parameters if using raw pointers.

## Async Architecture (UsbRequest interaction)
The connection acts as the factory/context for `UsbRequest`.
- `queueRequest`: Called by `UsbRequest` to submit a URB.
- `requestWait`: Blocks until *any* URB on this FD completes.

## Edge Cases
- **Buffer Truncation**: For SDK < P, bulk transfer lengths > 16KB are truncated. For SDK >= P, they are allowed (likely split by kernel or supported by newer kernels).
- **Zero Length Packets**: Supported.
