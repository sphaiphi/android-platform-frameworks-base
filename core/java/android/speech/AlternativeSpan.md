# AlternativeSpan - Reverse Engineering Documentation

## Executive Summary
`AlternativeSpan` is a data class (Parcelable) used in the Android Speech Recognition API. It represents a list of alternative hypotheses for a specific substring (span) of a recognized speech result. This allows recognizers to provide corrections or alternatives for specific parts of a sentence without replacing the entire result.

## Data Model

### Core Fields
- `mStartPosition` (int): The inclusive start index of the span in the original recognized string. Must be non-negative.
- `mEndPosition` (int): The exclusive end index of the span in the original recognized string. Must be greater than `mStartPosition`.
- `mAlternatives` (List\<String\>): A non-empty list of alternative strings that could replace the span defined by `mStartPosition` and `mEndPosition`.

## API Reference

### Constructors
- `AlternativeSpan(int startPosition, int endPosition, @NonNull List<String> alternatives)`: Validates inputs (start >= 0, start < end, list not empty) and initializes the object.

### Accessors
- `getStartPosition()`: Returns start index.
- `getEndPosition()`: Returns end index.
- `getAlternatives()`: Returns the list of alternative strings.

### Standard Methods
- `toString()`: Returns string representation.
- `equals(Object)`: Equality check based on fields.
- `hashCode()`: Hash code generation.
- `writeToParcel(Parcel, int)`: Serialization for IPC.
- `describeContents()`: Returns 0.

## Java-to-C++ Translation Guide

### Class Mapping
- Map to a struct or class `AlternativeSpan`.

### Fields
- `int32_t start_position`
- `int32_t end_position`
- `std::vector<std::string> alternatives`

### Serialization
- Implement `Parcelable` read/write logic matching the Java implementation:
    - Read/Write `int` for start position.
    - Read/Write `int` for end position.
    - Read/Write string list (size then strings).

### Validation
- Ensure C++ constructors enforce `start_position >= 0`, `start_position < end_position`, and `!alternatives.empty()`.
