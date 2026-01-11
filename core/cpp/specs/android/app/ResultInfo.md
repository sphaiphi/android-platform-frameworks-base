# ResultInfo - Reverse Engineering Documentation

## Executive Summary
`ResultInfo` is an internal data class used by the `ActivityManager` to encapsulate the result of an activity execution (e.g., when an activity is started with `startActivityForResult`). it carries the request code, result code, returned data (Intent), and identification of the source and target.

## Architecture Overview
- **Structure**:
    - `mResultWho`: String identifier for the result requester.
    - `mRequestCode`: The original request code passed to `startActivityForResult`.
    - `mResultCode`: The result code set by the finished activity (e.g., `RESULT_OK`, `RESULT_CANCELED`).
    - `mData`: The `Intent` containing the result data.
    - `mCallerToken`: The `IBinder` token of the calling activity.
- **Inheritance**: Implements `Parcelable`.

## Detailed Functionality

### Serialization
**Purpose**: Enables the transfer of activity results between the target process, system server, and source process.
**Mechanism**: Standard `Parcel` reading and writing. It includes a strong binder for the `mCallerToken`.

### Equality and Hashing
**Purpose**: Comparing results for delivery or tracking.
**Logic**: Checks all fields, utilizing `Intent.filterEquals` for the data intent to ignore extras in the comparison.

## API Reference
- `public final String mResultWho`: Requester ID.
- `public final int mRequestCode`: Original ID.
- `public final int mResultCode`: Outcome code.
- `public final Intent mData`: Result payload.

## Java-to-C++ Translation Guide
- **Data Struct**: Map to a simple C++ `class`.
- **Intent**: Use `android::content::Intent` in the native layer.
- **Parceling**: Use `libbinder`'s `Parcel::writeStrongBinder` for the caller token.

## Implementation Risks
- **Identity**: Ensure `Intent.filterEquals` logic is correctly replicated if the native layer performs comparisons.
- **Token Validity**: The `mCallerToken` must be valid and tracked to ensure the result is delivered to the correct activity instance.
