# BackNavigationInfo - Reverse Engineering Documentation

## Executive Summary
`BackNavigationInfo` conveys the result of a back navigation prediction or setup to SystemUI (or other shell components). It defines *what* will happen if the back gesture completes (e.g., return to home, cross-activity) and provides callbacks and animation targets to execute that transition.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Information carrier for back navigation state.
*   **Inner Classes**:
    *   `CustomAnimationInfo`: Holds resource IDs for custom transitions.
    *   `Builder`: standard builder pattern.

## Data Model

### BackTargetType (IntDef)
*   `TYPE_UNDEFINED` (-1)
*   `TYPE_DIALOG_CLOSE` (0)
*   `TYPE_RETURN_TO_HOME` (1)
*   `TYPE_CROSS_ACTIVITY` (2)
*   `TYPE_CROSS_TASK` (3)
*   `TYPE_CALLBACK` (4) - Application handles it via `OnBackInvokedCallback`.

### Fields
| Field | Type | Description |
| :--- | :--- | :--- |
| `mType` | `int` | One of `BackTargetType`. |
| `mOnBackNavigationDone` | `RemoteCallback` | Callback to notify when shell is done with preview. |
| `mOnBackInvokedCallback` | `IOnBackInvokedCallback` | The app's callback (if `TYPE_CALLBACK`). |
| `mPrepareRemoteAnimation` | `boolean` | True if core prepares the animation. |
| `mAnimationCallback` | `boolean` | True if the callback is an `OnBackAnimationCallback`. |
| `mCustomAnimationInfo` | `CustomAnimationInfo` | Resources for custom animations. |
| `mLetterboxColor` | `int` | Color if letterboxed. |
| `mTouchableRegion` | `Rect` | App window region handling touch. |
| `mAppProgressGenerationAllowed` | `boolean` | If client view generates progress events. |
| `mFocusedTaskId` | `int` | ID of the focused task. |

### CustomAnimationInfo
Holds package name, window animation resource ID, and specific enter/exit/background resource IDs.

## Detailed Functionality

### `onBackNavigationFinished(boolean triggerBack)`
**Purpose**: Notifies the system (via `mOnBackNavigationDone`) that the navigation interaction is finished.
**Mechanism**: Sends a Bundle with `KEY_NAVIGATION_FINISHED` boolean to the `RemoteCallback`.

## Java-to-C++ Translation Guide

### Data Types
*   `RemoteCallback` -> `android::os::IRemoteCallback` (likely via `sp`).
*   `IOnBackInvokedCallback` -> `sp<IOnBackInvokedCallback>`.
*   `Rect` -> `android::graphics::Rect`.

### Parceling
*   **Order**:
    1.  `mType`
    2.  `mOnBackNavigationDone`
    3.  `mOnBackInvokedCallback`
    4.  `mPrepareRemoteAnimation`
    5.  `mAnimationCallback`
    6.  `mCustomAnimationInfo`
    7.  `mLetterboxColor`
    8.  `mTouchableRegion`
    9.  `mAppProgressGenerationAllowed`
    10. `mFocusedTaskId`

## Implementation Risks
*   **Callback Lifetimes**: `RemoteCallback` and `IOnBackInvokedCallback` are binder objects. Ensure proper ref-counting.
*   **CustomAnimationInfo**: This nested class also implements Parcelable and must be correctly handled during read/write of the parent object.
