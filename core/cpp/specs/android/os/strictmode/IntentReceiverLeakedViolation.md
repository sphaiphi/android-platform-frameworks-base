# IntentReceiverLeakedViolation - Reverse Engineering Documentation

## Executive Summary
`IntentReceiverLeakedViolation` is raised when an `Activity` or other component is destroyed without unregistering a `BroadcastReceiver` that was registered within it. This causes a memory leak.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Reporting**: Copies the stack trace from an `originStack` which captures where the receiver was originally registered.
