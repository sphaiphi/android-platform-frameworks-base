# GameManagerInternal - Reverse Engineering Documentation

## Executive Summary
`GameManagerInternal` is the local service interface for the Game Manager, allowing other system services to interact with it directly.

## Architecture Overview
*   **Type**: Abstract Class.

## Detailed Functionality
*   `getResolutionScalingFactor(String packageName, int userId)`: Used by `CompatModePackages` to apply resolution scaling overrides.

## Java-to-C++ Translation Guide
*   Internal interface.

## Implementation Risks
*   None.
