# GeomagneticField - Reverse Engineering Documentation

## Executive Summary
`GeomagneticField` is a mathematical model used to estimate the Earth's magnetic field at a given location (latitude, longitude, altitude) and time. Its primary use is calculating the magnetic declination (the difference between magnetic north and true north).

## Architecture Overview
The class implements the **World Magnetic Model (WMM-2020)**. It uses spherical harmonic expansion with associated Legendre functions. It is a standalone utility class with no external service dependencies.

## Detailed Functionality

### Calculation Flow
1. **Constructor**: Receives geodetic coordinates and time.
2. **Coordinate Conversion**: `computeGeocentricCoordinates` converts WGS84 coordinates to geocentric coordinates.
3. **Harmonic Expansion**:
    - Uses `G_COEFF` and `H_COEFF` (Gauss coefficients).
    - Updates coefficients for the current time using `DELTA_G` and `DELTA_H` (secular variation).
    - Uses a `LegendreTable` to compute Gauss-normalized associated Legendre functions.
    - Computes components of the potential function's gradient.
4. **Coordinate Rotation**: Rotates the geocentric magnetic field vector back to the geodetic frame (North, East, Down).

### Computed Values
- `getX()`: Northward component (nT).
- `getY()`: Eastward component (nT).
- `getZ()`: Downward component (nT).
- `getDeclination()`: Difference between true north and magnetic north (degrees).
- `getInclination()`: Angle of the field with the horizontal (degrees).
- `getFieldStrength()`: Total intensity (nT).

## Data Model
- **Constants**: Semi-major/minor axis of Earth (WGS84), reference radius.
- **Tables**: `G_COEFF`, `H_COEFF`, `DELTA_G`, `DELTA_H` (13x13 matrices).
- **LegendreTable**: Internal utility for recursive calculation of Legendre polynomials.

## API Reference
- `public GeomagneticField(float gdLatitudeDeg, float gdLongitudeDeg, float altitudeMeters, long timeMillis)`
- `public float getX()`, `public float getY()`, `public float getZ()`
- `public float getDeclination()`
- `public float getInclination()`
- `public float getHorizontalStrength()`
- `public float getFieldStrength()`

## Java-to-C++ Translation Guide
- **Math**: Heavily dependent on `Math.sin`, `Math.cos`, `Math.sqrt`, `Math.atan2`, `Math.pow`. Use `<cmath>`.
- **Arrays**: `float[][]` -> `std::vector<std::vector<float>>` or static arrays for better performance.
- **Base Time**: Calculation of `yearsSinceBase` needs careful handling of millisecond epoch time.

## Test Cases & Validation
- Compare output against official WMM-2020 test values provided by NOAA.
- Verify declination for known locations (e.g., London, New York).

## Implementation Risks
- Precision issues with floating-point calculations over many iterations.
- Model validity: Currently valid until 2025. Needs update periodically.
