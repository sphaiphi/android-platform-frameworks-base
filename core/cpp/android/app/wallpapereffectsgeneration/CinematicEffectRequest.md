# CinematicEffectRequest - Reverse Engineering Documentation

## Executive Summary
`CinematicEffectRequest` represents a request sent to the wallpaper effects generation service. It encapsulates the source image (Bitmap) and a unique task identifier.

## Architecture Overview
- **Package**: `android.app.wallpapereffectsgeneration`
- **Implements**: `Parcelable`
- **Role**: Request DTO.

## Detailed Functionality

**Purpose**: Transmit an image to be processed.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mTaskId` | `String` | Unique ID for the request. |
| `mBitmap` | `Bitmap` | The source image to process. |

## Java-to-C++ Translation Guide

- **Bitmap Handling**:
  - Java `Bitmap` -> C++ `android::graphics::Bitmap` (often wrapping `AHardwareBuffer` or `SkBitmap`).
  - When parcelling, `Bitmap` has complex logic involving shared memory (Ashmem) for large images. The C++ implementation must utilize the standard Android native bitmap parceling functions to ensure compatibility.
- **String**: Standard `String16` or UTF-8 string.

## Implementation Risks
- **Bitmap Parceling**: Incorrectly implementing the Bitmap read/write in C++ will cause the transaction to fail or crash the receiving Java service. Use existing platform helpers.
