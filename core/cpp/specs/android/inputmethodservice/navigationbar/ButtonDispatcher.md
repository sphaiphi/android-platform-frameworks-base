# ButtonDispatcher - Reverse Engineering Documentation

## Executive Summary
`ButtonDispatcher` acts as a proxy for multiple views sharing the same ID (e.g., navigation buttons that might appear in portrait vs landscape layouts). It dispatches property changes (visibility, alpha, image, listeners) to all registered views.

## Architecture Overview
*   **Role**: Multi-cast delegate for View properties.

## Detailed Functionality
*   **Registration**: `addView(View)` adds a view to the list and syncs current state (alpha, visibility, listeners) to it immediately.
*   **Dispatch**: `setAlpha`, `setVisibility`, `setImageDrawable` iterate `mViews` and apply changes.
*   **Animation**: Handles fade-in/fade-out animations (`mFadeAnimator`).

## Java-to-C++ Translation Guide
*   **Observer Pattern**: List of pointers to Views.
*   **Animation**: Property animation system needed.
