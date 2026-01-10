# FragmentManagerNonConfig - Reverse Engineering Documentation

## Executive Summary
`FragmentManagerNonConfig` is a simple container class used to pass retained state (fragments that are not destroyed across config changes) between `Activity` instances.

## Architecture Overview
*   **Data**: List of `Fragment` and List of `FragmentManagerNonConfig` (children).

## Java-to-C++ Translation Guide
*   Struct/Class.

## Implementation Risks
*   None.
