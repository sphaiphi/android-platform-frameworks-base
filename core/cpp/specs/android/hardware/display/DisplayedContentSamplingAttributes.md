# DisplayedContentSamplingAttributes - Reverse Engineering Documentation

## Executive Summary
`DisplayedContentSamplingAttributes` describes the capabilities of the hardware display sampling engine (e.g., what format and dataspace it samples in).

## Data Model
- `mPixelFormat`: `int` (HAL pixel format).
- `mDataspace`: `int` (HAL dataspace).
- `mComponentMask`: `int` (Bitmask of supported channels).

## Java-to-C++ Translation Guide
- Maps directly to hardware capabilities structures used in SurfaceFlinger / HWC.
