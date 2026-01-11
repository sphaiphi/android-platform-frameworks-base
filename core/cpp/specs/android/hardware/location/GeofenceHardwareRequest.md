# GeofenceHardwareRequest - Reverse Engineering Documentation

## Executive Summary
`GeofenceHardwareRequest` is a builder/configuration object for creating geofences. It defines properties like latitude, longitude, radius, transitions to monitor, and notification responsiveness.

## Architecture Overview
- **Pattern**: Builder / Configuration Object.
- **Role**: Parameters for `addGeofence`.

## Detailed Functionality
- **Defaults**:
  - Unknown timer: 30s.
  - Monitor transitions: Entered | Exited | Uncertain.
  - Notification responsiveness: 5s.
  - Source: GNSS.
- **Factory**: `createCircularGeofence(lat, long, radius)`.

## Data Model
- `mLatitude`, `mLongitude`, `mRadius`: `double`.
- `mMonitorTransitions`, `mUnknownTimer`, `mNotificationResponsiveness`, `mSourceTechnologies`: `int`.

## Java-to-C++ Translation Guide
- **Data Structure**: Struct/Class with builder methods.

## Questions for C++ Team
- None.
