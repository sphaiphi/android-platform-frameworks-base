# ForegroundServiceStartNotAllowedException - Reverse Engineering Documentation

## Executive Summary
`ForegroundServiceStartNotAllowedException` is thrown when an app tries to start a foreground service from the background (which is restricted).

## Architecture Overview
*   **Inheritance**: `ServiceStartNotAllowedException` -> `IllegalStateException`.
*   **Implements**: `Parcelable`.

## Java-to-C++ Translation Guide
*   Exception class.

## Implementation Risks
*   None.
