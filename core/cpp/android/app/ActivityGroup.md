# ActivityGroup - Reverse Engineering Documentation

## Executive Summary
`ActivityGroup` is a deprecated class that was used to embed multiple activities within a single screen. It manages a `LocalActivityManager` to handle the lifecycle of embedded activities. It has been largely superseded by Fragments.

## Architecture Overview
*   **Inheritance**: Extends `Activity`.
*   **Component**: `LocalActivityManager` (owned).
*   **Key Concept**: "Activity within Activity" pattern.

## Detailed Functionality

### Lifecycle Forwarding
**Purpose**: Forward lifecycle events of the parent `ActivityGroup` to the embedded activities managed by `LocalActivityManager`.
**Methods**:
*   `onCreate`: Calls `mLocalActivityManager.dispatchCreate`.
*   `onResume`: Calls `mLocalActivityManager.dispatchResume`.
*   `onPause`: Calls `mLocalActivityManager.dispatchPause`.
*   `onStop`: Calls `mLocalActivityManager.dispatchStop`.
*   `onDestroy`: Calls `mLocalActivityManager.dispatchDestroy`.

### State Retention
**Purpose**: Persist state of child activities.
**Mechanism**:
*   `onSaveInstanceState`: Saves state from `LocalActivityManager`.
*   `onRetainNonConfigurationChildInstances`: Returns map from `LocalActivityManager`.

### Activity Access
**Purpose**: Provide access to currently running embedded activity.
**Methods**: `getCurrentActivity()`.

## Data Model
*   `mLocalActivityManager`: `LocalActivityManager`. The core component doing the work.

## API Reference
*   `getCurrentActivity()`: Returns the currently active child activity.
*   `getLocalActivityManager()`: Accessor for the manager.

## Java-to-C++ Translation Guide

### Relevance
*   Since this is deprecated and relies on `LocalActivityManager` (legacy), prioritize Fragments. However, if legacy support is needed:
    *   Need `LocalActivityManager` C++ equivalent.
    *   Lifecycle forwarding logic is straightforward method delegation.

### Memory Management
*   `LocalActivityManager` ownership must be managed (unique_ptr).

## Implementation Risks
*   **Legacy Complexity**: The "Activity inside Activity" model has complex edge cases regarding window management and focus which are difficult to replicate and generally discouraged.
