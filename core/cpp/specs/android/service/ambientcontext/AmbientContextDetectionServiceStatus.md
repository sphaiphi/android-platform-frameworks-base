# AmbientContextDetectionServiceStatus - Reverse Engineering Documentation

## Executive Summary
`AmbientContextDetectionServiceStatus` is a data class (Parcelable) that reports the status of the `AmbientContextDetectionService` to the client. It conveys whether the service is available, denied access, etc.

## Data Model

### Fields
*   `mStatusCode`: `int` (Annotated with `@StatusCode`) - The status code (e.g., SUCCESS, ACCESS_DENIED).
*   `mPackageName`: `String` (NonNull) - The package name associated with the status.

### Constants
*   `STATUS_RESPONSE_BUNDLE_KEY`: `"android.app.ambientcontext.AmbientContextServiceStatusBundleKey"`

## API Reference

### Getters
*   `int getStatusCode()`: Returns the status code.
*   `String getPackageName()`: Returns the package name.

### Builder (`AmbientContextDetectionServiceStatus.Builder`)
*   **Constructor**: `Builder(String packageName)`
*   **Methods**:
    *   `setStatusCode(int value)`: Sets the status code.
    *   `build()`: Returns the instance. defaults status to `STATUS_UNKNOWN` if not set.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Implements `Parcelable`.
*   **C++**: Should implement `android::Parcelable`.
    *   `writeToParcel`: Writes Int and String.
    *   `readFromParcel`: Reads Int and String.

### Enums/Constants
*   Uses `AmbientContextManager.StatusCode` int defs. C++ should likely map these to an enum.

## Implementation Notes
*   Immutable object pattern.
*   Builder pattern used.
*   Validation for `StatusCode` and `NonNull` package name.
