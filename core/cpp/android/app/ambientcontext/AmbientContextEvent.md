# AmbientContextEvent - Reverse Engineering Documentation

## Executive Summary
`AmbientContextEvent` is a data carrier class (Parcelable) representing a single detected ambient event. It encapsulates the type of event (e.g., cough, snore), the time range of occurrence, confidence levels, and optional vendor-specific data.

## Architecture Overview
-   **Type**: Final Data Class (POJO equivalent).
-   **Design Pattern**: Builder Pattern (`AmbientContextEvent.Builder`).
-   **Role**: Data Transfer Object (DTO) passed between the Ambient Context Service and client applications via IPC (Binder).
-   **Dependencies**:
    -   `android.os.Parcelable`: For serialization across processes.
    -   `android.os.PersistableBundle`: For arbitrary vendor data.
    -   `java.time.Instant`: For high-precision timestamps.

## Detailed Functionality

### Constants & Definitions
The class defines integer constants for:
-   **Event Codes**: `EVENT_UNKNOWN` (0), `EVENT_COUGH` (1), `EVENT_SNORE` (2), `EVENT_BACK_DOUBLE_TAP` (3), `EVENT_VENDOR_WEARABLE_START` (100000).
-   **Levels**: `LEVEL_UNKNOWN` (0) to `LEVEL_HIGH` (5).
-   **Keys**: `KEY_VENDOR_WEARABLE_EVENT_NAME` string.

### Data Validation
-   **Constructor/Builder**: Validates that required fields (start time, end time, vendor data) are non-null.
-   **Range Checks**: Vendor events (> 100000) are expected to contain specific keys in `mVendorData` (though strictly enforcing this logic appears to be the responsibility of the detection service or validation layers, the class itself provides the container).

## Data Model

| Field Name | Java Type | C++ Equivalent Type | Description |
| :--- | :--- | :--- | :--- |
| `mEventType` | `int` | `int32_t` / `enum` | Type of event detected. |
| `mStartTime` | `java.time.Instant` | `int64_t` (millis/nanos) | Start timestamp. |
| `mEndTime` | `java.time.Instant` | `int64_t` (millis/nanos) | End timestamp. |
| `mConfidenceLevel` | `int` | `int32_t` / `enum` | Confidence 1-5. |
| `mDensityLevel` | `int` | `int32_t` / `enum` | Density 1-5. |
| `mVendorData` | `PersistableBundle` | `std::map` / `Bundle` | Key-value pairs for vendor extensions. |

## API Reference

### Getters
-   `getEventType()`: Returns `int`.
-   `getStartTime()`: Returns `Instant`.
-   `getEndTime()`: Returns `Instant`.
-   `getConfidenceLevel()`: Returns `int`.
-   `getDensityLevel()`: Returns `int`.
-   `getVendorData()`: Returns `PersistableBundle`.

### String Conversion
-   `eventToString(int)`: Static helper converting event int to String name.
-   `levelToString(int)`: Static helper converting level int to String name.
-   `toString()`: Returns human-readable representation of the instance.

### Builder (`AmbientContextEvent.Builder`)
-   Fluid API setters (`setEventType`, `setStartTime`, etc.).
-   `build()`: Validates internal state and constructs the `AmbientContextEvent`.

## Java-to-C++ Translation Guide

### Time Handling
-   Java uses `java.time.Instant`.
-   **C++ Recommendation**: Use `std::chrono::system_clock::time_point` or distinct `int64_t` values representing milliseconds/nanoseconds since epoch, ensuring alignment with how the underlying IPC mechanism serializes `Instant`.

### Parcelable / Serialization
-   Java uses `Parcelable` interface for Binder IPC.
-   **C++ Recommendation**: Implement standard Android Binder serialization (readInt, readLong, readBundle). Note that `PersistableBundle` in C++ maps to `android::os::PersistableBundle`.

### Enums
-   Java uses `@IntDef` annotations.
-   **C++ Recommendation**: Use `enum class EventCode : int32_t` and `enum class Level : int32_t` to ensure type safety.

## Test Cases & Validation
-   **Serialization**: Create an event with all fields populated, write to parcel, read back, verify equality.
-   **Defaults**: Verify Builder uses default values (Unknown/Min/Max/Empty Bundle) if fields are unset.
-   **Vendor Data**: Verify `PersistableBundle` integrity is maintained.

## Implementation Risks
-   **Time Precision**: `Instant` supports nanoseconds. Ensure C++ serialization logic preserves the required precision (usually Binder serializes Instant as seconds + nanoseconds).
-   **Vendor Data**: `PersistableBundle` handling in C++ can be complex if deep nesting is required.

## Questions for C++ Team
-   Does the C++ Binder interface for `Instant` expect (seconds, nanoseconds) pair or a single millisecond long?
-   Are vendor events supported in the C++ layer, or is this primarily for Java consumption?
