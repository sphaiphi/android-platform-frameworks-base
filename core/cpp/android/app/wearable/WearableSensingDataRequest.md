# WearableSensingDataRequest - Reverse Engineering Documentation

## Executive Summary
`WearableSensingDataRequest` is a data class (Parcelable) that encapsulates a request for data from the wearable sensing service. It contains a data type identifier and a bundle of request details. It also enforces size limits on the request.

## Architecture Overview
-   **Type**: `final class`, `Parcelable`
-   **Package**: `android.app.wearable`
-   **Pattern**: Immutable value object with Builder.

## Detailed Functionality

### Constants
-   `MAX_REQUEST_SIZE = 200`: Maximum size in bytes when parcelled (soft limit check).
-   `RATE_LIMIT_WINDOW_SIZE = 1 minute`: Window for rate limiting.
-   `RATE_LIMIT = 30`: Max requests per window.

### Fields
-   `mDataType` (int): Identifier for the type of data requested.
-   `mRequestDetails` (PersistableBundle): Key-value pairs detailing the request.

### Logic
-   **Parcelling**: Writes int and TypedObject (Bundle).
-   **Size Check**: `getDataSize()` marshals the object to a temporary Parcel to calculate size.
-   **Expansion**: `toExpandedString()` forces unparcelling of the bundle for logging visibility.

## API Reference
-   `int getDataType()`
-   `PersistableBundle getRequestDetails()`
-   `int getDataSize()`: Returns parcelled size.
-   `static int getMaxRequestSize()`
-   `static Duration getRateLimitWindowSize()`
-   `static int getRateLimit()`

### Builder
-   `Builder(int dataType)`
-   `setRequestDetails(PersistableBundle)`
-   `build()`

## Java-to-C++ Translation Guide
-   **Parcelable**: Implement `android::Parcelable` interface in C++.
-   **PersistableBundle**: Use C++ equivalent.
-   **Size Calculation**: C++ `Parcel` class has `dataSize()`.
-   **Immutability**: Make fields `const` in C++.

## Edge Cases
-   **Size Limit**: The class enables construction larger than `MAX_REQUEST_SIZE`, but notes system will reject it. C++ implementation of the service should enforce this rejection.
