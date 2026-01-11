# Environment - Reverse Engineering Documentation

## Executive Summary
`Environment` provides access to environment variables and standard directory paths (like External Storage, Data Directory, System Root). It centralizes path resolution for the Android filesystem hierarchy.

## Architecture Overview
-   **Role**: Path Provider / Static Config.
-   **Mechanism**: Wraps `System.getenv()` and constructs `File` objects.
-   **User Separation**: `UserEnvironment` inner class handles per-user external storage paths.

## API Reference
-   `getRootDirectory()`: `/system`
-   `getDataDirectory()`: `/data`
-   `getDownloadCacheDirectory()`: `/cache`
-   `getExternalStorageDirectory()`: Primary shared storage (e.g. `/sdcard` or `/storage/emulated/0`).
-   `getExternalStoragePublicDirectory(String type)`: Standard folders (DCIM, Pictures, Music).
-   `buildExternalStorageAppCacheDirs(package)`: App-specific paths on external storage.

## Java-to-C++ Translation Guide
-   **Environment Variables**: `getenv("ANDROID_DATA")`, `getenv("EXTERNAL_STORAGE")`.
-   **Hardcoded Paths**: Android filesystem layout is fairly static, but using the environment variables is safer.
-   **C++ Equivalent**: Often hardcoded in `init.rc` or `libcutils`. Use `getenv` in user-space C++ apps.

## Implementation Risks
-   **Scoped Storage**: Accessing `getExternalStorageDirectory` directly is deprecated/restricted in newer Android versions. Apps should use `Context` methods or `MediaStore`.
