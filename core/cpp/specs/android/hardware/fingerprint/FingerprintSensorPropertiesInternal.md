# FingerprintSensorPropertiesInternal - Reverse Engineering Documentation

## Executive Summary
`FingerprintSensorPropertiesInternal` is the internal (system-side) representation of fingerprint sensor properties. It extends `SensorPropertiesInternal` and implements `Parcelable`. Includes flags for HAL controls (illumination) and sensor locations.

## Architecture Overview
- **Inheritance**: Extends `android.hardware.biometrics.SensorPropertiesInternal`.
- **Usage**: Used by `FingerprintService` and passed to `FingerprintManager`.

## Fields
- `sensorType`: `int`.
- `halControlsIllumination`: `boolean`.
- `halHandlesDisplayTouches`: `boolean`.
- `mSensorLocations`: `List<SensorLocationInternal>`.

## Helper Methods
- `isAnyUdfpsType()`, `isUltrasonicUdfps()`, `isOpticalUdfps()`, `isAnySidefpsType()`.
- `getLocation(displayId)`.

## Java-to-C++ Translation Guide
- **Parcelable**: Match serialization order.
- **Structure**:
  ```cpp
  struct FingerprintSensorPropertiesInternal : public SensorPropertiesInternal {
      int32_t sensorType;
      bool halControlsIllumination;
      bool halHandlesDisplayTouches;
      std::vector<SensorLocationInternal> sensorLocations;
  };
  ```

