# ContentProtectionUtils - Reverse Engineering Documentation

## Executive Summary
Utility class for extracting and normalizing text strings from `ContentCaptureEvent` and `ViewNode` objects for content protection analysis.

## Key Methods
*   `getEventTextLower`: Extracts text from event, converts to lowercase.
*   `getViewNodeTextLower`: Extracts text from ViewNode, converts to lowercase.
*   `getHintTextLower`: Extracts hint text from ViewNode, converts to lowercase.

## Java-to-C++ Translation Guide
*   **String Handling**: `String.toLowerCase()` needs locale-aware handling or simple ASCII lowercasing depending on requirements (code uses default locale impl). C++ `std::tolower` or ICU.
