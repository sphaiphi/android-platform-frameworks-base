# FindAddress - Reverse Engineering Documentation

## Executive Summary
`FindAddress` is a utility class containing regex-based logic to detect physical US addresses in text. It implements the legacy `WebView.findAddress` algorithm.

## Data Model
*   **ZipRange**: Helper class for validating zip codes against state ranges.
*   **Regex**: Extensive patterns for states (`sStateRe`), house numbers (`sHouseNumberRe`), street names, and location suffixes (`sLocationNameRe`).

## Detailed Functionality
*   **`findAddress(String)`**: The main entry point.
*   **Algorithm**:
    1.  Finds a potential house number.
    2.  Extends the match forward to finding a street name, state, and optional zip code.
    3.  Validates constraints (word count, line count, matching state/zip).

## Java-to-C++ Translation Guide
*   **Regex**: Can be translated to C++ using `std::regex` or `RE2`.
*   **Logic**: The state/zip logic is hardcoded data; replicate the arrays and helper functions.
*   **Locale**: Note `Locale.getDefault()` usage for ordinal suffixes (st, nd, rd, th); C++ implementation should be locale-aware if needed, though this class is US-centric.
