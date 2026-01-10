# InputEvent - Reverse Engineering Documentation

## Executive Summary
`InputEvent` is the abstract base class for all input events in the system. It defines common properties for events like `KeyEvent` and `MotionEvent`, such as the source device, the event time, and the sequence number.

## Data Model

### Core Fields
*   **`mDeviceId`**: The ID of the device that generated the event.
*   **`mSource`**: The specific input source (e.g., `SOURCE_TOUCHSCREEN`).
*   **`mEventTime`**: The timestamp of the event.
*   **`mSeq`**: A process-local unique sequence number used for ordering.

## Detailed Functionality
*   **Consistency**: Works with `InputEventConsistencyVerifier` to ensure that event streams (e.g., Down/Move/Up) are logically sound.
*   **Pooling**: Supports a recycling mechanism to minimize memory pressure.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::InputEvent`.
*   **Polymorphism**: In C++, use a base class with virtual methods for `getDeviceId()`, etc.
*   **Parceling**: Uses a "Token" (`PARCEL_TOKEN_KEY_EVENT` or `PARCEL_TOKEN_MOTION_EVENT`) at the start of the parcel to identify the subclass.

## Implementation Risks
*   **Tainting**: The `isTainted` flag is used to mark events that have been modified or are inconsistent; C++ logic must respect this to prevent erratic behavior in the input pipeline.
