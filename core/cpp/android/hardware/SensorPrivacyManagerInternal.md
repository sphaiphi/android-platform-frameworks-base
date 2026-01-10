# SensorPrivacyManagerInternal - Reverse Engineering Documentation

## Executive Summary
`SensorPrivacyManagerInternal` is an abstract class used for internal communications within the system server. It provides methods for checking and managing sensor privacy that are not exposed to standard applications.

## Architecture Overview
This class defines the interface for the local service implementation of sensor privacy. It is typically implemented by `SensorPrivacyService` and accessed via `LocalServices`.

## Detailed Functionality

### Methods
- `isSensorPrivacyEnabled(userId, sensor)`: Checks privacy state for a specific user.
- `addSensorPrivacyListener(userId, sensor, listener)`: Internal listener for a specific user.
- `addSensorPrivacyListenerForAllUsers(sensor, listener)`: Global listener.
- `setPhysicalToggleSensorPrivacy(userId, sensor, enable)`: Called by `InputManagerService` to update state based on hardware switch events.

## Java-to-C++ Translation Guide
- **Interface**: `abstract class SensorPrivacyManagerInternal` -> `class SensorPrivacyManagerInternal` (Abstract Base).
- **Internal Callbacks**: Use standard C++ observer patterns.

## Implementation Risks
- Race conditions during user switching.
- Coordination with physical input events (hardware switches).
