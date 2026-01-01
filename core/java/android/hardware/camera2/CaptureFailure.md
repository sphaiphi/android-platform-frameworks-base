# CaptureFailure.java - Reverse Engineering Documentation

## Executive Summary
`CaptureFailure` is a report produced when a `CaptureRequest` fails to result in a successful image capture or metadata generation. It provides context about why the failure occurred.

## Architecture Overview
- **Type**: Data Class
- **Package**: `android.hardware.camera2`.

## Data Model
-   `mRequest`: The request that failed.
-   `mReason`: 
    -   `REASON_ERROR` (0): Framework/Hardware error.
    -   `REASON_FLUSHED` (1): Aborted by user.
-   `mWasImageCaptured`: Boolean indicating if the sensor actually captured data (buffers might still be available even if metadata failed).
-   `mSequenceId`: Capture sequence ID.
-   `mFrameNumber`: Monotonic frame identifier.
-   `mErrorPhysicalCameraId`: Specific physical camera that failed in a logical camera setup.

## Java-to-C++ Translation Guide
Simple struct in C++.

```cpp
struct CaptureFailure {
    CaptureRequest request;
    int reason;
    bool wasImageCaptured;
    int sequenceId;
    int64_t frameNumber;
    std::string physicalCameraId;
};
```
