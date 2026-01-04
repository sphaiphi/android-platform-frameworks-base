# ImplicitDirectBootViolation - Reverse Engineering Documentation

## Executive Summary
`ImplicitDirectBootViolation` is raised when a component implicitly relies on automatic Direct Boot filtering during a query (e.g., querying package manager) instead of explicitly specifying whether it wants to see components that are available before user unlock.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Recommendation**: Use explicit `PackageManager.MATCH_DIRECT_BOOT_*` flags.
