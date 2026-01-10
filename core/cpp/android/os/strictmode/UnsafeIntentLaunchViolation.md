# UnsafeIntentLaunchViolation - Reverse Engineering Documentation

## Executive Summary
`UnsafeIntentLaunchViolation` is a security-focused violation. It is raised when an app launches an `Intent` that originated from an external, untrusted source (an "Unsafe Intent"). This can lead to privilege escalation or unintended component launches.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Payload**: Holds a reference to the offending `Intent`.

## Detailed Functionality
-   **Transient Intent**: The `mIntent` field is marked `transient`. This means if the violation is serialized (e.g., sent over Binder to `dropbox`), the `Intent` object is lost, but the string representation in the message remains.
-   **Detection**: Raised by the framework when an `Intent` received from `getIntent()` or a `Broadcast` is used to start another component without proper sanitization.

## API Reference
-   `getIntent()`: Returns the `Intent` if available (not available if deserialized).
