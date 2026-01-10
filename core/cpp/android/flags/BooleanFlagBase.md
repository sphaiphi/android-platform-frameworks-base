# BooleanFlagBase - Reverse Engineering Documentation

## Executive Summary
`BooleanFlagBase` is the abstract base class for all boolean-typed feature flags.

## Architecture Overview
- **Inheritance**: Implements `Flag<Boolean>`.
- **Subclasses**: `BooleanFlag`, `DynamicBooleanFlag`, `FusedOffFlag`, `FusedOnFlag`.

## Detailed Functionality
- **Common State**: Stores namespace, name, label, description, and category.
- **Metadata**: Methods to set and retrieve human-readable metadata.
- **`toString()`**: Formats as `namespace.name[default]`.

## Java-to-C++ Translation Guide
- **C++**: Base class for flag types. Should hold common string properties.

## Source Reference
Defined in `BooleanFlagBase.java`.
