# DisplayAddress - Reverse Engineering Documentation

## Executive Summary
`DisplayAddress` is an abstract base class for stable identifiers used to address physical or network-connected displays. These identifiers are designed to be persistent across reboots, unlike logical display IDs.

## Data Model

### 1. Physical Display (`DisplayAddress.Physical`)
*   **ID**: `long` - A 64-bit value combining the physical port and display model.
*   **Port**: `int` (0-255) - The physical connector (e.g., HDMI port). Encoded in the LSB.
*   **Model**: `Long` - Metadata extracted from EDID (Extended Display Identification Data).

### 2. Network Display (`DisplayAddress.Network`)
*   **MAC Address**: `String` - The unique hardware address of the network display (e.g., for Miracast or Cast).

## Detailed Functionality
*   **Stable ID**: Used by `DisplayManager` to track display configurations even when logical IDs change.
*   **Port Matching**: `isPortMatch()` helper identifies if two addresses refer to the same physical connector, even if model information is missing for one.

## Java-to-C++ Translation Guide
*   **Representation**: In C++, this can be implemented as a `std::variant` of a 64-bit integer (physical) and a string (network).
*   **Parceling**: Serialization must match the native `DisplayAddress` implementation in `frameworks/native/libs/ui/`.

## Implementation Risks
*   **Collision**: If EDID is not available, multiple displays on the same model could theoretically collide if the port ID logic is not unique.
*   **Parsing MAC**: Network addresses rely on string comparison; ensure a consistent canonical format (colon notation).
