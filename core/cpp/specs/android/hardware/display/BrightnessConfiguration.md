# BrightnessConfiguration - Reverse Engineering Documentation

## Executive Summary
`BrightnessConfiguration` represents the configuration for the adaptive brightness algorithm. It defines the "Brightness Curve" (mapping from Lux to Nits) and per-application corrections. It supports XML serialization/deserialization for persistence.

## Architecture Overview
- **Type**: Immutable Data Object / Parcelable / XML Serializable
- **Package**: `android.hardware.display`
- **Key Components**:
    - **Curve**: `float[] mLux`, `float[] mNits`.
    - **Corrections**: Maps for Package Name -> `BrightnessCorrection` and Category -> `BrightnessCorrection`.
    - **Short Term Model**: Configurable timeouts and multipliers for user interaction resets.

## Detailed Functionality

### The Brightness Curve
- **Lux**: Ambient light levels (strictly increasing, starting at 0).
- **Nits**: Screen brightness (monotonic).
- Interpolation is implied to happen between these points by the consumer (DisplayPowerController).

### Corrections
- Allows modifying the brightness based on the foreground app.
- **By Package**: e.g., "com.example.game" -> scale brightness by 1.2.
- **By Category**: e.g., `CATEGORY_GAME` -> scale brightness by 1.2.

### Serialization
- **Parcelable**: Efficient IPC.
- **XML**: For storage on disk (`saveToXml`/`loadFromXml`).
    - Tags: `brightness-curve`, `brightness-point`, `brightness-corrections`, `brightness-correction`, `brightness-params`.

## Java-to-C++ Translation Guide

### Data Structures
- `std::vector<float>` for Lux/Nits.
- `std::map<std::string, BrightnessCorrection>` for package corrections.
- `std::map<int, BrightnessCorrection>` for category corrections.

### XML Handling
- Java uses `TypedXmlSerializer`/`TypedXmlPullParser`. C++ will need an XML library (e.g., `libxml2` or Android's internal XML parsing helpers) to read/write the same format.

### Validation
- **Monotonicity**: Lux must be strictly increasing. Nits must be monotonic (non-decreasing).
- **Start Point**: Lux[0] must be 0.
- **Ranges**: No negative numbers.

### Constants
- `SHORT_TERM_TIMEOUT_UNSET = -1`.

## Risks
- **XML Format Compatibility**: C++ implementation must match the XML tag/attribute names exactly to share config files with Java.
