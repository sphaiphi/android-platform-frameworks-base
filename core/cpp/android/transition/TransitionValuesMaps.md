# TransitionValuesMaps - Reverse Engineering Documentation

## Executive Summary
Internal helper structure to organize `TransitionValues` by different keys for efficient matching.

## Data Model
-   **`viewValues`**: Map<View, TransitionValues>
-   **`idValues`**: SparseArray<View>
-   **`itemIdValues`**: LongSparseArray<View>
-   **`nameValues`**: Map<String, View>

## Java-to-C++ Translation Guide
-   **Indexing**: Just a set of hashmaps/vectors to index the views in the scene.
