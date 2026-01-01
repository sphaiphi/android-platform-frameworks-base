# GnssSignalQuality.java - Reverse Engineering Documentation

## Executive Summary
`GnssSignalQuality` is an interface defining constants for Global Navigation Satellite System (GNSS) signal quality levels. It serves as a mapping to internal protocol buffer enums used by the location server.

## Architecture Overview
- **Type**: Interface (Constants definition)
- **Package**: `android.location`
- **Dependencies**: `android.server.location.ServerLocationProtoEnums` (Internal dependency).

## detailed Functionality
Defines three quality levels for GNSS signals:
1.  **UNKNOWN**: Signal quality is not known.
2.  **POOR**: Signal quality is poor.
3.  **GOOD**: Signal quality is good.

## Data Model
Contains only `int` constants.

| Constant | Value | Description |
| :--- | :--- | :--- |
| `GNSS_SIGNAL_QUALITY_UNKNOWN` | -1 | Mapped from proto. |
| `GNSS_SIGNAL_QUALITY_POOR` | 0 | Mapped from proto. |
| `GNSS_SIGNAL_QUALITY_GOOD` | 1 | Mapped from proto. |
| `NUM_GNSS_SIGNAL_QUALITY_LEVELS` | 2 | Count of valid levels (0 and 1). |

## Java-to-C++ Translation Guide

### Enum Definition
Translate this into a C++ `enum class`.

```cpp
namespace android::location {

enum class GnssSignalQuality : int32_t {
    UNKNOWN = -1,
    POOR = 0,
    GOOD = 1
};

} // namespace android::location
```

### Considerations
-   The Java code references `ServerLocationProtoEnums`. In C++, verify if strict alignment with the proto values is required (likely yes for serialization compatibility).
