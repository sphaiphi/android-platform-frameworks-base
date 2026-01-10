# PropertyMapper - Reverse Engineering Documentation

## Executive Summary
Interface for mapping property names (strings) to integer IDs. Consumed by `InspectionCompanion`.

## Key Methods
*   `mapBoolean`, `mapInt`, `mapColor`, etc.: Returns a unique ID for the property name/attribute ID pair.
*   Handles collisions (`PropertyConflictException`).

## Java-to-C++ Translation Guide
*   **Interface**: Virtual class.
