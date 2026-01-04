# DisplayWindowPolicyController - Reverse Engineering Documentation

## Executive Summary
`DisplayWindowPolicyController` is an abstract base class used to define and enforce policies for windows on specific displays (often virtual displays). It allows the display owner to intercept activity launches, restrict windowing modes, and filter window flags.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `abstract class`
*   **Role**: Policy Enforcer.

## Detailed Functionality

### Windowing Mode Support
*   Maintains a `Set<Integer>` of supported modes.
*   Default: `WINDOWING_MODE_FULLSCREEN`, `WINDOWING_MODE_MULTI_WINDOW`.
*   Thread-safe access (synchronized on the set).

### Window Flags
*   `isInterestedWindowFlags(windowFlags, systemWindowFlags)`: Checks if the window has flags the controller cares about.
*   `keepActivityOnWindowFlagsChanged`: Abstract callback when those flags change.

### Activity Launch Policy
*   `canActivityBeLaunched(...)`: Abstract method to approve/deny launch. Can provide an `IntentSender` for fallback/interception.
*   `canContainActivities(...)`: Checks a list of activities against the policy.

## Java-to-C++ Translation Guide

### Collections
*   `ArraySet<Integer>` -> `std::set<int>` or `std::unordered_set<int>`.
*   **Synchronization**: The Java code synchronizes on the set object. C++ needs a `std::mutex` protecting the set.

### Abstract Methods
*   Implement as `virtual` functions.

### IntentSender
*   Used in `canActivityBeLaunched`. In C++, this corresponds to `IIntentSender` (Binder).

## Implementation Risks
*   **Concurrency**: Ensure the mutex is used correctly in C++ to match the synchronized blocks.
