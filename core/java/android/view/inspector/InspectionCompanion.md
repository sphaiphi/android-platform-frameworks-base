# InspectionCompanion - Reverse Engineering Documentation

## Executive Summary
Interface for companion objects that handle property mapping and reading for a specific class. Used by the inspector to efficiently read properties.

## Key Methods
*   `mapProperties(PropertyMapper)`: Maps string property names to integer IDs.
*   `readProperties(T inspectable, PropertyReader)`: Reads values from the object and passes them to the reader using the mapped IDs.

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual class or template policy.
