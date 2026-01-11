# PropertyReader - Reverse Engineering Documentation

## Executive Summary
Interface for reading property values. Called by `InspectionCompanion` with the IDs obtained from `PropertyMapper`.

## Key Methods
*   `readBoolean`, `readInt`, `readColor`, etc.: Accepts ID and value.

## Java-to-C++ Translation Guide
*   **Interface**: Virtual class.
