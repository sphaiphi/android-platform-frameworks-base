# NonSdkApiUsedViolation - Reverse Engineering Documentation

## Executive Summary
`NonSdkApiUsedViolation` is raised when an application uses reflection or JNI to access internal Android APIs that are not part of the public SDK (hidden or internal members).

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Detection**: Intercepted by the ART runtime's "hidden API" enforcement logic.
