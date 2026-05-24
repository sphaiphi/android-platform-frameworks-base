# SubscriptionPlan - Reverse Engineering Documentation

## Executive Summary
`SubscriptionPlan` describes a carrier billing plan (e.g., "5GB Monthly Data"). It is used by the OS to track data usage against limits and provide UI feedback to the user. It is a Parcelable class with a Builder pattern.

## Data Model

### Core Fields
*   **cycleRule** (`RecurrenceRule`): Defines the start time and period (e.g., monthly) of the plan.
*   **title/summary** (`CharSequence`): Display strings.
*   **dataLimitBytes** (`long`): Total data allowed (or `BYTES_UNLIMITED`, `BYTES_UNKNOWN`).
*   **dataLimitBehavior** (`int`): Action when limit reached (`DISABLED`, `BILLED`, `THROTTLED`).
*   **dataUsageBytes** (`long`): Data consumed so far.
*   **dataUsageTime** (`long`): Timestamp of the usage snapshot.
*   **networkTypes** (`int[]`): Array of `TelephonyManager.NETWORK_TYPE_*` this plan applies to.
*   **mSubscriptionStatus** (`int`): Status of the sub (Active, Suspended, etc.).

## API Reference
*   **Builder**: `createRecurring` / `createNonrecurring` to instantiate.
*   **Setters**: `setDataLimit`, `setDataUsage`, `setNetworkTypes`, `setSubscriptionStatus`.
*   **Getters**: Accessors for all fields. `cycleIterator()` provides a utility to calculate past cycles.

## Java-to-C++ Translation Guide
*   **Parcelable**: Implement serialization.
    *   `RecurrenceRule` is another Parcelable (`android.util.RecurrenceRule`) that needs to be handled/mapped.
    *   `CharSequence` -> `std::u16string` or `std::string`.
    *   `int[]` -> `std::vector<int32_t>`.
*   **Time**: Uses `java.time.ZonedDateTime` and `Period`. C++ equivalent might use `std::chrono` or a dedicated date-time library capable of handling recurrences.

## Implementation Risks
*   **Complex Types**: `RecurrenceRule` involves time zones and calendar logic. Ensure the C++ side can parse/serialize this correctly if it's passed across Binder.
*   **Validation**: The Builder enforces constraints (e.g., end time after start time). C++ construction should enforce similar invariants.
