# Build - Reverse Engineering Documentation

## Executive Summary
`Build` exposes static information about the current build, extracted from system properties (`ro.*`). It provides details like the manufacturer, model, build ID, version codes (SDK_INT), and partition fingerprints.

## Architecture Overview
-   **Pattern**: Static Info Holder.
-   **Source**: `SystemProperties` (mostly read-only props).

## Data Model
-   **Identity**: `ID`, `DISPLAY`, `PRODUCT`, `DEVICE`, `BOARD`, `MANUFACTURER`, `BRAND`, `MODEL`.
-   **Hardware**: `HARDWARE`, `SKU`, `ODM_SKU`, `SOC_MANUFACTURER`, `SOC_MODEL`.
-   **Version**:
    -   `VERSION.SDK_INT`: Integer SDK level.
    -   `VERSION.RELEASE`: User-visible string.
    -   `VERSION.INCREMENTAL`: Precise build version.
    -   `VERSION.CODENAME`: Development codename (e.g., "UpsideDownCake").

## API Reference
-   `getSerial()`: Returns hardware serial (requires permission).
-   `is64Bit()`: Checks runtime architecture.
-   `getFingerprintedPartitions()`: Returns info about partitions (system, vendor, etc.).

## Java-to-C++ Translation Guide
-   **Properties**: Direct mapping to `property_get`.
-   **C++ Equivalent**: `android-base/properties.h` and specific headers generating build config.
-   **Fingerprint**: The logic to derive the fingerprint (if not set in `ro.build.fingerprint`) combines brand/name/device:version/id/incremental:type/tags.
