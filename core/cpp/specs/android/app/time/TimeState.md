# TimeState - Reverse Engineering Documentation

## Executive Summary
A snapshot of the system's time state, containing the current time (Unix Epoch + Elapsed Realtime) and a flag indicating if the user should be prompted to confirm this time.

## Architecture Overview
*   **Type**: `public final class` implementing `Parcelable`.
*   **Structure**: Immutable data class.

## Data Model
*   `UnixEpochTime mUnixEpochTime`: The time value.
*   `boolean mUserShouldConfirmTime`: Confidence signal (True = Low confidence, ask user).

## API Reference
*   `parseCommandLineArgs`: Utility for parsing shell arguments (`--elapsed_realtime`, `--unix_epoch_time`, `--user_should_confirm_time`).

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard.
*   **Shell Parsing**: Replicate command line argument parsing logic.

## Test Cases & Validation
*   Parse args: `--elapsed_realtime 100 --unix_epoch_time 200 --user_should_confirm_time true`.
*   Verify fields match.

## Implementation Risks
*   None.
