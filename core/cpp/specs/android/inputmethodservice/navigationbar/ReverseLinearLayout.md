# ReverseLinearLayout - Reverse Engineering Documentation

## Executive Summary
`ReverseLinearLayout` is a `LinearLayout` that can reverse the drawing order of its children (and their layout params) based on layout direction (RTL/LTR) or a manual "alternative order" flag. Used for the navigation bar to swap button order in 90/270 degree rotations.

## Detailed Functionality
*   **Reversal**: If `isLayoutReverse` is true, adds children at index 0 (stacking them in reverse). Swaps width/height in layout params if needed.

## Java-to-C++ Translation Guide
*   **Layout Logic**: Custom layout container logic.
