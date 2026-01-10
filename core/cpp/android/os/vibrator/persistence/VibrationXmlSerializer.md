# VibrationXmlSerializer - Reverse Engineering Documentation

## Executive Summary
`VibrationXmlSerializer` is the counterpart to the parser, converting `VibrationEffect` objects back into their XML string representation.

## Architecture Overview
-   **Pattern**: Serializer.
-   **Dependencies**: `TypedXmlSerializer`, `VibrationEffectSerializer` (internal).
-   **Flags**: `FLAG_PRETTY_PRINT` (indentation), `FLAG_ALLOW_HIDDEN_APIS` (serialization of non-public SDK effects).

## API Reference
-   `serialize(VibrationEffect, Writer)`: Main entry point.

## Java-to-C++ Translation Guide
-   **Relevance**: Mainly used for debugging (dumping state) or persisting user customizations.
-   **Logic**: Iterates segments and writes corresponding tags (`<primitive-effect>`, etc.).

## Implementation Risks
-   **Completeness**: Must support all Segment types (Step, Ramp, Pwle, Primitive, Prebaked) to be useful.
