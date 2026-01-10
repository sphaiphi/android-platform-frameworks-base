# BrightnessCorrection - Reverse Engineering Documentation

## Executive Summary
`BrightnessCorrection` is a wrapper for a brightness adjustment strategy. Currently, it supports only one implementation: `ScaleAndTranslateLog`. This strategy applies a mathematical formula to the brightness value.

## Architecture Overview
- **Type**: Immutable Data Object / Parcelable / XML Serializable
- **Pattern**: Strategy / Union (Simulated via private interface `BrightnessCorrectionImplementation`).
- **Implementations**:
    - `ScaleAndTranslateLog` (The only active one).

## Detailed Functionality

### ScaleAndTranslateLog
**Formula**: `y = exp(scale * ln(x) + translate)`
- `x`: Input brightness.
- `y`: Output brightness.
- **Constraints**:
    - `scale`: [0.5, 2.0]
    - `translate`: [-0.6, 0.7]

### Serialization
- **Parcel**: Writes an int type header (`SCALE_AND_TRANSLATE_LOG = 1`) then the implementation data.
- **XML**: Tag `<scale-and-translate-log scale="..." translate="..." />`.

## Java-to-C++ Translation Guide
- **Class Structure**: A base class (or variant) `BrightnessCorrection` with a specific subtype `ScaleAndTranslateLog`.
- **Math**: Use `std::log` and `std::exp`. Ensure float precision matches.
- **Clamping**: Important to replicate the constraints on `scale` and `translate` during construction.

## Data Model
- `ScaleAndTranslateLog`:
    - `float mScale`
    - `float mTranslate`

## Test Cases
- `apply(brightness)`:
    - Input: 100. Scale: 1.0, Translate: 0.0 -> `exp(ln(100))` = 100.
    - Input: 100. Scale: 0.5, Translate: 0.0 -> `exp(0.5 * ln(100))` = `sqrt(100)` = 10.
