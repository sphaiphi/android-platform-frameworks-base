# TextViewTranslationCallback - Reverse Engineering Documentation

## Executive Summary
`TextViewTranslationCallback` manages the display of translated text within a `TextView`. It intercepts the translation response and swaps the displayed text while preserving the original state.

## Architecture Overview
*   **Implements**: `ViewTranslationCallback`.
*   **Role**: Translation UI Manager.

## Detailed Functionality
*   **Transformation**: Uses `TranslationTransformationMethod` to show the translated text without changing the underlying buffer.
*   **Animation**: Fades text out/in when switching between original and translated versions.
*   **Padding**: Can pad the original text with spaces (`\u2002`) to match the translated text length, preventing layout jumps if the translation is longer.

## Java-to-C++ Translation Guide
*   **TransformationMethod**: Similar to Password transformation; renders different text than what is stored.
*   **Animation**: Alpha fade.

## Implementation Risks
*   **Text Layout**: Ensuring the view layout updates correctly if the translated text has a different size/line count.
