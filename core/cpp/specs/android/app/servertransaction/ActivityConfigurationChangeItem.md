# ActivityConfigurationChangeItem - Reverse Engineering Documentation

## Executive Summary
`ActivityConfigurationChangeItem` is a transaction item responsible for delivering activity configuration updates (e.g., screen rotation, locale changes, window resize) from the system server to the client application. It ensures that the client activity's configuration and window info are updated in sync with the server's state.

## Architecture Overview
- **Inheritance**: Extends `ActivityTransactionItem`, which holds the target activity's token.
- **Role**: Concrete implementation of a client transaction item specifically for configuration changes.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `preExecute`
**Purpose**: Prepares the client transaction handler for the configuration change.
**Algorithm**:
1. Apply compatibility overrides to the configuration if needed via `CompatibilityInfo.applyOverrideIfNeeded(mConfiguration)`.
2. Notify the client handler of the upcoming configuration change using `client.updatePendingActivityConfiguration()`.
**Java-Specific Notes**:
- Modifies the global/thread-local state regarding pending configurations to ensure subsequent batch items see the new config.
- `CompatibilityInfo` is an internal Android helper for handling app compatibility modes.

### `execute`
**Purpose**: Executes the configuration change on the client.
**Algorithm**:
1. Start tracing `activityConfigChanged`.
2. Call `client.handleActivityConfigurationChanged()` with the activity record, configuration, and window info.
3. End tracing.
**Java-Specific Notes**:
- `Trace` is used for system performance profiling (Systrace).
- `ActivityClientRecord` is looked up via the parent `ActivityTransactionItem` logic.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mConfiguration` | `android.content.res.Configuration` | The new configuration to apply. |
| `mActivityWindowInfo` | `android.window.ActivityWindowInfo` | Information about the activity's window (bounds, state). |

### Serialization (Parcelable)
- **Flattening**:
  - Writes parent data (`ActivityTransactionItem`).
  - Writes `mConfiguration` as a typed object.
  - Writes `mActivityWindowInfo` as a typed object.
- **Unflattening**:
  - Reads parent data.
  - Reads `mConfiguration`.
  - Reads `mActivityWindowInfo`.
  - Validates non-null for both fields.

## API Reference

### `public ActivityConfigurationChangeItem(@NonNull IBinder activityToken, @NonNull Configuration config, @NonNull ActivityWindowInfo activityWindowInfo)`
- **Constructor**: Initializes the item with the target activity token, configuration, and window info.
- **Notes**: Creates defensive copies of `config` and `activityWindowInfo`.

### `public boolean equals(Object o)`
- **Logic**: Checks equality of:
  - Parent state (activity token).
  - `mConfiguration`.
  - `mActivityWindowInfo`.

## Java-to-C++ Translation Guide

### Data Structures
- `android.content.res.Configuration` -> Mapped to C++ `Configuration` class (usually `ResTable_config` wrapper + extra fields).
- `android.window.ActivityWindowInfo` -> C++ equivalent struct/class for window info.
- `android.os.IBinder` -> `android::sp<android::IBinder>`.

### Memory Management
- Java uses automatic garbage collection. C++ implementation should manage the lifecycle of the item, likely using smart pointers (`std::unique_ptr` or `std::shared_ptr`) if passed around, or stack allocation if transient.
- The `mConfiguration` and `mActivityWindowInfo` are owned by this item (copies created in constructor).

### Serialization
- Use `android::Parcel` for writing/reading.
- `writeTypedObject` equivalent in C++ `Parcel` (e.g., `writeParcelable`).
- Ensure strict order matching the Java `writeToParcel`.

## Implementation Risks
- **Null Safety**: Java uses `@NonNull` annotations and `requireNonNull`. C++ must check for validity of pointers or use references where appropriate.
- **Tracing**: Ensure the `Trace` calls use the correct tag constants defined in C++ headers.
