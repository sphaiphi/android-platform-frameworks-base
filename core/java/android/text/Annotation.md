# Annotation - Reverse Engineering Documentation

## Executive Summary
`Annotation` is a text span that stores a key-value pair of strings. It implements `ParcelableSpan`, allowing it to be persisted (e.g., across process boundaries or in `Bundle`s). It is typically used to attach metadata to text regions.

## Data Model
- **`mKey`** (`String`): The key of the annotation.
- **`mValue`** (`String`): The value of the annotation.

## API Reference
- **`Annotation(String key, String value)`**: Constructor.
- **`Annotation(Parcel src)`**: Reconstructs from Parcel.
- **`getSpanTypeId()`**: Returns `TextUtils.ANNOTATION`.
- **`writeToParcel(Parcel dest, int flags)`**: Writes key and value strings.
- **`getKey()`**: Returns the key.
- **`getValue()`**: Returns the value.

## Java-to-C++ Translation Guide
- **Struct**: Simple struct with two string fields.
- **Serialization**: Implement standard Android Parcelable pattern in C++ (write/read strings).
