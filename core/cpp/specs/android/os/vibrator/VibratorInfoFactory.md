# VibratorInfoFactory - Reverse Engineering Documentation

## Executive Summary
`VibratorInfoFactory` is a utility class for creating `VibratorInfo` instances. Its primary capability is merging multiple `VibratorInfo` objects into a single `MultiVibratorInfo`.

## Architecture Overview
-   **Pattern**: Factory.
-   **Logic**:
    -   0 infos -> Empty/Default info.
    -   1 info -> Return it directly.
    -   >1 infos -> Return `MultiVibratorInfo`.

## API Reference
-   `create(int id, VibratorInfo[] vibrators)`: The sole public entry point.

## Java-to-C++ Translation Guide
-   **Relevance**: Useful if the C++ layer mimics the Java object hierarchy for managing composite vibrators.
