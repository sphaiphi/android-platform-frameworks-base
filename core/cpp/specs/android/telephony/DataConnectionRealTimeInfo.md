# DataConnectionRealTimeInfo - Reverse Engineering Documentation

## Executive Summary
`DataConnectionRealTimeInfo` is a simple Parcelable data class used to transport real-time status information about a cellular data connection, specifically focusing on the power state of the modem's data context.

## Data Model
*   **mTime** (`long`): Timestamp of when the info was collected (nanoseconds since boot).
*   **mDcPowerState** (`int`): The power state of the data connection.
    *   `DC_POWER_STATE_LOW` (1)
    *   `DC_POWER_STATE_MEDIUM` (2)
    *   `DC_POWER_STATE_HIGH` (3)
    *   `DC_POWER_STATE_UNKNOWN` (Integer.MAX_VALUE)

## API Reference
*   **Getters**: `getTime()`, `getDcPowerState()`.
*   **Parcelable**: Standard `writeToParcel` and `createFromParcel`.

## Java-to-C++ Translation Guide
*   **Structure**: Plain Old Data (POD) struct.
*   **Serialization**: Must implement `Parcelable` read/write compatible with the Java definition.
    *   Order: `long` (time) -> `int` (state).

## Questions for C++ Team
*   The class TODO mentions "How to handle multiple subscriptions?". Currently, this class has no field for `subId`. Is this info associated with a specific phone/slot implicitly via the API that returns it?
