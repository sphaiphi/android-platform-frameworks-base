# RadioButton - Reverse Engineering Documentation

## Executive Summary
`RadioButton` is a `CompoundButton` that is mutually exclusive within a `RadioGroup`.

## Architecture Overview
*   **Inheritance**: `CompoundButton` -> `RadioButton`.
*   **Role**: Single-choice Item.

## Detailed Functionality
*   **`toggle()`**: Overridden to prevent unchecking. Once checked, a radio button stays checked until another one is selected (clearing this one).

## Java-to-C++ Translation Guide
*   **Logic**: Simple override of `toggle`.

## Implementation Risks
*   None.
