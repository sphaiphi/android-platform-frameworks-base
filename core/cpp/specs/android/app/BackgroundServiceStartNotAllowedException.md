# BackgroundServiceStartNotAllowedException - Reverse Engineering Documentation

## Executive Summary
`BackgroundServiceStartNotAllowedException` is a specific `ServiceStartNotAllowedException` thrown when an app attempts to start a background service from the background (which is restricted in modern Android versions).

## Architecture Overview
*   **Inheritance**: `ServiceStartNotAllowedException` -> `IllegalStateException`.
*   **Implements**: `Parcelable`.

## Detailed Functionality
*   **Purpose**: Semantic exception type for specific background start failures.
*   **Constructor**: Takes a message string.

## Java-to-C++ Translation Guide
*   Map to C++ Exception class.

## Implementation Risks
*   None.
