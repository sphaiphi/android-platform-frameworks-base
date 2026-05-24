# VerifiedInputEvent - Reverse Engineering Documentation

## Executive Summary
`VerifiedInputEvent` is the base class for "Verified" versions of input events (e.g., `VerifiedKeyEvent`, `VerifiedMotionEvent`). These events contain only the subset of data that has been cryptographically signed or otherwise verified by the system's `InputDispatcher`, ensuring they are authentic and haven't been spoofed by a third-party application.

## Architecture Overview
*   **Role**: Trusted data carrier for secure input.
*   **Source**: Created by the `InputManager` service.
*   **Trust Model**: Contains only immutable, system-verified properties.

## Data Model
*   **`mDeviceId`**: The hardware device ID.
*   **`mEventTimeNanos`**: Verified timestamp.
*   **`mSource`**: Verified input source.
*   **`mDisplayId`**: Verified target display.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::VerifiedInputEvent`.
*   **Parceling**: Bit-for-bit parity with `frameworks/native/libs/input/Input.cpp` is mandatory.

## Implementation Risks
*   **Subset Limitation**: Applications must be aware that a `VerifiedInputEvent` contains significantly less data than a standard `InputEvent`. For example, a `VerifiedMotionEvent` only contains data for the primary pointer.
