# AdvancedProtectionFeature - Reverse Engineering Documentation

## Executive Summary
`AdvancedProtectionFeature` is a Parcelable class representing a specific feature within the Advanced Protection Mode. It essentially wraps an integer ID representing the feature.

## Architecture Overview
*   **Package**: `android.security.advancedprotection`
*   **Type**: Class (Parcelable, System API)
*   **Usage**: Returned by `AdvancedProtectionManager.getAdvancedProtectionFeatures()`.

## Data Model
*   `mId` (int): The unique identifier for the feature.

## API Reference
*   `int getId()`: Returns the feature ID.

## Java-to-C++ Translation Guide
*   Can be mapped to a simple struct or class with an integer ID.
*   Parcelable serialization is trivial (just the integer).
