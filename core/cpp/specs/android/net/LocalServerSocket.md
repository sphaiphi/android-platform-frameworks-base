# LocalServerSocket.java - Reverse Engineering Documentation

## Executive Summary
`LocalServerSocket` is a wrapper around `LocalSocketImpl` that creates an inbound UNIX-domain socket. On Android, it specifically defaults to the **Linux abstract namespace**, allowing sockets to be named without creating files on the filesystem.

## Architecture Overview
- **Type**: Class
- **Package**: `android.net`
- **Implements**: `Closeable`
- **Key Dependencies**: `LocalSocketImpl`, `LocalSocketAddress`.

## Detailed Functionality

### Construction
1.  **`LocalServerSocket(String name)`**:
    -   Creates a `LocalSocketImpl`.
    -   Creates a `SOCKET_STREAM` (TCP-like).
    -   Binds to `LocalSocketAddress` with `name` (Abstract namespace by default).
    -   Calls `listen` with backlog 50.
2.  **`LocalServerSocket(FileDescriptor fd)`**:
    -   Wraps an existing bound file descriptor.
    -   Calls `listen`.
    -   Retrieves the local address from the implementation.

### Operations
-   **`accept()`**: Blocks until a connection arrives. Returns a `LocalSocket` representing the client connection. Internally calls `impl.accept()`.
-   **`close()`**: Closes the underlying implementation.
-   **`getFileDescriptor()`**: Returns the `FileDescriptor`.

## Java-to-C++ Translation Guide
This maps directly to standard BSD socket API calls for AF_UNIX.

### Logic
```cpp
// Constructor equivalent
int fd = socket(AF_UNIX, SOCK_STREAM, 0);
struct sockaddr_un addr;
// Setup addr for Abstract Namespace (leading null byte)
// bind(fd, ...)
// listen(fd, 50)
```

### Abstract Namespace
In C++, abstract namespace addresses in `sockaddr_un.sun_path` start with a null byte `\0`. Java's `LocalSocketAddress` handles this translation.

## Usage
Used for IPC between processes on Android, commonly Zygote, system services, etc.
