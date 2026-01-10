# StaticInspectionCompanionProvider - Reverse Engineering Documentation

## Executive Summary
Implementation of `InspectionCompanionProvider` that looks for inner classes named `InspectionCompanion` or generated classes with the suffix `$InspectionCompanion`.

## Key Algorithms
*   **`provide`**:
    1.  Constructs class name: `cls.getName() + "$InspectionCompanion"`.
    2.  Attempts to load class via `ClassLoader`.
    3.  Instantiates if found and assignable.

## Java-to-C++ Translation Guide
*   **Reflection**: Relies heavily on Java reflection (`Class.forName`, `newInstance`). C++ requires a manual registry or compile-time generation (macros/templates) as it lacks runtime reflection of this dynamism.
