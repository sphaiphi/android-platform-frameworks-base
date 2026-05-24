# LocalSocket.java - Reverse Engineering Documentation

## Executive Summary
`LocalSocket` represents a client-side or connected UNIX-domain socket (AF_LOCAL/AF_UNIX). It supports stream (TCP-like), datagram (UDP-like), and sequential packet modes. It provides input/output streams and file descriptor passing (ancillary data) capabilities.

## Architecture Overview
- **Type**: Class
- **Package**: `android.net`
- **Implements**: `Closeable`
- **Key Dependencies**: `LocalSocketImpl`, `LocalSocketAddress`, `Credentials`.

## Detailed Functionality

### Socket Types
-   `SOCKET_STREAM` (2): `SOCK_STREAM`
-   `SOCKET_DGRAM` (1): `SOCK_DGRAM`
-   `SOCKET_SEQPACKET` (3): `SOCK_SEQPACKET`

### Lifecycle
1.  **Creation**: Can be created fresh or from an existing `FileDescriptor`.
2.  **Connection**: `connect(LocalSocketAddress)` binds the socket (if not anonymous) and connects to the endpoint.
3.  **I/O**: `getInputStream()` and `getOutputStream()` allow read/write operations.
4.  **Ancillary Data**:
    -   `setFileDescriptorsForSend(FileDescriptor[])`: Queues FDs to be sent with the next write.
    -   `getAncillaryFileDescriptors()`: Retrieves FDs received in the last read.
5.  **Credentials**: `getPeerCredentials()` retrieves PID/UID/GID of the peer (`SO_PEERCRED`).

### File Descriptor Passing
This is a critical feature. On Linux AF_UNIX sockets, `SCM_RIGHTS` messages allow passing file descriptors between processes. `LocalSocket` exposes this via specific methods attached to the socket, synchronized with the byte stream.

## Java-to-C++ Translation Guide

### Core Mapping
-   `connect()` -> `connect(fd, sockaddr*, len)`
-   `bind()` -> `bind(fd, sockaddr*, len)`
-   `getInputStream/OutputStream` -> `read/write` or `recvmsg/sendmsg`.

### Ancillary Data
Implementing `setFileDescriptorsForSend` in C++ requires constructing `msghdr` with `cmsghdr` for `SCM_RIGHTS`.
-   **Java**: `socket.setFileDescriptorsForSend(fds); socket.getOutputStream().write(data);`
-   **C++**: `sendmsg` with both data `iov` and control buffer containing FDs.

### Safety
-   Java manages the lifecycle of `FileDescriptor` objects. C++ implementation must handle `dup` or ownership transfer carefully to avoid leaks or double-closes.

## Usage
Extensively used in Android for efficient IPC, especially when large data or FDs (like shared memory or hardware buffers) need to be transferred.
