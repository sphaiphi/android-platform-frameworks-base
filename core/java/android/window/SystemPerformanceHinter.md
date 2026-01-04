# SystemPerformanceHinter - Reverse Engineering Documentation

## Executive Summary
`SystemPerformanceHinter` manages performance hints for a process/window. It abstracts the interaction with `SurfaceControl` (for early wake-up and frame rate) and `PerformanceHintManager` (ADPF for CPU/GPU boost).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class`
*   **Role**: Performance Manager.

## Detailed Functionality

### Sessions (`HighPerfSession`)
*   Callers create a session with flags (`HINT_SF`, `HINT_ADPF`).
*   `startSession()`: Increments usage count (via active list).
    *   **SF**: Sets `FrameRateCategory` to HIGH, sets `EarlyWakeupStart`.
    *   **ADPF**: Sends `CPU_LOAD_UP` hint.
*   `close()`: Decrements/Removes session.
    *   **SF**: Resets `FrameRateCategory` to DEFAULT, sets `EarlyWakeupEnd`.
    *   **ADPF**: Sends `CPU_LOAD_RESET` hint.

### Logic
*   It aggregates flags from all active sessions. If *any* session needs a hint, it's enabled. It only disables the hint when *no* sessions need it.

## Java-to-C++ Translation Guide

### Dependencies
*   `SurfaceControl::Transaction`: Direct mapping.
*   `PerformanceHintManager`: Maps to `APerformanceHint` NDK or internal framework equivalent.

### Logic
*   The aggregation logic (bitwise OR of flags) is simple and portable.

## Implementation Risks
*   **Transaction Application**: Uses `applyAsyncUnsafe()`. C++ should likely use `apply(true /* async */)`.
