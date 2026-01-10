# CameraCompatTaskInfo - Reverse Engineering Documentation

## Executive Summary
`CameraCompatTaskInfo` is a Parcelable data structure holding camera compatibility state for a task, specifically regarding freeform windowing rotation adjustments.

## Architecture Overview
*   **Type**: Parcelable.
*   **Usage**: Part of `AppCompatTaskInfo`.

## Detailed Functionality
*   **Mode**: `freeformCameraCompatMode` (Portrait in Landscape, Landscape in Portrait, etc.).
*   **Helper**: `getDisplayRotationFromCameraCompatMode` calculates the emulated rotation.

## Java-to-C++ Translation Guide
*   Simple struct mapping.

## Implementation Risks
*   None.
