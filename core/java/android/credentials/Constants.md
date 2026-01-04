# Constants - Reverse Engineering Documentation

## Executive Summary
`Constants` contains general constants for the Credential Manager service that do not fit into specific data structures.

## Constants
- **`SUCCESS_CREDMAN_SELECTOR` (0)**: Success result code for the selector UI.
- **`FAILURE_CREDMAN_SELECTOR` (-1)**: Failure/Cancellation result code for the selector UI.

## Java-to-C++ Translation Guide
- Define as `constexpr` or `enum` in a common header.
