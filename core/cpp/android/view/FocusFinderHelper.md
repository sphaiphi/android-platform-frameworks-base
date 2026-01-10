# FocusFinderHelper - Reverse Engineering Documentation

## Executive Summary
`FocusFinderHelper` is a restricted helper class designed primarily for unit testing. It provides access to the internal algorithms of `FocusFinder` (which are normally package-private or private) to verify geometric calculations like "beam overlap" and "major axis distance."

## Architecture Overview
*   **Role**: Test-only proxy for `FocusFinder`.
*   **Wrapper**: Holds a reference to a `FocusFinder` instance and delegates calls to it.

## Detailed Functionality
*   **`isBetterCandidate()`**: Exposes the logic for comparing two potential focus targets.
*   **`beamBeats()`**: Exposes the beam-overlap priority logic.
*   **`majorAxisDistance()`**: Calculates the raw distance between two rectangles on a specific axis.

## Java-to-C++ Translation Guide
*   **Utility**: In a C++ project, similar functionality might be exposed via `friend` classes in unit tests rather than a dedicated helper class.

## Implementation Risks
*   **Accessibility**: This class is `@hide` and should never be used in production application code.
