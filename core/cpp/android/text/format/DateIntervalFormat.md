# DateIntervalFormat - Reverse Engineering Documentation

## Executive Summary
Wrapper around ICU's `DateIntervalFormat` to format ranges (e.g., "Jan 10-12").

## API Reference
- **`formatDateRange`**: Main entry point. Accepts flags (`FORMAT_SHOW_TIME`, etc.) to configure output. Handles "midnight" special cases.

## Java-to-C++ Translation Guide
- **ICU**: Use `android::icu::DateIntervalFormat`.
- **Logic**: Port the skeleton generation logic (converting flags to skeleton string).
