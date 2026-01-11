# GestureLibraries - Reverse Engineering Documentation

## Executive Summary
`GestureLibraries` is a factory class for creating `GestureLibrary` instances from various sources (files, resource IDs, private app storage).

## Architecture Overview
- **Factory Pattern**: Static methods (`fromFile`, `fromRawResource`, etc.) return specific `GestureLibrary` implementations.
- **Implementations**:
  - `FileGestureLibrary`: Persists gestures to a file.
  - `ResourceGestureLibrary`: Read-only library loaded from Android resources (`res/raw`).

## Detailed Functionality
- `fromFile(String/File)`: Creates a library backed by a filesystem path.
- `fromRawResource(Context, int)`: Creates a read-only library from an APK resource.
- `save()` / `load()`: Delegates to `GestureStore` with appropriate Input/Output streams.

## Java-to-C++ Translation Guide
- **File I/O**: Use standard C++ file streams (`std::fstream`) or POSIX file descriptors.
- **Resources**: The concept of `RawResource` is Android-specific. In a pure C++ context, this might map to loading assets from a specific directory or memory buffer.

## Source Reference
Defined in `GestureLibraries.java`.
