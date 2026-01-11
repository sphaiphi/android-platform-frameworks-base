# TaskFragmentAnimationParams - Reverse Engineering Documentation

## Executive Summary
`TaskFragmentAnimationParams` overrides the default animations for a TaskFragment (open, change, close). It is used when the organizer wants to customize transitions for embedded fragments.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: DTO for animation settings.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mAnimationBackgroundColor` | `int` | ARGB color. |
| `mOpenAnimationResId` | `int` | Resource ID. |
| `mChangeAnimationResId` | `int` | Resource ID. |
| `mCloseAnimationResId` | `int` | Resource ID. |

## Detailed Functionality
*   **Defaults**: `DEFAULT_ANIMATION_RESOURCES_ID` (0xFFFFFFFF).
*   **`hasOverrideAnimation()`**: Checks if any res ID is set to a non-default value.

## Java-to-C++ Translation Guide
*   Standard Parcelable.

## Implementation Risks
*   **Resource IDs**: C++ code might not have access to the same resources context to resolve these IDs if they refer to app resources. They are typically resolved by the transition player (Shell/SystemUI) which has context.
