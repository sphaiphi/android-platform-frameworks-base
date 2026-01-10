# GeofenceHardwareCallback - Reverse Engineering Documentation

## Executive Summary
`GeofenceHardwareCallback` is an abstract class for receiving geofence transition events and operation status updates (add/remove/pause/resume success/failure).

## Architecture Overview
- **Pattern**: Callback Interface.

## API Reference
- `onGeofenceTransition(id, transition, location, timestamp, type)`
- `onGeofenceAdd(id, status)`
- `onGeofenceRemove(id, status)`
- `onGeofencePause(...)`
- `onGeofenceResume(...)`

## Java-to-C++ Translation Guide
- **C++**: Pure virtual class.
- **Mapping**: `onGeofenceTransition` maps to a C++ callback with `Location` struct/object.

## Questions for C++ Team
- None.
