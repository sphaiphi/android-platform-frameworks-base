# FrameRateCategoryRate - Reverse Engineering Documentation

## Executive Summary
`FrameRateCategoryRate` is a Parcelable data class used to manage suggested frame rates for two primary categories: `Normal` and `High`. It is used by the system to communicate recommended rendering speeds to applications based on the current display configuration.

## Data Model
*   **`mNormal`**: `float` - The suggested frame rate for standard content (e.g., 60Hz).
*   **`mHigh`**: `float` - The suggested frame rate for high-performance content (e.g., 90Hz or 120Hz).

## Detailed Functionality
*   **Parcelable**: Facilitates communication between `DisplayManagerService` and client processes.
*   **Getters**: `getNormal()` and `getHigh()` provide access to the rates.

## Java-to-C++ Translation Guide
*   **Structure**: In C++, this can be a simple `struct` or a class with `float` members.
*   **Parceling**: Standard data marshalling via `android::Parcel`.

## Implementation Risks
*   **Invalid Rates**: System must ensure that `mHigh` is always greater than or equal to `mNormal` to prevent logic errors in the rendering pipeline.
