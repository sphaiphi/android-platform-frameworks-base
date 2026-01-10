# CameraStreamStats - Reverse Engineering Documentation

## Executive Summary
`CameraStreamStats` is a hidden (`@hide`) parcelable class that captures statistics for an individual camera stream. It includes configuration details (width, height, format), performance metrics (latency, error counts), and histograms for analyzing jitter and latency.

## Architecture Overview
This class is a component of `CameraSessionStats`. It provides granular data for each stream active in a camera session, supporting deep performance analysis and telemetry.

## Detailed Functionality

### Metrics
- **Configuration**: `mWidth`, `mHeight`, `mFormat`, `mDataSpace`, `mColorSpace`, `mDynamicRangeProfile`, `mStreamUseCase`.
- **Performance**: `mMaxPreviewFps`, `mStartLatencyMs`.
- **Resource Usage**: `mUsage`, `mMaxHalBuffers`, `mMaxAppBuffers`.
- **Errors**: `mRequestCount`, `mErrorCount`.
- **Analysis**: `mHistogramType`, `mHistogramBins` (float array), `mHistogramCounts` (long array).

### Histograms
- Currently supports `HISTOGRAM_TYPE_CAPTURE_LATENCY` (1).
- Bins and counts allow the proxy to reconstruct probability distributions of latency.

## Data Model
- `HISTOGRAM_TYPE_UNKNOWN` (0)
- `HISTOGRAM_TYPE_CAPTURE_LATENCY` (1)

## API Reference (Internal)
- Getters for all configuration and performance fields.

## Java-to-C++ Translation Guide
- **Class**: `class CameraStreamStats` -> `struct CameraStreamStats`.
- **Arrays**: `float[]`, `long[]` -> `std::vector<float>`, `std::vector<int64_t>`.
- **Constants**: Static ints -> `enum class`.

## Implementation Risks
- Memory overhead of histogram arrays if many streams are active.
- Consistency of `mDataSpace` and `mFormat` values with their native counterparts in `system/graphics.h`.
