# NetworkStatsDataMigrationUtils.java - Reverse Engineering Documentation

## Executive Summary
`NetworkStatsDataMigrationUtils` is a system utility class designed to facilitate the migration of persistent network statistics from legacy formats (pre-Android 13) to the modern formats used by the Connectivity mainline module. It provides logic to read legacy binary files (`netstats_xt.bin`, `netstats_uid.bin`, etc.) and convert them into `NetworkStatsCollection` objects.

## Architecture Overview
- **Type**: Utility Class (System API)
- **Package**: `android.net.netstats`
- **Visibility**: `@SystemApi(client = MODULE_LIBRARIES)` / `@hide`
- **Dependencies**: `android.net.NetworkStatsCollection`, `android.net.NetworkStatsHistory`, `android.net.NetworkIdentity`.

## Detailed Functionality

### Core Responsibilities
1.  **File Location Discovery**:
    -   Legacy files are located in `/data/system/`.
    -   Specific files: `netstats_xt.bin`, `netstats_uid.bin`.
    -   Newer legacy files (tagged/uid) are in `/data/system/netstats/` with prefixes like `xt.`, `uid.`, `uid_tag.`.
2.  **Binary Parsing**:
    -   Uses `ArtFastDataInput` (a performance-optimized version of `DataInputStream`).
    -   Verifies a file magic header: `FILE_MAGIC` (`0x414E4554` - "ANET").
    -   Handles multiple versions of the binary format (`VERSION_UNIFIED_INIT`, `VERSION_UID_WITH_TAG`, etc.).
3.  **Data Structure Reconstitution**:
    -   **NetworkIdentitySet**: Parses sets of network identities (Type, RAT Type, SubscriberId, NetworkId, Roaming, Metered, Default, OEM Managed, SubId). Handles legacy mobile type collapse (e.g., mapping `TYPE_MOBILE_HIPRI` to `TYPE_MOBILE`).
    -   **NetworkStatsHistory**: Parses time-series buckets containing `rxBytes`, `rxPackets`, `txBytes`, `txPackets`, and `operations`. Supports variable-length `long` encoding (protobuf-style) in newer versions.
    -   **NetworkStatsCollection**: Builds a map of `Key` (Ident, UID, Set, Tag) to `History`.

### Migration Workflow
The system (e.g., `NetworkStatsService`) calls `readPlatformCollection` up to three times across reboots to attempt migration. If successful, the data is merged into the new stats system.

## Data Model

### Legacy Prefixes
-   `PREFIX_XT` ("xt"): Interface-level statistics.
-   `PREFIX_UID` ("uid"): UID-level statistics.
-   `PREFIX_UID_TAG`: Tagged UID-level statistics (e.g., specific app sockets).

### Binary Format Versions
-   Handles evolution of the data format, such as the addition of roaming flags, network IDs, meteredness, and SubIDs.

## Java-to-C++ Translation Guide

### Binary Parsing
Porting this to C++ requires a strict byte-for-byte implementation of the Java `DataInput` methods (`readInt`, `readLong`, `readUTF`) and the custom `readVarLong` (LEB128 variant).

```cpp
// Protobuf-style varlong (LEB128) implementation
int64_t readVarLong(InputStream& in) {
    int shift = 0;
    int64_t result = 0;
    while (shift < 64) {
        uint8_t b = in.readByte();
        result |= static_cast<int64_t>(b & 0x7F) << shift;
        if ((b & 0x80) == 0) return result;
        shift += 7;
    }
    throw ProtocolException("malformed var long");
}
```

### Data Mapping
-   **NetworkIdentitySet**: Use a `std::set<NetworkIdentity>` where `NetworkIdentity` is a C++ struct with a custom comparator.
-   **NetworkStatsHistory**: Use a `std::vector` of bucket structs or a specialized time-series container.

### Constants
The `FILE_MAGIC` and version constants must be preserved exactly to read existing disk files.

## Implementation Risks
-   **Byte Order**: Java `DataInputStream` is Big-Endian. Ensure C++ `readInt`/`readLong` handles endianness correctly.
-   **String Encoding**: `readUTF()` in Java has a specific two-byte length prefix.
-   **File System Access**: Migration involves reading from protected system directories. In C++, this requires appropriate SELinux permissions and capabilities.
