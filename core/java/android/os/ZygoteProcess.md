# ZygoteProcess - Reverse Engineering Documentation

## Executive Summary
`ZygoteProcess` manages the connection to the Zygote daemon (via local socket) to fork new application processes. It handles the protocol for sending arguments (UID, GID, nice name, classpath) and reading the resulting PID.

## Architecture Overview
-   **Role**: App Launcher Client.
-   **Communication**: `LocalSocket` (UNIX domain socket).
-   **Endpoints**:
    -   `zygote` (Primary, 64-bit usually).
    -   `zygote_secondary` (32-bit usually).
    -   `usap_pool` (Unspecialized App Process Pool - optimization).

## Detailed Functionality
-   **`start(...)`**: Main entry point.
    1.  Constructs argument list (`--setuid`, `--setgid`, `--runtime-args`, class name).
    2.  Selects primary or secondary zygote based on ABI.
    3.  Connects (if not connected) to `@zygote` socket.
    4.  Sends arguments.
    5.  Reads PID from socket.
-   **USAP**: Supports "Unspecialized App Process" pool, where processes are pre-forked and waiting to be specialized (renamed, perms dropped).

## Java-to-C++ Translation Guide
-   **Equivalent**: `AppZygote` in native code doesn't strictly exist as a generic class, but `frameworks/base/cmds/app_process` implements the Zygote itself.
-   **Protocol**: The socket protocol is text-based (newline separated arguments). C++ clients (like `system_server` native parts) would need to implement this text protocol to spawn processes via Zygote.

## Implementation Risks
-   **Blocking**: Socket I/O is blocking. Zygote is single-threaded in its accept loop.
-   **Security**: The socket is restricted. Only `system_server` (and root) can talk to Zygote.
