# TransitionValues - Reverse Engineering Documentation

## Executive Summary
A holder for property values of a specific View during a transition.

## Data Model
-   **`view`**: The target View.
-   **`values`**: `Map<String, Object>`. Arbitrary property storage.
-   **`targetedTransitions`**: List of transitions interested in this view.

## Java-to-C++ Translation Guide
-   **Struct**: `struct TransitionValues { View* view; std::map<std::string, std::any> values; ... }`.
