# InputBinding - Reverse Engineering Documentation

## Executive Summary
Information given to an IME about a client binding (InputConnection token, UID, PID).

## Data Model
*   `mConnection`: Local InputConnection reference.
*   `mConnectionToken`: Binder token.
*   `mUid`, `mPid`.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
