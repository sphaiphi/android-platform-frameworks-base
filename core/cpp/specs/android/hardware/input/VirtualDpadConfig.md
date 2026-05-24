# VirtualDpadConfig - Reverse Engineering Documentation

## Executive Summary
`VirtualDpadConfig` holds configuration for creating a `VirtualDpad`.

## Architecture Overview
- **Inheritance**: Extends `VirtualInputDeviceConfig`.
- **Parcelable**.
- **Builder Pattern**.

## Detailed Functionality
- Minimal config, relies mostly on the base class (Vendor ID, Product ID, Display ID).

## Java-to-C++ Translation Guide
- Struct/Class inheriting base config.
