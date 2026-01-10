# Credentials.java - Reverse Engineering Documentation

## Executive Summary
`Credentials` is a value class representing UNIX credentials (PID, UID, GID) passed via ancillary data on UNIX domain sockets.

## Architecture Overview
- **Type**: Immutable Value Object
- **Package**: `android.net`
- **Usage**: Used by `LocalSocket` to retrieve peer credentials.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `pid` | `int` | Process ID of the peer. |
| `uid` | `int` | User ID of the peer. |
| `gid` | `int` | Group ID of the peer. |

## Java-to-C++ Translation Guide
This maps directly to `struct ucred` in Linux.

### C++ Definition
```cpp
struct Credentials {
    pid_t pid;
    uid_t uid;
    gid_t gid;
};
```

### Notes
- "root peers may lie" comment suggests caution when trusting these values, though kernel-provided `ucred` is generally trustworthy for identifying the connecting process at the time of connection.
