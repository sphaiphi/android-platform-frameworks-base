# TaskFragmentCreationParams - Reverse Engineering Documentation

## Executive Summary
`TaskFragmentCreationParams` is a Parcelable data object used to specify options when creating a new `TaskFragment`. It encapsulates identity, ownership, geometry, and behavioral flags required by the `WindowManager` to instantiate the fragment correctly.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Specification DTO for creation.
*   **Key Relationships**: Used by `WindowContainerTransaction` to request fragment creation.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mOrganizer` | `TaskFragmentOrganizerToken` | The organizer responsible for this fragment. |
| `mFragmentToken` | `IBinder` | Unique token assigned by the client to identify the new fragment. |
| `mOwnerToken` | `IBinder` | Activity token used to identify the Task to create the fragment in. |
| `mInitialRelativeBounds` | `Rect` | Bounds relative to the parent Task. |
| `mWindowingMode` | `int` | Initial windowing mode (e.g., MULTI_WINDOW). |
| `mPairedPrimaryFragmentToken` | `IBinder` | (Optional) Fragment token to position above. |
| `mPairedActivityToken` | `IBinder` | (Optional) Activity token to position above. |
| `mAllowTransitionWhenEmpty` | `boolean` | Flag to allow transitions if no activities are present. |
| `mOverrideOrientation` | `int` | Forced orientation (system organizers only). |
| `mConfigurationChangeMask` | `int` | Mask for triggering callbacks on config changes. |

## Detailed Functionality

### Positional Logic
*   The `pairedPrimaryFragmentToken` and `pairedActivityToken` are mutually exclusive.
*   They allow precise Z-ordering or stacking within the Task hierarchy during initialization.

### Orientation and Configuration
*   `mOverrideOrientation` and `mConfigurationChangeMask` are primarily for system-level organizers (like those handling activity embedding in a specific way).

## Java-to-C++ Translation Guide

### Data Types
*   `IBinder` -> `sp<IBinder>`.
*   `Rect` -> `android::graphics::Rect`.
*   `TaskFragmentOrganizerToken` -> C++ Parcelable equivalent.

### Parceling Order
1.  `mOrganizer`
2.  `mFragmentToken`
3.  `mOwnerToken`
4.  `mInitialRelativeBounds`
5.  `mWindowingMode`
6.  `mPairedPrimaryFragmentToken`
7.  `mPairedActivityToken`
8.  `mAllowTransitionWhenEmpty`
9.  `mOverrideOrientation`
10. `mConfigurationChangeMask`

## Implementation Risks
*   **Mutually Exclusive Tokens**: Ensure the C++ Builder enforces that `pairedPrimaryFragmentToken` and `pairedActivityToken` aren't both set.
