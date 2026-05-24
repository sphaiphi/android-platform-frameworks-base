# DigitalClock - Reverse Engineering Documentation

## Executive Summary
`DigitalClock` is a deprecated widget that displays the current time textually. It has been superseded by `TextClock`.

## Architecture Overview
*   **Inheritance**: `TextView` -> `DigitalClock`.
*   **Status**: Deprecated.

## Detailed Functionality
*   **Ticker**: `Runnable` that posts itself every second.
*   **Format**: Uses `DateFormat.getTimeFormatString` (system preference 12/24h).
*   **Updates**: Re-queries format on `ACTION_TIME_CHANGED` etc.

## Java-to-C++ Translation Guide
*   **Legacy**: Implement using `TextClock` logic instead.

## Implementation Risks
*   None.
