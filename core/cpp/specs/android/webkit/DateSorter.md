# DateSorter - Reverse Engineering Documentation

## Executive Summary
`DateSorter` is a utility class that bins dates into categories like "Today", "Yesterday", "Last 7 days", "Last Month", and "Older". It was likely used for history or download list grouping.

## Detailed Functionality
*   **Bins**: 5 fixed bins.
*   **Labels**: Uses `DateSorterBridge` (ICU) and localized strings to generate labels.
*   **`getIndex(long time)`**: Returns the bin index for a timestamp.
*   **`getBoundary(int index)`**: Returns the time boundary for a bin.

## Java-to-C++ Translation Guide
*   **Localization**: Requires access to ICU or a similar localization library for date strings ("Yesterday", etc.).
*   **Logic**: Simple time arithmetic relative to "start of today".
