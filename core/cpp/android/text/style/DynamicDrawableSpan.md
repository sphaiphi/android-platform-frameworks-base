# DynamicDrawableSpan - Reverse Engineering Documentation

## Executive Summary
Base class for spans replacing text with a drawable (e.g. `ImageSpan`). Supports vertical alignment.

## Properties
- **`mVerticalAlignment`**: Bottom, Baseline, or Center.

## Java-to-C++ Translation Guide
- **Replacement**: Implements `ReplacementSpan`. Measures and draws the drawable.
