# SearchUiManager - Reverse Engineering Documentation

## Executive Summary
`SearchUiManager` serves as the entry point/factory for creating `SearchSession` instances. It is obtained via `Context.getSystemService(Context.SEARCH_UI_SERVICE)`.

## Architecture Overview
-   **Package**: `android.app.search`
-   **Type**: Manager class
-   **Role**: Service wrapper / Factory.

## Detailed Functionality
-   **Constructor**: Takes a `Context`.
-   **createSearchSession**: Instantiates and returns a new `SearchSession` passing the context and `SearchContext`.

## Java-to-C++ Translation Guide
-   This class is primarily a convenience wrapper in Java. In C++, if the usage model differs (e.g., direct binder interaction), this might be merged with the client creation logic.
-   However, to maintain API parity, a similar factory function/class should exist.

## Questions for C++ Team
-   None.
