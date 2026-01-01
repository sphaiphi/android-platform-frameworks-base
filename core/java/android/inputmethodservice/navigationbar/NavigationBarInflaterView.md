# NavigationBarInflaterView - Reverse Engineering Documentation

## Executive Summary
`NavigationBarInflaterView` is responsible for parsing a layout string (e.g., "back;home;recent") and inflating the corresponding buttons into the navigation bar layout. It supports different layouts for portrait/landscape.

## Detailed Functionality
*   **Layout Parser**: Splits string by `;` (gravity) and `,` (buttons).
*   **Inflation**: Inflates specific layouts based on keywords (`BACK`, `IME_SWITCHER`, etc.).
*   **Dispatcher**: Registers inflated views with `ButtonDispatcher`.

## Java-to-C++ Translation Guide
*   **Dynamic Layout**: Mechanism to construct UI from string definitions.
