# ResourceCursorAdapter - Reverse Engineering Documentation

## Executive Summary
`ResourceCursorAdapter` is a `CursorAdapter` that inflates views from XML resources. It simplifies `newView` by just inflating a specific layout ID.

## Architecture Overview
*   **Inheritance**: `CursorAdapter` -> `ResourceCursorAdapter`.

## Detailed Functionality
*   **`newView`**: `inflater.inflate(mLayout, ...)`
*   **`newDropDownView`**: `inflater.inflate(mDropDownLayout, ...)`

## Java-to-C++ Translation Guide
*   **Simplified**: Basic wrapper.

## Implementation Risks
*   None.
