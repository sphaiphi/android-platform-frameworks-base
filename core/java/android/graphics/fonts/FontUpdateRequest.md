# FontUpdateRequest - Reverse Engineering Documentation

## Executive Summary
`FontUpdateRequest` is an internal `Parcelable` class used to transmit update operations over Binder to the `FontManagerService`. It unifies "File Update" and "Family Update" operations into a single type.

## Architecture Overview
-   **Variant Type**: Acts like a tagged union (discriminated union).
    -   `TYPE_UPDATE_FONT_FILE` (0): Contains `ParcelFileDescriptor` + Signature.
    -   `TYPE_UPDATE_FONT_FAMILY` (1): Contains `Family` definition.
-   **Inner Classes**:
    -   `Font`: Internal representation of a font entry (PostScript name, style, index, variation settings). Supports XML read/write.
    -   `Family`: Internal representation of a family (Name + List of `Font`). Supports XML read/write.

## Detailed Functionality
-   **Constructors**: Specialized constructors initialize the object in one of the two modes.
-   **Serialization**:
    -   `writeToParcel`: Writes type tag, then appropriate fields.
    -   `readFromXml` / `writeToXml`: Helper methods for persisting family configurations to XML.

## Java-to-C++ Translation Guide
-   **Union**: Map this to a `std::variant` or a struct with an enum type field in C++.
-   **XML Parsing**: The XML methods use `XmlPullParser`. C++ implementation would need an XML parser (e.g., libxml2 or tinyxml) to handle the configuration files.

## Source Reference
Defined in `FontUpdateRequest.java` and `FontUpdateRequest.aidl`.
