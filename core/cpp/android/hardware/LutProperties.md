# LutProperties - Reverse Engineering Documentation

## Executive Summary
`LutProperties` provides information about the Lookup Table (LUT) capabilities of the device hardware. It exposes the supported dimensions, size, and sampling keys for color correction LUTs handled by the Hardware Composer (HWC).

## Architecture Overview
This is a simple data class used by `OverlayProperties` to describe hardware-accelerated LUT support. It is flagged with `FLAG_LUTS_API`.

## Detailed Functionality

### Properties
- **Dimension**: Whether the hardware supports 1D or 3D LUTs.
- **Size**: The resolution of the LUT for each dimension.
- **Sampling Keys**: The criteria used for LUT sampling (e.g., `RGB`, `MAX_RGB`, `CIE_Y`).

## Data Model
- **SamplingKey (int)**:
    - `SAMPLING_KEY_RGB` (0)
    - `SAMPLING_KEY_MAX_RGB` (1)
    - `SAMPLING_KEY_CIE_Y` (2)
- **Dimension (int)**:
    - `ONE_DIMENSION` (1)
    - `THREE_DIMENSION` (3)

## API Reference
- `public int getDimension()`
- `public int getSize()`
- `public int[] getSamplingKeys()`

## Java-to-C++ Translation Guide
- **Class**: `class LutProperties` -> `struct LutProperties`.
- **Initialization**: Constructor is private, used by native code. C++ needs to instantiate this via JNI to pass it up to Java.

## Implementation Risks
- Desynchronization of sampling key constants between Java and HWC HAL.
