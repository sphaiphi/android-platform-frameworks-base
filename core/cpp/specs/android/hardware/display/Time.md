# Time - Reverse Engineering Documentation

## Executive Summary
`Time` is a lightweight Parcelable wrapper around `java.time.LocalTime` (hour, minute, second, nano). It is used to transport time configuration for Night Light schedules across Binder.

## Data Model
- `mHour`, `mMinute`, `mSecond`, `mNano`: Integers.

## Java-to-C++ Translation Guide
- Map to a simple struct:
  ```cpp
  struct Time {
      int32_t hour;
      int32_t minute;
      int32_t second;
      int32_t nano;
  };
  ```
- **Serialization**: Write 4 integers in order.
