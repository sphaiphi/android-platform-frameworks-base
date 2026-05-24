# GeofenceHardwareMonitorCallback - Reverse Engineering Documentation

## Executive Summary
`GeofenceHardwareMonitorCallback` is an abstract class for receiving status changes of the monitoring system (e.g., GPS hardware became unavailable).

## Architecture Overview
- **Pattern**: Callback Interface.

## API Reference
- `onMonitoringSystemChange(GeofenceHardwareMonitorEvent)`: The primary callback method.
- `onMonitoringSystemChange(type, available, location)`: Deprecated legacy method.

## Java-to-C++ Translation Guide
- **C++**: Pure virtual class.

## Questions for C++ Team
- None.
