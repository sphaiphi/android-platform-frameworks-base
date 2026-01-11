# Spannable - Reverse Engineering Documentation

## Executive Summary
Interface for text that supports attaching and detaching markup objects (spans). Extends `Spanned`.

## API Reference
- **`setSpan(Object what, int start, int end, int flags)`**: Attaches a span.
- **`removeSpan(Object what)`**: Detaches a span.

## Java-to-C++ Translation Guide
- **Core Concept**: Defines the mutation methods for markup.
