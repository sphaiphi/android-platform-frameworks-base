# UiTranslationManager - Reverse Engineering Documentation

## Executive Summary
The client-facing API for managing UI Translation. It allows apps (or the system) to trigger UI translation flows, though in practice it's often triggered by the system intelligence.

## Data Model
*   **States**: `STARTED` (0), `PAUSED` (1), `RESUMED` (2), `FINISHED` (3).
*   **Extras**: Keys for passing state, locale, and package name in bundles.

## Key Methods
*   **`startTranslation`**: Calls service to update state to STARTED. Requires specific permissions (`MANAGE_UI_TRANSLATION`).
*   **`pause/resume/finishTranslation`**: State transitions.
*   **`registerUiTranslationStateCallback`**: Registers a callback for state changes (using `UiTranslationStateRemoteCallback` to wrapper the Binder call).

## Java-to-C++ Translation Guide
*   **Permissions**: Permission checks happen in system server, but this client code has `@RequiresPermission` annotations.
*   **Binder**: Wraps calls to `ITranslationManager`.
