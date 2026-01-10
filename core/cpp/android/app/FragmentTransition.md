# FragmentTransition - Reverse Engineering Documentation

## Executive Summary
`FragmentTransition` handles the complexity of Fragment Transitions (using the Transition framework). It calculates which fragments are entering/exiting based on the transaction, configuring shared elements, and starting the transitions.

## Architecture Overview
*   **Helper Class**: Static methods used by `FragmentManagerImpl`.
*   **Logic**:
    *   `startTransitions`: Entry point.
    *   `calculateFragments`: Determines IN/OUT fragments.
    *   `configureTransitionsOrdered` / `configureTransitionsReordered`.

## Detailed Functionality
*   **Mapping**: Maps shared element views.
*   **Epicenter**: Calculates transition epicenter.
*   **Merging**: Merges Enter/Exit/SharedElement transitions into a `TransitionSet`.
*   **Execution**: Calls `TransitionManager.beginDelayedTransition`.

## Java-to-C++ Translation Guide
*   **Complex Logic**: High logic density involving View hierarchies and Transition properties.
*   **Dependencies**: Requires `Transition` framework port.

## Implementation Risks
*   **View Hierarchy**: Manipulates view visibility and targets deeply.
