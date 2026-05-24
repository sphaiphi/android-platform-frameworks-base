# UiTranslationController - Reverse Engineering Documentation

## Executive Summary
Manages the lifecycle and logic of UI Translation within a specific `Activity`. It acts as the bridge between the `UiTranslationManager` (system service calls) and the View hierarchy.

## Architecture
*   **Ownership**: Owned by `Activity`.
*   **Translators**: Maintains a map of `Translator` instances keyed by source/target spec pairs.
*   **View Tracking**: Keeps weak references to Views involved in translation (`mViews`) to update them when translation finishes or updates.
*   **Threading**: Uses a dedicated `HandlerThread` ("UiTranslationController_...") for worker tasks (creating translators, sending requests) to avoid blocking the UI thread.

## Key Algorithms
*   **`updateUiTranslationState`**:
    *   **STARTED**: collects Views, creates `Translator` (if needed), traverses hierarchy (`findViewsTraversalByAutofillIds`), dispatch `dispatchCreateViewTranslationRequest` to views, and sends request.
    *   **PAUSED/RESUMED**: Iterates tracked views and calls `onHideTranslation`/`onShowTranslation`.
    *   **FINISHED**: Destroys translators, clears state on views, notifies manager.
*   **`onTranslationCompleted`**:
    *   Receives `TranslationResponse`.
    *   Matches results to Views via `AutofillId`.
    *    Handles Virtual Views (children of a View).
    *   Calls `View.onViewTranslationResponse` and the `ViewTranslationCallback` to display results.
*   **Dump**: Provides debug info (translators, tracked views, view hierarchy traversal).

## Java-to-C++ Translation Guide
*   **View Hierarchy**: Deeply coupled with Android View system (`ViewRootImpl`, `WindowManagerGlobal`, `ViewGroup`). Porting this requires a corresponding UI toolkit reference.
*   **WeakReference**: Uses `WeakReference` to hold Views.
*   **HandlerThread**: Standard Looper/Handler pattern.
