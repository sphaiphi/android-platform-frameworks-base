# ProtoUtils - Reverse Engineering Documentation

## Executive Summary
Helper functions for writing common Android proto structures (AggStats, Duration, BitWiseFlags) and debugging `ProtoInputStream`.

## Logic
*   **`toAggStatsProto`**: Writes min/max/average stats.
*   **`currentFieldToString`**: Formats current field info from `ProtoInputStream` for logging/errors.

## Java-to-C++ Translation Guide
*   **Utility**: Static helper functions.
