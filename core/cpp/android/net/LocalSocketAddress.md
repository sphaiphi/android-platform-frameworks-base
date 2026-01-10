# LocalSocketAddress.java - Reverse Engineering Documentation

## Executive Summary
`LocalSocketAddress` encapsulates the address of a UNIX-domain socket. It defines the name and the namespace (Abstract, Reserved, Filesystem).

## Architecture Overview
- **Type**: Data Class
- **Package**: `android.net`
- **Enums**: `Namespace` (ABSTRACT, RESERVED, FILESYSTEM).

## Detailed Functionality

### Namespaces
1.  **ABSTRACT** (0): Linux abstract namespace. The name is not on the filesystem. In `sockaddr_un`, the first byte of `sun_path` is `\0`.
2.  **RESERVED** (1): Android reserved namespace (`/dev/socket/`). Only `init` creates these.
3.  **FILESYSTEM** (2): Normal filesystem path.

### Data
-   `name`: String identifier.
-   `namespace`: The `Namespace` enum.

## Java-to-C++ Translation Guide

### Mapping
-   **ABSTRACT**: Prepend `\0` to `name`. `sun_path` length includes the null byte.
-   **RESERVED**: Typically maps to paths in `/dev/socket/`.
-   **FILESYSTEM**: Direct path mapping.

### C++ Usage
When populating `struct sockaddr_un`:
```cpp
struct sockaddr_un addr;
addr.sun_family = AF_UNIX;
if (namespace == ABSTRACT) {
    addr.sun_path[0] = '\0';
    strncpy(addr.sun_path + 1, name.c_str(), sizeof(addr.sun_path) - 2);
    // len calculation is specific for abstract
} else {
    strncpy(addr.sun_path, name.c_str(), sizeof(addr.sun_path) - 1);
}
```
