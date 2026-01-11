# TranslationCapability - Reverse Engineering Documentation

## Executive Summary
A Parcelable data class that describes the capabilities of a translation service, specifically regarding supported source/target languages (specs) and the state of the model (on-device, downloading, etc.).

## Data Model
*   **State (`int`)**:
    *   `STATE_AVAILABLE_TO_DOWNLOAD` (1)
    *   `STATE_DOWNLOADING` (2)
    *   `STATE_ON_DEVICE` (3)
    *   `STATE_NOT_AVAILABLE` (4)
    *   `STATE_REMOVED_AND_AVAILABLE` (1000)
*   **Specs**: `TranslationSpec` for source and target.
*   **UI Translation**: `boolean` indicating if UI translation is supported for this pair.
*   **Flags**: Supported translation flags.

## Java-to-C++ Translation Guide
*   **Parcelable**: Implement Android Binder serialization.
*   **Enums**: Map `ModelState` constants to C++ enum.
