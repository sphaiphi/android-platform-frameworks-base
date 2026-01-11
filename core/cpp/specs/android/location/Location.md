# Location.java - Reverse Engineering Documentation

## Executive Summary
`Location` is a comprehensive data class representing a geographic location. It encapsulates core coordinates (latitude, longitude), accuracy, timestamp, and optional fields like altitude, speed, bearing, and their respective accuracies. It includes sophisticated logic for geodesic calculations (distance and bearing) based on the WGS84 ellipsoid and handles data serialization via `Parcelable`.

## Architecture Overview
- **Type**: Data Object / `Parcelable`
- **Package**: `android.location`
- **Key Dependencies**:
    -   `android.os.Bundle`: For extra data.
    -   `android.os.Parcel`: For IPC.
    -   `java.text.DecimalFormat`: For string formatting.
- **Design Pattern**:
    -   **Bitmask**: Uses an integer bitmask (`mFieldsMask`) to track which optional fields are set (Has-Field pattern).
    -   **ThreadLocal Cache**: Uses `ThreadLocal<BearingDistanceCache>` to optimize sequential `distanceTo` and `bearingTo` calls, avoiding re-calculation for the same pair of points.

## Data Model

### State Flags (`mFieldsMask`)
Bitmask flags indicating presence of data:
-   `HAS_ALTITUDE_MASK` (1 << 0)
-   `HAS_SPEED_MASK` (1 << 1)
-   `HAS_BEARING_MASK` (1 << 2)
-   `HAS_HORIZONTAL_ACCURACY_MASK` (1 << 3)
-   `HAS_MOCK_PROVIDER_MASK` (1 << 4)
-   `HAS_ALTITUDE_ACCURACY_MASK` (1 << 5)
-   `HAS_SPEED_ACCURACY_MASK` (1 << 6)
-   `HAS_BEARING_ACCURACY_MASK` (1 << 7)
-   `HAS_ELAPSED_REALTIME_UNCERTAINTY_MASK` (1 << 8)
-   `HAS_MSL_ALTITUDE_MASK` (1 << 9)
-   `HAS_MSL_ALTITUDE_ACCURACY_MASK` (1 << 10)

### Primary Fields
| Field | Type | Description |
| :--- | :--- | :--- |
| `mProvider` | `String` | Name of the location provider (e.g., "gps", "network"). |
| `mTimeMs` | `long` | Unix epoch time in milliseconds. |
| `mElapsedRealtimeNs` | `long` | Elapsed realtime since boot in nanoseconds. |
| `mElapsedRealtimeUncertaintyNs` | `double` | Uncertainty of elapsed realtime (68% confidence). |
| `mLatitudeDegrees` | `double` | Latitude in degrees [-90, 90]. |
| `mLongitudeDegrees` | `double` | Longitude in degrees [-180, 180]. |
| `mHorizontalAccuracyMeters` | `float` | Horizontal accuracy radius (68% confidence). |
| `mAltitudeMeters` | `double` | Altitude above WGS84 ellipsoid in meters. |
| `mAltitudeAccuracyMeters` | `float` | Vertical accuracy (68% confidence). |
| `mSpeedMetersPerSecond` | `float` | Speed in m/s. |
| `mSpeedAccuracyMetersPerSecond` | `float` | Speed accuracy (68% confidence). |
| `mBearingDegrees` | `float` | Bearing in degrees [0, 360). |
| `mBearingAccuracyDegrees` | `float` | Bearing accuracy (68% confidence). |
| `mMslAltitudeMeters` | `double` | Mean Sea Level altitude. |
| `mMslAltitudeAccuracyMeters` | `float` | MSL altitude accuracy. |
| `mExtras` | `Bundle` | Key-value pairs for provider-specific extras. |

## Detailed Functionality

### Geodesic Calculations (`computeDistanceAndBearing`)
-   **Algorithm**: Implements the Inverse Formula (Section 4) from NOAA's "Direct and Inverse Solutions of Geodesics on the Ellipsoid with Application of Nested Equations" (Vincenty's formulae variant?).
-   **Ellipsoid**: WGS84 (Major axis `a = 6378137.0`, flattening `f = 1/298.257223563`).
-   **Iterative Approach**: Uses an iterative loop (max 20 iterations) to solve for lambda.
-   **Outputs**: Distance (meters), Initial Bearing (degrees), Final Bearing (degrees).
-   **Caching**: Stores inputs (lat1, lon1, lat2, lon2) and outputs in a `ThreadLocal` cache to speed up subsequent calls for distance and then bearing.

### String Conversion (`convert`)
-   **Double to String**: Supports formats:
    -   `FORMAT_DEGREES`: `[+-]DDD.DDDDD`
    -   `FORMAT_MINUTES`: `[+-]DDD:MM.MMMMM`
    -   `FORMAT_SECONDS`: `DDD:MM:SS.SSSSS`
-   **String to Double**: Parses the above formats. Uses `StringTokenizer` with delimiter `:`. Handles negative values.

### Completeness
-   `isComplete()`: Checks if provider, accuracy, time, and elapsed realtime are set.
-   `makeComplete()`: Fills missing essential fields with defaults (provider="", accuracy=100m, current time).

## Java-to-C++ Translation Guide

### Math Implementation
The `computeDistanceAndBearing` function is mathematically complex and critical. It must be ported precisely using `double` precision.
-   **Constants**: Ensure `a`, `b`, `f` match WGS84 definitions exactly.
-   **Math Functions**: Use `<cmath>` (`atan`, `tan`, `cos`, `sin`, `sqrt`, `atan2`).
-   **Loop**: Maintain the 20-iteration limit and convergence threshold (`1.0e-12`).

### Bitmask Handling
C++ implementation should use a bitset or manual bitwise operations on an integer member to track field presence, mirroring `mFieldsMask`.

### Thread Local Cache
In C++, `thread_local` storage can be used for the `BearingDistanceCache`.
```cpp
struct BearingDistanceCache {
    double mLat1, mLon1, mLat2, mLon2;
    float mDistance, mInitialBearing, mFinalBearing;
};
thread_local BearingDistanceCache sCache;
```

### Serialization
Replicate the `Parcelable` read/write order exactly for compatibility with Binder.
1.  Provider (String)
2.  Fields Mask (Int)
3.  Time (Long)
4.  Elapsed Realtime (Long)
5.  (If set) Elapsed Realtime Uncertainty (Double)
6.  Lat (Double)
7.  Lon (Double)
8.  (If set) Altitude (Double)
9.  (If set) Speed (Float)
10. (If set) Bearing (Float)
11. (If set) Horizontal Accuracy (Float)
12. (If set) Vertical Accuracy (Float)
13. (If set) Speed Accuracy (Float)
14. (If set) Bearing Accuracy (Float)
15. (If set) MSL Altitude (Double)
16. (If set) MSL Altitude Accuracy (Float)
17. Extras (Bundle)

## Edge Cases
-   **Bearing Range**: `setBearing` normalizes inputs to [0, 360). Negative inputs are wrapped. -0.0 is converted to 0.0.
-   **Coordinate Parsing**: The `convert(String)` method is robust against various formats but strictly expects `:` delimiters for Minutes/Seconds.
-   **Antipodal Points**: Geodesic calculations may fail to converge or produce ambiguous results for nearly antipodal points. The implementation has a break condition.

## Implementation Risks
-   **Floating Point Precision**: Ensure `double` is used for coordinates and intermediate geodesic calculations. `float` is used for accuracies and bearings/speeds.
-   **Extras Bundle**: `Bundle` is a generic Android container. In C++, this typically maps to `PersistableBundle` or a map of variants. Special care needed if complex objects are inside extras.
