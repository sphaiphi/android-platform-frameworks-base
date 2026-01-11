# AggregateBatteryConsumer - Reverse Engineering Documentation

## Executive Summary
`AggregateBatteryConsumer` represents the total power consumption across the entire device or a specific scope (e.g., all apps). It aggregates metrics from multiple `BatteryConsumer` instances (individual apps, system services) to provide a holistic view of battery usage.

## Architecture Overview
-   **Inheritance**: Extends `BatteryConsumer`.
-   **Pattern**: Composite / Aggregate.
-   **Data Storage**: Uses `BatteryConsumerData` (cursor-window based) to store aggregated power values and usage durations.

## Data Model
-   **Scope**: Defined by `AGGREGATE_BATTERY_CONSUMER_SCOPE_DEVICE` (0) or `AGGREGATE_BATTERY_CONSUMER_SCOPE_ALL_APPS` (1).
-   **Power Components**: Contains a `PowerComponents` object holding detailed breakdown (CPU, Screen, WiFi, etc.).
-   **Consumed Power**: Total power in mAh.

## API Reference
-   `getConsumedPower()`: Total power.
-   `getScope()`: Returns the aggregation scope.
-   `writeToXml(...)`: Serialization for persistence.

## Java-to-C++ Translation Guide
-   **Data Layout**: Relies on `BatteryConsumer.BatteryConsumerDataLayout` indices. C++ implementation needs to match the column indices (`COLUMN_INDEX_SCOPE`, `COLUMN_INDEX_CONSUMED_POWER`).
-   **XML Parsing**: Corresponds to `BatteryUsageStats` XML format.
