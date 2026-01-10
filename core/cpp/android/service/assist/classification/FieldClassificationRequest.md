# FieldClassificationRequest - Reverse Engineering Documentation

## Executive Summary
`FieldClassificationRequest` is a data class (Parcelable) that wraps the `AssistStructure` sent to the `FieldClassificationService`.

## Data Model

### Fields
*   `mAssistStructure`: `AssistStructure` (NonNull) - The snapshot of the view hierarchy to be analyzed.

## API Reference

### Getters
*   `AssistStructure getAssistStructure()`

### Construction
*   Constructor taking `AssistStructure`.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Standard `Parcelable`.
*   **C++**: `android::Parcelable`. `AssistStructure` is a heavy object; ensure the C++ Parcelable implementation handles it correctly (it likely has its own C++ equivalent or is passed as a StrongBinder token depending on implementation, but `AssistStructure` usually travels as a large payload).

## Implementation Notes
*   Generated using `DataClass`.
*   Immutable.
