# RuntimeAppOpAccessMessage - Reverse Engineering Documentation

## Executive Summary
`RuntimeAppOpAccessMessage` is a data class used to track and report runtime permission access events (AppOps). It captures metadata about which application accessed a specific operation, which feature was used, the sampling strategy employed, and a descriptive message (which may include a stack trace for synchronous operations). This is used for privacy auditing and logging.

## Architecture Overview
- **Structure**:
    - `mUid`: UID of the accessing package.
    - `mOpCode`: The specific AppOp operation (e.g., `OP_COARSE_LOCATION`).
    - `mPackageName`: Name of the accessing app.
    - `mAttributionTag`: The specific feature or attribution within the app.
    - `mMessage`: Details about the access event.
    - `mSamplingStrategy`: How the event was selected for collection.
- **Inheritance**: Implements `Parcelable`.
- **Immutable**: Once created, the object's state cannot be changed.

## Detailed Functionality

### AppOp Identification
**Purpose**: Mapping internal codes to readable names.
**Mechanism**: `getOp()` uses `AppOpsManager.opToPublicName(mOpCode)` to return a standard string (like "android:fine_location").

### Validation
**Purpose**: Ensuring data integrity.
**Logic**: The constructor uses `AnnotationValidations` to enforce ranges (e.g., `uid >= 0`) and non-null constraints.

## API Reference
- `public int getUid()`: Returns accessor UID.
- `public String getPackageName()`: Returns package name.
- `public String getOp()`: Returns human-readable op name.
- `public int getSamplingStrategy()`: Returns the audit strategy.

## Java-to-C++ Translation Guide
- **AppOps Registry**: Map `mOpCode` to the native `AppOpsManager` constants in C++.
- **Immutable Data**: Use `const` members in a C++ `struct`.
- **Parceling**: Implement `writeToParcel` and `readFromParcel` using `libbinder`.

## Implementation Risks
- **OpCode Consistency**: The `mOpCode` must match the system's AppOp registry. Any discrepancy will lead to incorrect privacy auditing.
- **Message Size**: Stack traces in `mMessage` can be quite large. C++ implementations should be mindful of binder transaction limits.
