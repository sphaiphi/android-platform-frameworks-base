# HealthStatsParceler - Reverse Engineering Documentation

## Executive Summary
`HealthStatsParceler` is a wrapper class designed to bridge `HealthStatsWriter` (which is mutable and write-only) and `HealthStats` (which is immutable and read-only) via the Parcelable interface. It allows a `HealthStatsWriter` to be sent across Binder IPC without explicitly converting it to a `HealthStats` object first, potentially saving an object allocation/copy on the sending side if the data is just being passed through.

## Architecture Overview
-   **Pattern**: Parcelable Wrapper / Adapter.
-   **Dual Mode**:
    1.  **Writer Mode**: Holds a `HealthStatsWriter`. When written to a Parcel, it asks the writer to flatten itself.
    2.  **Reader Mode**: Constructed from a Parcel. It immediately deserializes into a `HealthStats` object.

## Detailed Functionality

### Writing (Marshaling)
-   **Constructor**: `HealthStatsParceler(HealthStatsWriter writer)`
-   **`writeToParcel`**: Delegates directly to `mWriter.flattenToParcel(out)`.
-   **Optimization**: Avoids creating the intermediate `HealthStats` object on the server side (BatteryStatsService) just to send it to the client.

### Reading (Unmarshaling)
-   **Constructor**: `HealthStatsParceler(Parcel in)`
-   **Logic**: Instantiates `mHealthStats = new HealthStats(in)`.
-   **`getHealthStats()`**: Returns the cached `mHealthStats` object.

### Self-Reflective Usage
-   **`getHealthStats()` on Writer Mode**: If code needs the `HealthStats` object locally from the wrapper, it simulates a Parcel round-trip:
    1.  `Parcel.obtain()`
    2.  `mWriter.flattenToParcel`
    3.  `new HealthStats(parcel)`
    4.  Returns the new object.

## API Reference
-   `writeToParcel(Parcel, int)`: Serializes the underlying writer.
-   `getHealthStats()`: Returns the immutable stats object (performing serialization/deserialization if necessary).

## Java-to-C++ Translation Guide
-   **Relevance**: This is largely a Java-specific binding optimization helper.
-   **C++ equivalent**: Likely unnecessary if `HealthStats` and `HealthStatsWriter` are unified or if the Binder interface definition (AIDL) handles the type conversion.
-   **If needed**: Implement a class that can hold either a reference to a Builder or the finished Object, and serializes whichever is present.

## Questions for C++ Team
1.  Does the C++ Binder interface (`IBatteryStats`) return `HealthStatsParceler` or just `HealthStats`? The AIDL defines `parcelable HealthStatsParceler;`, so the C++ side will receive this structure.
2.  The C++ `readFromParcel` will likely just deserialize directly into a `HealthStats` equivalent struct.
