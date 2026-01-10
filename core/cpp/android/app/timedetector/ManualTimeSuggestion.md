# ManualTimeSuggestion - Reverse Engineering Documentation

## Executive Summary
`ManualTimeSuggestion` represents a time signal provided manually by a user (e.g., via settings). It encapsulates the suggested time (as a `UnixEpochTime` object) and debugging metadata. It is a `Parcelable` object designed to be passed across process boundaries, primarily from the settings UI to the `TimeDetectorService`. It delegates most of its logic to `TimeSuggestionHelper`.

## Architecture Overview
- **Class**: `ManualTimeSuggestion`
- **Implements**: `Parcelable`
- **Helper**: Delegates logic to `TimeSuggestionHelper` to share behavior with other suggestion types.
- **Key Dependencies**: `android.app.time.UnixEpochTime`, `android.app.timedetector.TimeSuggestionHelper`.

## Detailed Functionality

### Constructors
**Purpose**: Initialize the suggestion.
**Algorithm**:
1.  **Public Constructor**: Takes a `UnixEpochTime`. Creates a `TimeSuggestionHelper`.
2.  **Private Constructor**: Takes a `TimeSuggestionHelper` (used by Parcelable creator).
3.  **Command Line**: `parseCommandLineArg` uses `TimeSuggestionHelper` to parse shell arguments.

### `getUnixEpochTime()`
**Purpose**: Retrieve the suggested time.
**Returns**: `UnixEpochTime` (elapsed realtime reference + unix epoch time).

### Debug Information
**Purpose**: Store and retrieve strings for debugging why a suggestion was made.
**Methods**: `addDebugInfo(String...)`, `getDebugInfo()`.
**Implementation**: Delegated to `TimeSuggestionHelper`.

### Parcelable Implementation
**Purpose**: Serialization for IPC.
**Methods**: `describeContents`, `writeToParcel`, `CREATOR`.
**Implementation**: Delegated to `TimeSuggestionHelper`.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mTimeSuggestionHelper` | `TimeSuggestionHelper` | **Invariant**: Non-null. Holds the actual state (time and debug info). |

## API Reference

### `ManualTimeSuggestion(UnixEpochTime unixEpochTime)`
- **Purpose**: Creates a new suggestion.
- **Parameters**: `unixEpochTime` - The time suggestion (reference time + wall clock time).
- **Preconditions**: `unixEpochTime` must not be null.

### `getUnixEpochTime()`
- **Returns**: `UnixEpochTime`.

### `addDebugInfo(String... debugInfos)`
- **Purpose**: Adds debug metadata.

### `equals(Object o)` / `hashCode()`
- **Behavior**: Value equality based on `TimeSuggestionHelper` (which checks `UnixEpochTime` and class type). Debug info is **excluded** from equality checks.

## Java-to-C++ Translation Guide

### Memory Management
- **Java**: Objects are garbage collected.
- **C++**: Use `std::shared_ptr` or `std::unique_ptr` for `ManualTimeSuggestion` and its internal helper. The `TimeSuggestionHelper` logic might be embedded directly or composed.

### Parcelable
- **Java**: `Parcelable` interface.
- **C++**: Implement `android::os::Parcelable` trait or manual serialization methods compatible with the Binder transaction buffer layout.

### Composition
- **Java**: Uses a helper object `TimeSuggestionHelper` to reuse code.
- **C++**: Can use inheritance (base class `TimeSuggestion`) or composition similar to Java. Given `TimeSuggestionHelper` is final and effectively a mixin, composition or a base struct `TimeSuggestionState` is appropriate.

### Debug Info
- **Java**: `List<String>`.
- **C++**: `std::vector<std::string>`.

## Test Cases & Validation
1.  **Serialization**: Create instance, write to parcel, read back. Verify `UnixEpochTime` matches.
2.  **Equality**: Two instances with same time should be equal. Two instances with same time but different debug info should still be equal.
3.  **Command Line Parsing**: Verify `parseCommandLineArg` correctly parses valid flags.

## Implementation Risks
- **Parcel Compatibility**: Ensure the wire format matches exactly what Java writes (delegated to helper).
- **Null Handling**: The helper prevents nulls; C++ must ensure valid state.

## Questions for C++ Team
- Should we replicate the `TimeSuggestionHelper` pattern or just implement the logic directly in the C++ class since it's simple?
