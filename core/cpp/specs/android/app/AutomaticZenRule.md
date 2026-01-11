# AutomaticZenRule - Reverse Engineering Documentation

## Executive Summary
`AutomaticZenRule` represents a rule for Do Not Disturb (Zen) mode. It defines conditions (schedule, event) under which DND should be activated, the interruption filter to apply, and configuration details.

## Architecture Overview
*   **Type**: Parcelable Data Class.
*   **Usage**: Used with `NotificationManager`.

## Detailed Functionality
*   **Fields**:
    *   `name`: Rule name.
    *   `owner`: ComponentName of the provider (ConditionProviderService).
    *   `conditionId`: Uri describing the rule condition.
    *   `interruptionFilter`: Filter level (Priority, Alarms, None).
    *   `enabled`: Boolean state.
    *   `zenPolicy`: `ZenPolicy` object (granular controls).
    *   `deviceEffects`: `ZenDeviceEffects`.
    *   `configurationActivity`: Activity to edit the rule.
    *   `type`: Rule type (Schedule, Calendar, Bedtime, etc.).

## Data Model
*   Includes `Builder` for construction.
*   Constants for types (`TYPE_SCHEDULE_TIME`, `TYPE_EVENT`, etc.) and fields.

## Java-to-C++ Translation Guide
*   Standard Parcelable mapping.
*   Dependencies: `ComponentName`, `Uri`, `ZenPolicy`, `ZenDeviceEffects`.

## Implementation Risks
*   **Validation**: Input validation (string lengths, types) is important.
