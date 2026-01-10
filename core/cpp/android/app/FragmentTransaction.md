# FragmentTransaction - Reverse Engineering Documentation

## Executive Summary
`FragmentTransaction` is the API for performing a set of fragment operations (add, remove, replace, hide, show, attach, detach) atomically.

## Architecture Overview
*   **Type**: Abstract Class.
*   **Implementation**: `BackStackRecord`.

## Detailed Functionality
*   **Operations**: `add`, `replace`, `remove`, `hide`, `show`, `detach`, `attach`.
*   **Configuration**: `setCustomAnimations`, `setTransition`, `setTransitionStyle`.
*   **Back Stack**: `addToBackStack`, `disallowAddToBackStack`.
*   **Commit**: `commit`, `commitAllowingStateLoss`, `commitNow`.

## Java-to-C++ Translation Guide
*   Command pattern interface.

## Implementation Risks
*   None (Interface definition).
