# ApplicationStartInfo - Reverse Engineering Documentation

## Executive Summary
`ApplicationStartInfo` describes details about an application process startup, including the reason, start type (cold, warm, hot), launch mode, and critical timestamps. It allows apps to diagnose startup performance and reasons.

## Architecture Overview
*   **Type**: Parcelable Data Class.
*   **Features**: Protobuf support.

## Detailed Functionality

### Startup States
*   `STARTUP_STATE_STARTED`, `STARTUP_STATE_ERROR`, `STARTUP_STATE_FIRST_FRAME_DRAWN`.

### Start Reasons
*   Enumerated: `ALARM`, `BACKUP`, `BOOT_COMPLETE`, `BROADCAST`, `CONTENT_PROVIDER`, `JOB`, `LAUNCHER`, `PUSH`, `SERVICE`, `START_ACTIVITY`, etc.

### Start Type
*   `COLD`: Process started from scratch.
*   `WARM`: Process retained saved instance state.
*   `HOT`: Process brought to foreground.

### Timestamps
*   Map of Integer keys to Long timestamps (nanoseconds).
*   Keys: `LAUNCH`, `FORK`, `BIND_APPLICATION`, `FIRST_FRAME`, `FULLY_DRAWN`.

## Data Model
*   `mStartupState`, `mPid`, `mRealUid`, `mPackageName`, `mReason`, `mStartType`, `mStartIntent`.
*   `mStartupTimestampsNs`: `ArrayMap<Integer, Long>`.

## Java-to-C++ Translation Guide
*   Standard Parcelable mapping.
*   Map `ArrayMap` to `std::map` or `std::unordered_map`.

## Implementation Risks
*   None. Pure data container.
