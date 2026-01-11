# ActivityNotFoundException - Reverse Engineering Documentation

## Executive Summary
`ActivityNotFoundException` is a runtime exception thrown when a call to start an Activity fails because no activity can be found to handle the given `Intent`.

## Architecture Overview
- **Inheritance:** Extends `RuntimeException`.
- **Relationship:** Thrown by `Context.startActivity()` and related methods.

## Detailed Functionality
- **`ActivityNotFoundException()`**: Default constructor.
- **`ActivityNotFoundException(String name)`**: Constructor with a detail message.

## Data Model
- No internal state beyond standard Exception fields.

## API Reference
- `public ActivityNotFoundException()`
- `public ActivityNotFoundException(String name)`

## Java-to-C++ Translation Guide
- **Exceptions**: C++ uses `try-catch` blocks and exception classes similar to Java.
- **Equivalence**: Should map to a specific error code or a custom exception class in C++ (e.g., `android::ActivityNotFoundException`).

## Implementation Risks
- None. Simple wrapper.
