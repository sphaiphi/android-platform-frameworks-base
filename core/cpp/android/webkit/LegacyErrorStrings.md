# LegacyErrorStrings - Reverse Engineering Documentation

## Executive Summary
`LegacyErrorStrings` maps integer error codes (from `EventHandler` legacy constants) to localized resource strings (e.g., "Web page not available").

## Detailed Functionality
*   **`getString(code, context)`**: Returns the localized string.
*   **Error Codes**: Maps codes like -1 (ERROR), -2 (LOOKUP), -6 (CONNECT), -8 (TIMEOUT) to `com.android.internal.R.string`.

## Java-to-C++ Translation Guide
*   **Resource Mapping**: C++ doesn't access Android resources directly easily without JNI. Error string generation usually happens on the Java side.
