# DateUtilsBridge - Reverse Engineering Documentation

## Executive Summary
Bridge class to interface with ICU classes (Calendar, TimeZone) for `DateUtils`.

## API Reference
- **`icuTimeZone`**: Wraps Java TimeZone.
- **`createIcuCalendar`**: Creates ICU Calendar.
- **`toSkeleton`**: Converts flags (SHOW_YEAR, etc.) into a skeleton string ("yMMM").

## Java-to-C++ Translation Guide
- **Helper**: In C++, use ICU types directly. The `toSkeleton` logic determines which fields (y, M, d, h, m) should be present based on flags.
