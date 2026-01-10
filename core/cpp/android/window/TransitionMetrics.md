# TransitionMetrics - Reverse Engineering Documentation

## Executive Summary
`TransitionMetrics` is a helper singleton that provides a simplified API for reporting transition timing metrics (e.g., animation start time) back to the system server. It wraps the `ITransitionMetricsReporter` interface.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` (Singleton)
*   **Role**: Metrics Reporting Proxy.

## Detailed Functionality
*   **`reportAnimationStart(IBinder token)`**: Gets the current `SystemClock.elapsedRealtime()` and sends it to the reporter.
*   **Initialization**: Uses `WindowOrganizer.getTransitionMetricsReporter()` to obtain the binder interface.

## Java-to-C++ Translation Guide
*   **Singleton**: `static TransitionMetrics& getInstance()`.
*   **Clock**: Use `android::uptimeMillis()` or equivalent native monotonic clock.

## Implementation Risks
*   None.
