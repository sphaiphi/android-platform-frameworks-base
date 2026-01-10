# Chronometer - Reverse Engineering Documentation

## Executive Summary
`Chronometer` is a `TextView` that implements a simple timer. It counts up (or down) from a base time. It formats the elapsed time (e.g., "MM:SS") and updates the display every second.

## Architecture Overview
*   **Inheritance**: `TextView` -> `Chronometer`.
*   **Timing**: Uses `SystemClock.elapsedRealtime()`.

## Detailed Functionality

### 1. Update Loop
*   **`start()`**: Sets `mStarted = true` and calls `updateRunning()`.
*   **`updateRunning()`**: Posts a `Runnable` (`mTickRunnable`) to the handler.
*   **`mTickRunnable`**:
    *   Updates the text.
    *   Dispatches `onChronometerTick`.
    *   Calculates delay to the next second boundary (`1000 - (now % 1000)`) and re-posts itself.

### 2. Formatting
*   Uses `DateUtils.formatElapsedTime` or a custom `Formatter` if `setFormat` is used.
*   Handles "H:MM:SS" or "MM:SS".

## Java-to-C++ Translation Guide
*   **Timer**: Requires a recurring timer mechanism on the UI thread.
*   **String Formatting**: Use `strftime` or similar.

## Implementation Risks
*   **Leak**: Ensure the runnable is removed when the view is detached.
