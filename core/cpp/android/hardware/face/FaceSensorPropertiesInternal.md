# FaceSensorPropertiesInternal - Reverse Engineering Documentation

## Executive Summary
`FaceSensorPropertiesInternal` is the internal (system-side) representation of face sensor properties. It extends `SensorPropertiesInternal` and implements `Parcelable`. It includes flags for face detection support and self-illumination.

## Architecture Overview
- **Inheritance**: Extends `android.hardware.biometrics.SensorPropertiesInternal`.
- **Usage**: Used by `FaceService` and passed to `FaceManager`.

## Fields
- `sensorType`: `int`.
- `supportsFaceDetection`: `boolean`.
- `supportsSelfIllumination`: `boolean`.

## Java-to-C++ Translation Guide
- **Parcelable**: Inherits parceling from superclass, then writes its own fields. C++ implementation must mirror this order (Super fields first, then subclass fields).
- **Structure**:
  ```cpp
  struct FaceSensorPropertiesInternal : public SensorPropertiesInternal {
      int32_t sensorType;
      bool supportsFaceDetection;
      bool supportsSelfIllumination;
  };
  ```

