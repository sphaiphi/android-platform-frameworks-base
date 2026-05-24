# TextClassificationConstants - Reverse Engineering Documentation

## Executive Summary
Holds constants and configuration flags for TextClassifier, read from `DeviceConfig`.

## Data Model
*   **Flags**: `smart_selection_enabled`, `smart_linkify_enabled`, `system_textclassifier_enabled`, etc.
*   **Memoization**: Caches values to avoid repeated IPC calls to DeviceConfig.

## Java-to-C++ Translation Guide
*   **Config**: Wraps system property/config access.
