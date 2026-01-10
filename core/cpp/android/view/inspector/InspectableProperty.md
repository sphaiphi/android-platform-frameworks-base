# InspectableProperty - Reverse Engineering Documentation

## Executive Summary
Annotation used to mark getters on inspectable nodes (Views) to expose properties to the layout inspector.

## Data Model
*   **Attributes**: `name`, `attributeId`, `hasAttributeId`, `valueType`.
*   **Enums/Flags**: `enumMapping`, `flagMapping`.
*   **ValueType**: Enumeration for types (NONE, INFERRED, INT_ENUM, INT_FLAG, COLOR, GRAVITY, RESOURCE_ID).

## Java-to-C++ Translation Guide
*   **Annotation**: Maps to metadata or a reflection system in C++ (if one exists), or manual registration.
