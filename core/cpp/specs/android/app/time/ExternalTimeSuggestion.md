# ExternalTimeSuggestion - Reverse Engineering Documentation

## Executive Summary
Represents a time suggestion originating from an external source (e.g., HAL, Vehicle Network, NTP). It encapsulates a timestamp (UTC) cross-referenced with the device's elapsed realtime clock to account for latency between suggestion creation and processing.

## Architecture Overview
*   **Type**: `public final class` implementing `Parcelable`.
*   **Design Pattern**: Immutable Value Object / Wrapper.
*   **Helper**: Delegates most logic to `TimeSuggestionHelper` (not provided in context, needs assumption or analysis of dependency).

## Detailed Functionality
*   **Purpose**: transport a suggestion that "Current Unix Time is X, measured when System Elapsed Time was Y".
*   **Latency Compensation**: The system calculates `CurrentTime = SuggestionTime + (CurrentElapsed - SuggestionElapsed)`.

## Data Model
*   **Internal State**: Managed by `TimeSuggestionHelper`.
*   **Logical State**: `UnixEpochTime` (pair of `long` values: `mElapsedRealtimeMillis`, `mUnixEpochTimeMillis`).
*   **Debug Info**: List of strings (debug history).

## API Reference
*   `ExternalTimeSuggestion(long elapsedRealtimeMillis, long suggestionMillis)`: Constructor.
*   `UnixEpochTime getUnixEpochTime()`: Returns the time signal.
*   `List<String> getDebugInfo()`: Returns debug metadata.
*   `void addDebugInfo(String...)`: Appends debug info.
*   `parseCommandLineArg(ShellCommand)`: Factory for shell usage.

## Java-to-C++ Translation Guide
*   **Parcelable**: Implement `Parcelable` protocol using `binder/Parcel.h` or `android::os::Parcel`.
*   **TimeSuggestionHelper**: This class is likely a shared utility. In C++, check if a template or base class exists. If not, reimplement the storage of `UnixEpochTime` and `vector<string>` for debug info.
*   **Types**: `int64_t` for milliseconds.

## Test Cases & Validation
*   Serialization/Deserialization loop test.
*   Equality checks (ignoring debug info).

## Implementation Risks
*   `TimeSuggestionHelper` logic must be replicated or linked. If it handles `equals`/`hashCode` ignoring debug info, C++ must do the same.
