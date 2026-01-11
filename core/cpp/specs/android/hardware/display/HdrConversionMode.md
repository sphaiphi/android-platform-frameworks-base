# HdrConversionMode - Reverse Engineering Documentation

## Executive Summary
`HdrConversionMode` defines how the system handles HDR content conversion (e.g., forcing SDR to HDR, or restricting HDR output).

## Data Model
- `mConversionMode`:
    - `UNSUPPORTED`
    - `PASSTHROUGH` (No conversion)
    - `SYSTEM` (System decides)
    - `FORCE` (User forced)
- `mPreferredHdrOutputType`: `HdrType` (Dolby Vision, HDR10, etc.). Only valid if mode is `FORCE`.

## Validation
- Constructor throws `IllegalArgumentException` if you try to set a preferred type when mode is PASSTHROUGH or UNSUPPORTED.

## Java-to-C++ Translation Guide
- **Parcelable**: Standard mapping.
- **Logic**: Replicate the validation logic in the constructor to ensure valid states.
