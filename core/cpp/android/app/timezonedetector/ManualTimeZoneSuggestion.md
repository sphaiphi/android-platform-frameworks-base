# ManualTimeZoneSuggestion - Reverse Engineering Documentation

## Executive Summary
`ManualTimeZoneSuggestion` encapsulates a user-provided time zone suggestion (typically from Settings). It is a Parcelable data object containing the suggested time zone ID (Olson ID) and optional debug metadata.

## Architecture Overview
- **Class**: `ManualTimeZoneSuggestion`
- **Implements**: `Parcelable`
- **Purpose**: Carrier for manual time zone updates across IPC boundaries.

## Detailed Functionality

### Core Properties
- **Zone ID**: The string ID of the time zone (e.g., "America/Los_Angeles"). Non-null.
- **Debug Info**: A list of strings to aid in tracing why a suggestion was made.

### Constructors
- `ManualTimeZoneSuggestion(String zoneId)`: Main constructor.
- `createFromParcel(Parcel)`: Internal use for deserialization.

### Command Line Parsing
- `parseCommandLineArg(ShellCommand)`: Parses `--zone_id <id>` from shell commands to create a suggestion.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mZoneId` | `String` | The Olson time zone ID (e.g., "Europe/London"). **Invariant**: Non-null. |
| `mDebugInfo` | `ArrayList<String>` | List of debug strings. Nullable internally, but getter returns empty list. |

## API Reference

### `getZoneId()`
- **Returns**: `String` (Non-null).

### `addDebugInfo(String... debugInfos)`
- **Purpose**: Appends strings to the debug info list.

### `equals(Object o)`
- **Behavior**: Checks equality of `mZoneId`. **Ignores** `mDebugInfo`.

## Java-to-C++ Translation Guide

### Type Mapping
- `String` -> `std::string`.
- `ArrayList<String>` -> `std::vector<std::string>`.

### Parcelable
- **Java**: `Parcelable` interface.
- **C++**: Implement `android::os::Parcelable` or equivalent serialization compatible with Binder.

### Equality
- **Important**: C++ implementation of `==` operator should also ignore debug info to match Java semantics.

## Test Cases & Validation
1.  **Serialization**: Verify round-trip parceling preserves the Zone ID.
2.  **Equality**: Two suggestions with the same Zone ID must be equal regardless of debug info.
3.  **Command Line**: Parse `--zone_id` correctly.

## Implementation Risks
- **Null Safety**: Java constructor enforces `Objects.requireNonNull(zoneId)`. C++ constructor must ensure `zoneId` is valid/non-empty if that's the contract (though empty string might be a valid but "unknown" zone depending on deeper logic, here it just looks like a string container).
