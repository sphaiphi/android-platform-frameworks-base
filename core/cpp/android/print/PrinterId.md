# PrinterId - Reverse Engineering Documentation

## Executive Summary
`PrinterId` uniquely identifies a printer. It consists of the `ComponentName` of the print service that manages the printer and a locally unique ID string assigned by that service.

## Architecture Overview
- **Type**: Parcelable Data Class (final).
- **Identity**: Combination of (Service ComponentName + Local String ID).

## Java-to-C++ Translation Guide
-   **Equality**: Must implement equality based on both fields.
-   **Component Name**: Maps to a struct with package name and class name.
