# Geofence.java - Reverse Engineering Documentation

## Executive Summary
`Geofence` is a data class representing a circular geographical boundary. It is used to define areas for geofencing operations, allowing the system to trigger events when a device enters or exits the specified region. The class supports defining a center point (latitude/longitude), a radius, and an expiration time.

## Architecture Overview
- **Type**: Data Object / `Parcelable`
- **Package**: `android.location`
- **Implements**: `android.os.Parcelable`
- **Role**: Defines the properties of a geofence. Used by location services to track proximity.

## Detailed Functionality

### Core Logic
1.  **Geometry**: Currently supports only circular geofences on a flat, horizontal plane (WGS84 ellipsoid altitude is ignored).
2.  **Expiration**: Geofences have an expiration time defined in realtime milliseconds (since boot).
3.  **Validation**: Input parameters (latitude, longitude, radius) are validated upon construction.

### Properties
-   **Latitude**: -90.0 to +90.0 degrees.
-   **Longitude**: -180.0 to +180.0 degrees.
-   **Radius**: Positive float value in meters.
-   **Expiration**: Realtime milliseconds timestamp.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mLatitude` | `double` | Latitude of the center in degrees. |
| `mLongitude` | `double` | Longitude of the center in degrees. |
| `mRadius` | `float` | Radius of the geofence in meters. |
| `mExpirationRealtimeMs` | `long` | Expiration time in elapsed realtime milliseconds. |

## API Reference

### Static Factory
-   `createCircle(double latitude, double longitude, float radius, long expirationRealtimeMs)`: Creates a new `Geofence` instance. Validates arguments.

### Accessors
-   `getLatitude()`: Returns latitude.
-   `getLongitude()`: Returns longitude.
-   `getRadius()`: Returns radius.

### Logic Methods
-   `isExpired()`: Checks if the geofence is expired relative to `SystemClock.elapsedRealtime()`.
-   `isExpired(long referenceRealtimeMs)`: Checks expiry against a specific timestamp.

### Parcelable
-   Standard `writeToParcel` and `CREATOR` implementation for IPC.

## Java-to-C++ Translation Guide

### Class Definition
A C++ struct or class is appropriate.

```cpp
struct Geofence {
    double latitude;
    double longitude;
    float radius;
    int64_t expiration_realtime_ms;

    bool is_expired(int64_t current_realtime_ms) const {
        return current_realtime_ms >= expiration_realtime_ms;
    }
};
```

### Validation
Ensure input validation logic is replicated in the C++ constructor or factory method:
-   Lat: [-90, 90]
-   Lon: [-180, 180]
-   Radius: > 0

### Serialization
Implement standard Android Parcel serialization if this object needs to cross Binder boundaries from C++.

## Test Cases
1.  **Creation**: Valid lat/lon/radius -> Success.
2.  **Validation Failure**: Lat 91, Lon 181, Radius -1 -> Should throw/fail.
3.  **Expiry**:
    -   `expiration = 1000`, `current = 500` -> Not expired.
    -   `expiration = 1000`, `current = 1000` -> Expired.
    -   `expiration = 1000`, `current = 1500` -> Expired.
