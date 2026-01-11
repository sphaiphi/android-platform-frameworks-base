# StrictJarManifest - Reverse Engineering Documentation

## Executive Summary
Provides read/write access to JAR manifests (main attributes and entry attributes). It enforces line length limits and character encoding (UTF-8). Used by `StrictJarFile`.

## Architecture
*   **Attributes**: `mainAttributes` (global) and `entries` (per-file attributes).
*   **Chunks**: Stores byte ranges (`Chunk`) for entries to facilitate deferred/lazy verification.

## Key Algorithms
*   **`read`**:
    *   Parses the manifest byte array using `StrictJarManifestReader`.
    *   Identifies the main section and individual entry sections.
*   **`write`**:
    *   Writes attributes to an `OutputStream`.
    *   Enforces 72-byte line length limit with continuations (space prefix on new lines).

## Java-to-C++ Translation Guide
*   **Parsing**: The line continuation logic (CR, LF, CRLF handling) and 72-byte limit are critical for spec compliance.
