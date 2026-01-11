# Bundle - Reverse Engineering Documentation

## Executive Summary
`Bundle` is a subclass of `BaseBundle` optimized for passing data between Android components (Activities, Services) via Intents and Parcels. It adds support for `Parcelable` objects, which `BaseBundle` (and `PersistableBundle`) does not natively emphasize in the same way (though `BaseBundle` holds the map).

## Architecture Overview
-   **Inheritance**: `BaseBundle` -> `Bundle`.
-   **Role**: Type-safe container for IPC.
-   **Flags**: `FLAG_HAS_FDS`, `FLAG_HAS_BINDERS` track if the bundle contains active objects that require special handling during marshaling.

## Detailed Functionality
-   **Type-Safe Setters**: `putParcelable`, `putBinder`, `putBundle`, etc.
-   **Defusing**: Implements "defusing" logic (inherited from `BaseBundle`) to catch exceptions during unparceling of bad data without crashing the process.
-   **Filter**: `hasFileDescriptors()` and `hasBinders()` scan the map or the parcelled data to warn about active objects.

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: `android::os::Bundle` in `frameworks/native/libs/binder`.
-   **Parcelling**:
    -   Writes length.
    -   Writes Magic (`0x4C444E42`).
    -   Writes Map content.
    -   Writes `hasIntent` boolean (optimization).

## Implementation Risks
-   **ClassLoader**: `Bundle` is sensitive to ClassLoaders. When unparceling custom Parcelables, the correct ClassLoader must be set via `setClassLoader()`, otherwise `ClassNotFoundException` occurs.
