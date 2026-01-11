# TelephonyTimeZoneSuggestion - Reverse Engineering Documentation

## Executive Summary
`TelephonyTimeZoneSuggestion` represents a time zone suggestion derived from telephony signals (NITZ, MCC). It includes the zone ID, a "slot index" (identifying the SIM/radio), and metadata about the quality and matching heuristic of the suggestion.

## Architecture Overview
- **Class**: `TelephonyTimeZoneSuggestion`
- **Implements**: `Parcelable`
- **Pattern**: Builder pattern used for construction to manage complexity and invariants.

## Detailed Functionality

### Constants (Enums)
- **MatchType**: `NA`, `NETWORK_COUNTRY_ONLY`, `NETWORK_COUNTRY_AND_OFFSET`, `EMULATOR_ZONE_ID`, `TEST_NETWORK_OFFSET_ONLY`. Describes *how* the zone was determined.
- **Quality**: `NA`, `SINGLE_ZONE`, `MULTIPLE_ZONES_WITH_SAME_OFFSET`, `MULTIPLE_ZONES_WITH_DIFFERENT_OFFSETS`. Describes the certainty.

### Creation
- **`createEmptySuggestion(int slotIndex, String debugInfo)`**: Creates a "withdrawal" suggestion (null Zone ID).
- **Builder**: Used for all other cases. Validates that `MatchType` and `Quality` are consistent with the presence/absence of a Zone ID.

### Validation Logic (`Builder.validate()`)
- If `zoneId` is **null**: `Quality` and `MatchType` MUST be `NA` (0).
- If `zoneId` is **not null**: `Quality` and `MatchType` MUST NOT be `NA`.

### Command Line Parsing
- Parses `--slot_index` (required), `--zone_id` (optional, "_" means null/withdraw), `--quality`, `--match_type`.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mSlotIndex` | `int` | SIM slot identifier. |
| `mZoneId` | `String` (Nullable) | The suggested Zone ID. Null means "no opinion" or "withdraw". |
| `mMatchType` | `int` (Enum) | Heuristic type. |
| `mQuality` | `int` (Enum) | Confidence level. |
| `mDebugInfo` | `List<String>` | Debug metadata. |

## API Reference

### `getSlotIndex()`
- **Returns**: `int`.

### `getZoneId()`
- **Returns**: `String` or `null`.

### `getMatchType()` / `getQuality()`
- **Returns**: Integer constants (see Enums).

### `equals(Object)`
- **Behavior**: Checks equality of Slot, ZoneID, MatchType, Quality. Ignores DebugInfo.

## Java-to-C++ Translation Guide

### Enums
- **Java**: `static final int` with `@IntDef`.
- **C++**: `enum class MatchType : int32_t`, `enum class Quality : int32_t`.

### Validation
- **Critical**: The `validate()` logic in the Builder must be replicated in C++ to prevent creating invalid state objects (e.g., a suggestion with a Zone ID but no Quality).

### Parsing logic
- The command line parser handles `_` as a special value for `null` zone ID. C++ shell argument parsing should replicate this if needed.

## Test Cases & Validation
1.  **Validation**: Attempt to build a suggestion with `ZoneId` but `Quality=NA` -> Should fail/throw.
2.  **Withdrawal**: `createEmptySuggestion` should result in `ZoneId=null`, `Quality=NA`.
3.  **Serialization**: Verify all fields (including enums) transfer correctly.

## Implementation Risks
- **Enum Synchronization**: Ensure C++ enums match the integer values defined in Java exactly.
- **Null String**: Handle `mZoneId` being null (std::optional or empty check, but distinct from "empty string" if that distinction matters).
