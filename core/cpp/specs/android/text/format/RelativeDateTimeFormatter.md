# RelativeDateTimeFormatter - Reverse Engineering Documentation

## Executive Summary
Wrapper for ICU `RelativeDateTimeFormatter`. Handles "yesterday", "2 days ago", etc.

## API Reference
- **`getRelativeTimeSpanString`**: Calculates difference, selects unit (seconds, minutes, hours, days, weeks), and uses ICU to format. Handles "minResolution" to force coarser units.

## Java-to-C++ Translation Guide
- **ICU**: Use `android::icu::RelativeDateTimeFormatter`.
- **Logic**: Logic to choose the appropriate unit and direction (past/future) based on duration thresholds.
