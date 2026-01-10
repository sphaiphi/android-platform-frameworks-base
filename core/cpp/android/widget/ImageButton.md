# ImageButton - Reverse Engineering Documentation

## Executive Summary
`ImageButton` is an `ImageView` that behaves like a button (standard button background, focus states, click sounds).

## Architecture Overview
*   **Inheritance**: `ImageView` -> `ImageButton`.
*   **Role**: Clickable Image.

## Detailed Functionality
*   **Style**: Uses `com.android.internal.R.attr.imageButtonStyle`.
*   **Pointer Icon**: Hand/Arrow depending on state.

## Java-to-C++ Translation Guide
*   **Styling**: Apply button background style to an ImageView.

## Implementation Risks
*   None.
