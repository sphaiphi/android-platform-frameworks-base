# DisplayHashManager - Reverse Engineering Documentation

## Executive Summary
The system service manager (`Context.DISPLAY_HASH_SERVICE`) used to interact with the Display Hash framework. It provides methods to query supported algorithms and verify existing hashes.

## Architecture
*   **Service Wrapper**: Communicates with `WindowManagerService` (via `WindowManagerGlobal`) to perform operations.
*   **Singleton Cache**: Caches the set of supported hashing algorithms (`sSupportedHashAlgorithms`).

## Key Methods
*   **`getSupportedHashAlgorithms`**: Queries the window manager for algorithms supported by the hardware/system.
*   **`verifyDisplayHash`**: Sends a `DisplayHash` to the system for HMAC validation. Returns a `VerifiedDisplayHash` if valid.
*   **`setDisplayHashThrottlingEnabled`**: Test API to control rate-limiting of hash generation.

## Java-to-C++ Translation Guide
*   **Service Access**: Wraps `IWindowManager` calls.
*   **Caching**: Uses a static set with synchronized access.
