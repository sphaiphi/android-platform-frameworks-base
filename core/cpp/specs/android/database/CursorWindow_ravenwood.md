# CursorWindow_ravenwood - Reverse Engineering Documentation

## Executive Summary
`CursorWindow_ravenwood` is a *host-side* (non-Android device) implementation of `CursorWindow`'s native methods. It is used for unit testing framework code on a desktop JVM where the actual Android Native (C++) `CursorWindow` implementation is missing.

## Architecture
*   **Storage**: In-memory `ArrayList<Row>`.
*   **Row**: `String[] mFields`, `int[] mTypes`.
*   **Logic**: Re-implements `nativePutString`, `nativeGetString`, etc., using Java objects.

## Relevance to C++ Team
*   **Ignore**: This is a test double. The actual C++ implementation is in `frameworks/base/libs/androidfw/CursorWindow.cpp` (or similar location in `core/jni`). This file should *not* be ported to the Android device C++ codebase.
