# ProgramSelector - Reverse Engineering Documentation

## Executive Summary
`ProgramSelector` acts as a complex key for tuning to radio stations. It holds a primary identifier (like frequency or RDS PI) and optional secondary identifiers (like HD subchannel) and vendor-specific IDs. It handles technology-specific logic (AM/FM/HD/DAB).

## Architecture Overview
-   **Type**: Parcelable, System API.
-   **Package**: `android.hardware.radio`.
-   **Role**: Uniquely identifies a radio program. Used for tuning and in program lists.

## Detailed Functionality

### Core Fields
-   `mProgramType`: Legacy integer (deprecated).
-   `mPrimaryId`: The main `Identifier` (e.g., frequency). Required.
-   `mSecondaryIds`: Array of `Identifier`s. Optional hints or sub-channel info.
-   `mVendorIds`: Array of `long`s for vendor-specific data.

### Identifiers
-   **Inner Class**: `Identifier` (Parcelable).
    -   `mType`: Integer type (e.g., `IDENTIFIER_TYPE_AMFM_FREQUENCY`).
    -   `mValue`: Long value.
-   **Types**:
    -   `AMFM_FREQUENCY` (1): kHz.
    -   `RDS_PI` (2): 16-bit.
    -   `HD_STATION_ID_EXT` (3): 64-bit (Station ID + Subchannel + Frequency).
    -   `DAB_SID_EXT` (5): Deprecated.
    -   `DAB_DMB_SID_EXT` (14): 44-bit (SId + ECC + SCIdS).
    -   `HD_STATION_NAME` (10004): 64-bit encoded name.
    -   And others (Vendor, DRM, etc.).

### Logic
-   **Creation**:
    -   `createAmFmSelector`: Factory method. Handles band determination (AM vs FM) based on frequency if band is not explicit. Supports HD subchannels (maps to `IDENTIFIER_TYPE_HD_SUBCHANNEL`).
-   **Equality**:
    -   `equals/hashCode`: Based **only** on `mPrimaryId`.
    -   `strictEquals`: Checks `mPrimaryId` and `mSecondaryIds`.
-   **Accessors**:
    -   `getFirstId(int type)`: Finds first identifier of a type.
    -   `getAllIds(int type)`: Finds all identifiers of a type.
    -   `withSecondaryPreferred`: Returns a new selector with a specific secondary ID prioritized.

## Data Model
-   **Identifier Type**: Integer constants.
-   **Value**: Long (64-bit).

## Java-to-C++ Translation Guide
-   **Structs**: Map `Identifier` to a C++ struct/class.
-   **Constructors**: Replicate `createAmFmSelector` logic, especially the frequency/band heuristics.
-   **Equality**: Implement `operator==` corresponding to Java's `equals` (primary ID only) and maybe a separate method for strict equality.
-   **Container**: Use `std::vector` for secondary IDs.

## Implementation Risks
-   **Bitwise Operations**: HD Radio and DAB identifiers use specific bit layouts (e.g., packing Station ID, Subchannel, and Frequency into 64 bits). These bitwise operations must be precisely replicated in C++.
-   **Legacy Compat**: Note the deprecated fields and types; focus on `Identifier` based logic.

---
