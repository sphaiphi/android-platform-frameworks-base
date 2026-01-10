# AutofillFeatureFlags - Reverse Engineering Documentation

## Executive Summary
Utility class for accessing Autofill-related feature flags from `DeviceConfig`.

## Data Model
*   **Keys**: Constants for DeviceConfig keys (e.g., `autofill_dialog_enabled`, `pcc_classification_enabled`).
*   **Defaults**: Default values for flags.

## Java-to-C++ Translation Guide
*   **Config Access**: Wraps `DeviceConfig`. C++ needs a way to read system properties/config.
