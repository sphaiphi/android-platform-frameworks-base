# StrictJarManifestReader - Reverse Engineering Documentation

## Executive Summary
Helper class for reading JAR manifests. Handles the specific syntax of manifests (key: value, line continuations).

## Logic
*   **`readHeader`**: Reads a key-value pair, handling multi-line values.
*   **`readName`**: Parses attribute name.
*   **`readValue`**: Parses attribute value, concatenating continuation lines.

## Java-to-C++ Translation Guide
*   **State Machine**: Simple parser state machine.
