# DialerFilter - Reverse Engineering Documentation

## Executive Summary
`DialerFilter` is a deprecated widget that combines a standard QWERTY keyboard input with a numeric 12-key dialer input mechanism. It was used to filter lists (like contacts) using either input mode.

## Architecture Overview
*   **Inheritance**: `RelativeLayout` -> `DialerFilter`.
*   **Status**: Deprecated.

## Detailed Functionality
*   **Modes**: `DIGITS_AND_LETTERS`, `DIGITS_ONLY`, `LETTERS_ONLY`, etc.
*   **Inputs**: Contains two `EditText` fields (`mLetters` and `mDigits`) or swaps their roles (primary/hint).
*   **Key Handling**: Intercepts keys to route them to the appropriate field based on mode.

## Java-to-C++ Translation Guide
*   Likely unnecessary to port unless supporting very old legacy apps.

## Implementation Risks
*   None.
