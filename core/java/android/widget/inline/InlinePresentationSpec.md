# InlinePresentationSpec - Reverse Engineering Documentation

## Executive Summary
`InlinePresentationSpec` is a configuration data class used to define the size constraints and styling requirements for an inline suggestion (e.g., an Autofill chip).

## Architecture Overview
*   **Type**: Data Class (`Parcelable`).
*   **Role**: Specification / Configuration.

## Detailed Functionality
*   **Constraints**: Defines `mMinSize` and `mMaxSize` (`Size` objects).
*   **Styling**: Carries a `Bundle` (`mStyle`) containing UI versioning and style attributes (defined by AndroidX libraries) to ensure the remote view matches the host's look and feel.
*   **Filtering**: `filterContentTypes()` utility to sanitize the style bundle before IPC.

## Java-to-C++ Translation Guide
*   **Struct**:
    ```cpp
    struct InlinePresentationSpec {
        Size minSize;
        Size maxSize;
        Bundle style; // Map<String, Variant>
    };
    ```

## Implementation Risks
*   None.
