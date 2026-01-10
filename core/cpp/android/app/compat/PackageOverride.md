# PackageOverride - Reverse Engineering Documentation

## Executive Summary
`PackageOverride` defines a specific override rule for a compatibility change, applicable to a particular version range of an application. It allows the system to force a feature flag to be enabled or disabled for specific app versions, often used for hotfixing or targeted testing.

## Architecture Overview
*   **Type**: Data Object / Parcelable-like.
*   **Visibility**: System API (`@SystemApi`).
*   **Design Pattern**: Builder Pattern.

## Detailed Functionality

### Core Logic
An override consists of:
1.  **Version Range**: `[minVersionCode, maxVersionCode]`.
2.  **Value**: `enabled` (boolean).

### Evaluation
*   **`evaluate(long versionCode)`**:
    *   Checks if `min <= versionCode <= max`.
    *   If yes, returns `VALUE_ENABLED` (1) or `VALUE_DISABLED` (2) based on the `enabled` flag.
    *   If no, returns `VALUE_UNDEFINED` (0).
*   **`evaluateForAllVersions()`**:
    *   Optimization check. If the range covers `Long.MIN_VALUE` to `Long.MAX_VALUE`, returns the value.
    *   Otherwise, returns `VALUE_UNDEFINED`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mMinVersionCode` | `long` | Start of version range (inclusive). |
| `mMaxVersionCode` | `long` | End of version range (inclusive). |
| `mEnabled` | `boolean` | The override value. |

### Constants (`@EvaluatedOverride`)
*   `VALUE_UNDEFINED = 0`
*   `VALUE_ENABLED = 1`
*   `VALUE_DISABLED = 2`

## API Reference

### Builder
*   `setMinVersionCode(long)`: Default `Long.MIN_VALUE`.
*   `setMaxVersionCode(long)`: Default `Long.MAX_VALUE`.
*   `setEnabled(boolean)`: Default `false`.
*   `build()`: Validates that `min <= max`.

### Accessors
*   `getMinVersionCode()`
*   `getMaxVersionCode()`
*   `isEnabled()`

### Serialization
*   `writeToParcel(Parcel)`
*   `createFromParcel(Parcel)`
*   *Note*: While not implementing `Parcelable` interface explicitly in the provided text, it follows the contract.

## Java-to-C++ Translation Guide

### Class Definition
```cpp
class PackageOverride {
public:
    enum EvaluatedOverride {
        VALUE_UNDEFINED = 0,
        VALUE_ENABLED = 1,
        VALUE_DISABLED = 2
    };

    // Constructors, Getters
    int evaluate(int64_t versionCode) const;
    int evaluateForAllVersions() const;

    // Serialization
    status_t writeToParcel(Parcel* parcel) const;
    static PackageOverride createFromParcel(const Parcel& parcel);

private:
    int64_t mMinVersionCode;
    int64_t mMaxVersionCode;
    bool mEnabled;
};
```

### Parcelable
*   **Java**: `dest.writeLong`, `dest.writeBoolean`.
*   **C++**: Use `libbinder`'s `Parcel` class. `parcel->writeInt64(...)`, `parcel->writeBool(...)`.

### Builder
Implement a nested `Builder` class in C++ following the same pattern, returning `PackageOverride` instances.

## Test Cases & Validation
1.  **Range Check**: Create override for range [10, 20].
    *   `evaluate(9)` -> `UNDEFINED`.
    *   `evaluate(10)` -> `ENABLED/DISABLED`.
    *   `evaluate(15)` -> `ENABLED/DISABLED`.
    *   `evaluate(20)` -> `ENABLED/DISABLED`.
    *   `evaluate(21)` -> `UNDEFINED`.
2.  **Full Range**: Create default builder override. `evaluateForAllVersions()` should return a value.
3.  **Validation**: Builder should throw/error if `min > max`.

## Implementation Risks
*   **Version Code Types**: Ensure `int64_t` is used for version codes to match Java's `long`.
*   **Parceling Compatibility**: The C++ serialization order must exactly match the Java `writeToParcel` order to allow passing these objects between Java/C++ layers if necessary (e.g., via AIDL).
