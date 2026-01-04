# BatteryManager - Reverse Engineering Documentation

## Executive Summary
`BatteryManager` is a system service that provides information about the device's battery and charging state. It allows applications to query properties such as charge level, voltage, temperature, and health, and to listen for changes via sticky broadcasts.

## Architecture Overview
- **Service Type**: System-level service retrieved via `Context.getSystemService(Context.BATTERY_SERVICE)`.
- **Backend Interaction**: Communicates with `IBatteryStats` (BatteryStatsService) and `IBatteryPropertiesRegistrar` (batteryproperties service).
- **Data Source**: Receives data from the Health HAL (and previously the BatteryService).
- **Events**: Primarily driven by the `ACTION_BATTERY_CHANGED` sticky broadcast.

## Detailed Functionality

### Battery Property Querying
**Purpose**: To get instantaneous snapshots of battery metrics.
**Algorithm**:
1. Application calls `getIntProperty(id)` or `getLongProperty(id)`.
2. `BatteryManager` makes a Binder call to the `batteryproperties` service.
3. The service queries the kernel/HAL for the requested metric (e.g., `CURRENT_NOW`, `CHARGE_COUNTER`).
4. Returns the value or a sentinel (`Long.MIN_VALUE`) if unsupported.

### Charging State Tracking
**Purpose**: To determine if the device is plugged in and the type of power source.
**Status Constants**:
- `BATTERY_STATUS_CHARGING`
- `BATTERY_STATUS_DISCHARGING`
- `BATTERY_STATUS_FULL`
**Plug Types**: `AC`, `USB`, `WIRELESS`, `DOCK`.

### Health Monitoring
**Purpose**: To detect hardware issues with the battery.
**Health States**: `GOOD`, `OVERHEAT`, `DEAD`, `OVER_VOLTAGE`, `COLD`.

## Data Model

### Key Constants (Extras)
- `EXTRA_LEVEL`: Current battery percentage.
- `EXTRA_VOLTAGE`: Battery voltage in mV.
- `EXTRA_TEMPERATURE`: Battery temperature in tenths of a degree Celsius.
- `EXTRA_CYCLE_COUNT`: Number of full charge cycles.

### Properties
- `BATTERY_PROPERTY_CAPACITY` (4): Remaining percentage.
- `BATTERY_PROPERTY_CURRENT_NOW` (2): Instantaneous current in µA.
- `BATTERY_PROPERTY_STATE_OF_HEALTH` (10): Estimated remaining life as a percentage of design capacity.

## API Reference

### Public Methods
- `boolean isCharging()`: Quick check for power connection.
- `int getIntProperty(int id)`: Query integer metrics.
- `long computeChargeTimeRemaining()`: Estimate time to full charge.

## Java-to-C++ Translation Guide

### Metric Units
- **Java**: Current is in microamperes (µA), Energy in nanowatt-hours (nWh).
- **C++**: Ensure the native HAL types (typically from `android.hardware.health`) are converted to these same units for consistency.

### Service Discovery
- **Java**: `batteryproperties` service.
- **C++**: Use `android::IServiceManager` to get `batteryproperties` and use the `IBatteryPropertiesRegistrar` interface.

## Test Cases & Validation
1. **Capacity Consistency**: Verify that `getIntProperty(BATTERY_PROPERTY_CAPACITY)` matches the value in the `ACTION_BATTERY_CHANGED` extra `level`.
2. **Current Direction**: Verify that `CURRENT_NOW` is positive when charging and negative when discharging.
3. **Temperature Conversion**: Verify that `EXTRA_TEMPERATURE` divided by 10 matches the Celsius value from a hardware sensor.

## Implementation Risks
- **Hardware Accuracy**: Fuel gauge hardware accuracy varies wildly. The C++ implementation should treat these values as estimates and apply smoothing if necessary.
- **Permission Mapping**: Accessing sensitive properties like `SERIAL_NUMBER` or `MANUFACTURING_DATE` requires the `BATTERY_STATS` permission.