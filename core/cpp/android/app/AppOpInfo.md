# AppOpInfo - Reverse Engineering Documentation

## Executive Summary
`AppOpInfo` is an immutable data class holding metadata about a specific App Operation (AppOp). It defines the op code, name, associated permission, restriction policies, and default mode.

## Architecture Overview
*   **Type**: Data Class.
*   **Usage**: Used by `AppOpsManager` to define the registry of all available ops.

## Detailed Functionality
*   **Fields**:
    *   `code`: Integer ID.
    *   `name`: Public string constant.
    *   `simpleName`: Debug name.
    *   `permission`: Associated permission string (optional).
    *   `restriction`: User restriction string (optional).
    *   `defaultMode`: Default access mode (`MODE_ALLOWED`, etc.).
    *   `disableReset`: Boolean (prevent reset).
    *   `restrictRead`: Boolean (restrict read access).
    *   `forceCollectNotes`: Boolean.

## Data Model
*   Includes a `Builder` static inner class for construction.

## Java-to-C++ Translation Guide
*   Map to a `struct` or `class` with const fields.
*   Could be part of a static registry in C++.
