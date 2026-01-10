# FragmentContainer - Reverse Engineering Documentation

## Executive Summary
`FragmentContainer` is an abstract base class that provides a callback mechanism for a `Fragment` to access its view hierarchy from its host (Activity or another Fragment).

## Architecture Overview
*   **Methods**:
    *   `onFindViewById(int id)`: Retrieve a view.
    *   `onHasView()`: Check if container holds views.
    *   `instantiate(...)`: Factory method for fragments.

## Java-to-C++ Translation Guide
*   Abstract class / Interface.

## Implementation Risks
*   None.
