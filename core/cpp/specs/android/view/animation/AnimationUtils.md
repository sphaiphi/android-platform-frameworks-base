# AnimationUtils - Reverse Engineering Documentation

## Executive Summary
Utility class for loading animations and interpolators from XML resources, and for managing the animation clock.

## Key Algorithms
*   **`currentAnimationTimeMillis`**: Returns the current time used for animation steps. Critical for synchronizing animations. Thread-local clock state.
*   **`loadAnimation`**: XML parser for inflating `Animation` objects.
*   **`loadInterpolator`**: XML parser for inflating `Interpolator` objects.

## Java-to-C++ Translation Guide
*   **XML Parsing**: Relies on `XmlPullParser`. C++ would need a resource inflation system (like Android's AssetManager/Aapt logic ported to native).
*   **Thread Local**: Uses `ThreadLocal` for animation clock. C++ uses `thread_local`.
