# AmbientContextDetectionResult - Reverse Engineering Documentation

## Executive Summary
`AmbientContextDetectionResult` is a data class (Parcelable) that encapsulates the result of an ambient context detection event. It contains a list of detected events and the target package name.

## Data Model

### Fields
*   `mEvents`: `List<AmbientContextEvent>` (NonNull) - The list of detected events.
*   `mPackageName`: `String` (NonNull) - The package name the result is intended for.

### Constants
*   `RESULT_RESPONSE_BUNDLE_KEY`: `"android.app.ambientcontext.AmbientContextDetectionResultBundleKey"` - Key used when bundling this object for `RemoteCallback`.

## API Reference

### Getters
*   `List<AmbientContextEvent> getEvents()`: Returns the list of events.
*   `String getPackageName()`: Returns the package name.

### Builder (`AmbientContextDetectionResult.Builder`)
*   **Constructor**: `Builder(String packageName)`
*   **Methods**:
    *   `addEvent(AmbientContextEvent value)`: Adds a single event.
    *   `addEvents(List<AmbientContextEvent> values)`: Adds a list of events.
    *   `clearEvents()`: Clears the list.
    *   `build()`: Returns the `AmbientContextDetectionResult` instance.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Implements `Parcelable`.
*   **C++**: Should implement `android::Parcelable`.
    *   `writeToParcel`: Writes List (ParcelableList) and String.
    *   `readFromParcel`: Reads List and String.

### Dependencies
*   Depends on `AmbientContextEvent` (likely in `android.app.ambientcontext` namespace).

## Implementation Notes
*   Immutable object pattern.
*   Builder pattern for construction.
*   Input validation (NonNull) is enforced.
