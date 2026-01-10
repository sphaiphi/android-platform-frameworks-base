# SerialPort - Reverse Engineering Documentation

## Executive Summary
`SerialPort` represents an open serial communication link. It provides low-level methods to read from and write to the serial hardware using byte buffers.

## Architecture Overview
This class encapsulates a `ParcelFileDescriptor` and uses JNI for raw IO operations. It is designed to be managed by `SerialManager`.

## Detailed Functionality

### Lifecycle
- `open(pfd, speed)`: Associates the port with a file descriptor and sets the baud rate via native code.
- `close()`: Closes the underlying file descriptor and native context.

### Data IO
- `read(ByteBuffer)`: Reads data into a buffer. Handles both direct and array-backed buffers.
- `write(ByteBuffer, length)`: Writes data from a buffer.
- `sendBreak()`: Sends a break signal (stream of zeroes) for a short duration.

## Data Model
- `mNativeContext` (int): Native handle for the serial device state.
- `mFileDescriptor`: The `ParcelFileDescriptor` associated with the open port.

## Java-to-C++ Translation Guide
- **Native State**: `mNativeContext` should map to a pointer to a C++ object that handles `termios` configuration.
- **IO**: Use standard POSIX `read()`, `write()`, and `tcsendbreak()`.
- **Buffers**: Map `ByteBuffer` to `void*` and `size_t`.

## Implementation Risks
- Blocked IO: Serial reads can block if no data is available. C++ code should handle timeouts or non-blocking modes correctly.
- Baud Rate Mapping: Translating integer speeds to `B9600`, `B115200`, etc., in `termios`.
