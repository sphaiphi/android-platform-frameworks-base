# VerifiedMotionEvent - Reverse Engineering Documentation

## Executive Summary
`VerifiedMotionEvent` is a Parcelable data class containing a subset of a `MotionEvent` that has been authenticated by the system. it focus on the primary pointer's position and the core action state to provide a trusted baseline for motion analysis.

## Data Model
*   **`mRawX` / `mRawY`**: The authenticated physical coordinates of the primary pointer.
*   **`mActionMasked`**: The authenticated action (e.g., `ACTION_DOWN`, `ACTION_UP`).
*   **`mDownTimeNanos`**: The authenticated start time of the gesture.

## Detailed Functionality
*   **Inheritance**: Extends `VerifiedInputEvent`.
*   **Verification**: Allows checking authenticated flags like `FLAG_WINDOW_IS_OBSCURED`.

## Java-to-C++ Translation Guide
*   **Primary Type**: Wrap `android::VerifiedMotionEvent`.
*   **Parceling**: Serialization must match the native implementation in `frameworks/native/libs/input/`.

## Implementation Risks
*   **Single Pointer**: Unlike a full `MotionEvent`, this class typically only verifies the state of the first pointer, making it unsuitable for multi-touch verification.
