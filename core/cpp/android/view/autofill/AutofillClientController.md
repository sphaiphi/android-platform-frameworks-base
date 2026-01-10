# AutofillClientController - Reverse Engineering Documentation

## Executive Summary
Manages Autofill requests for an `Activity`. Acts as the client-side controller, interfacing between the Activity lifecycle, the View hierarchy, and the `AutofillManager` system service.

## Architecture
*   **Ownership**: Owned by `Activity`.
*   **Manager Access**: Lazily fetches `AutofillManager` via `getSystemService`.
*   **Lifecycle Hooks**: `onActivityCreated`, `onActivityStarted`, `onActivityResumed`, `onActivityPaused`, etc. ensure autofill state is managed correctly during activity transitions.
*   **UI**: Manages `AutofillPopupWindow` for showing autofill UI (if not handled by system window).

## Key Algorithms
*   **`forResume`**: Logic to handle autofill state when activity resumes. Includes compatibility mode checks and potential relayout fixes (retrying fill if layout changed).
*   **`autofillClientFindViewByAutofillIdTraversal`**: Traverses the ViewRootImpls to find a view by its `AutofillId`.

## Java-to-C++ Translation Guide
*   **Activity Lifecycle**: Needs hooks into the equivalent of Android Activity lifecycle.
*   **View Hierarchy**: Deep dependency on `View`, `ViewRootImpl`, `WindowManagerGlobal`.
