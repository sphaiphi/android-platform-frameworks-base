# ReplacementTransformationMethod - Reverse Engineering Documentation

## Executive Summary
Base class for simple 1-to-1 character replacements (e.g., newline to space).

## API Reference
- **`getOriginal()`**: Returns chars to replace.
- **`getReplacement()`**: Returns replacement chars.

## Java-to-C++ Translation Guide
- **View**: A view over the source text that swaps specific characters on the fly.
