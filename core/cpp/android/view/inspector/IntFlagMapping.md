# IntFlagMapping - Reverse Engineering Documentation

## Executive Summary
Helper class to map integer values to sets of string names for flag properties. Used by `PropertyMapper`.

## Data Model
*   **Flag**: Inner class holding `mask`, `target`, `name`.
*   **List**: List of Flags.

## Key Algorithms
*   **`get(int value)`**: Iterates flags, checks `(value & mask) == target`, adds name to set if true.

## Java-to-C++ Translation Guide
*   **Bit Manipulation**: Standard bitwise operations.
