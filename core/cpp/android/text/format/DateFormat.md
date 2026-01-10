# DateFormat - Reverse Engineering Documentation

## Executive Summary
Utilities for formatting dates and times using system locale conventions. Acts as a factory for `java.text.DateFormat`.

## API Reference
- **`is24HourFormat`**: Checks system preference for 24h format.
- **`getBestDateTimePattern`**: Returns the best localized pattern for a skeleton (e.g., "MMMMd"). Uses ICU `DateTimePatternGenerator`.
- **`getTimeFormat`**, **`getDateFormat`**: Returns formatters.
- **`format(CharSequence, Calendar)`**: Formats a date using a custom format string (subset of standard patterns).

## Java-to-C++ Translation Guide
- **ICU**: Heavily relies on ICU `DateTimePatternGenerator` and `DateFormat`.
- **Legacy**: The `format` method implements a custom (and somewhat legacy) formatting logic (`acdEHhLKkLMmsyz`).
