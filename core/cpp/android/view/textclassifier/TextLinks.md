# TextLinks - Reverse Engineering Documentation

## Executive Summary
Result of `generateLinks`. Contains a collection of `TextLink` objects identifying entities in the text.

## Data Model
*   **Links**: List of `TextLink`.
*   **Text**: The full text analyzed.

## Nested Classes
*   **TextLink**: A single link (start, end, entity scores).
*   **Request**: Arguments for `generateLinks`.
*   **TextLinkSpan**: A `ClickableSpan` implementation that handles clicking on a link.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
