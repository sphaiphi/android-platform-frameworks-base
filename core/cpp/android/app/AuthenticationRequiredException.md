# AuthenticationRequiredException - Reverse Engineering Documentation

## Executive Summary
`AuthenticationRequiredException` is a `SecurityException` thrown when an operation requires user authentication (e.g., confirming credentials) to proceed. It contains a `PendingIntent` that the app can launch to recover/prompt the user.

## Architecture Overview
*   **Inheritance**: `SecurityException` -> `RuntimeException` -> `Exception`.
*   **Implements**: `Parcelable`.

## Detailed Functionality
*   **Fields**:
    *   `mUserAction`: `PendingIntent` to trigger authentication UI.
*   **Usage**: Thrown by content providers or system services.

## Java-to-C++ Translation Guide
*   Map to a custom exception class in C++.
*   Ideally, exceptions shouldn't be used for control flow across IPC boundaries in C++ (Binder doesn't propagate C++ exceptions directly like Java). This usually maps to a specific error code return with side-channel data (the PendingIntent).

## Implementation Risks
*   **Exception Propagation**: Ensure the Binder transport correctly marshals this exception if emulating Java Binder behavior.
