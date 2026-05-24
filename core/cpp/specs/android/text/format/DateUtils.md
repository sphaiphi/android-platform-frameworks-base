# DateUtils - Reverse Engineering Documentation

## Executive Summary
High-level date formatting utilities.

## API Reference
- **`getRelativeTimeSpanString`**: "42 minutes ago".
- **`getRelativeDateTimeString`**: "Oct 31, 10:00 AM".
- **`formatElapsedTime`**: "MM:SS" or "H:MM:SS".
- **`isToday`**: Checks if time is today.

## Java-to-C++ Translation Guide
- **Logic**: Delegates most relative formatting to `RelativeDateTimeFormatter`.
- **Elapsed Time**: Custom logic for HH:MM:SS formatting.
