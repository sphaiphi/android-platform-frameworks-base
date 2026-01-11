# CustomViolation - Reverse Engineering Documentation

## Executive Summary
`CustomViolation` allows developers or framework components to define and report their own specific StrictMode violations that do not fit into the standard categories.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Payload**: Carries a developer-defined name or message.
