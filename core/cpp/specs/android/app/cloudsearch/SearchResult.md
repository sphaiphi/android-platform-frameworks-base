# SearchResult - Reverse Engineering Documentation

## Executive Summary
`SearchResult` represents a single item in a search response. It contains displayable information like title, snippet, and score, along with a `Bundle` of extra information used for specific content types (apps, web links, etc.).

## Architecture Overview
*   **Pattern**: Immutable Data Object / Builder Pattern.
*   **Role**: Data Container.
*   **Key Dependencies**: `android.os.Bundle` for extensible attributes.

## Detailed Functionality

### Core Fields
*   **Title**: Display title (String).
*   **Snippet**: Short description/snippet (String).
*   **Score**: Ranking score (float).
*   **ExtraInfos**: `Bundle` containing metadata.

### Constants (Extra Info Keys)
Extensive list of keys for the `ExtraInfos` bundle, defining specific data types expected in the bundle:
*   **App Metadata**: Domain URL, Icon, Developer Name, Size, Rating, IARC, Review Count, etc.
*   **Actions**: Install button intent, App card intent.
*   **Web**: Web URL, Web Icon.

**Java-Specific Notes**:
*   **`Bundle`**: Heavily used here to store heterogeneous metadata without strict schema in the class itself.
*   **`@StringDef`**: Used for keys.

**C++ Implementation Guidance**:
*   The C++ implementation must provide a robust way to access `ExtraInfos`.
*   Accessors for specific "Extra Info" keys might be helpful helper methods, rather than just exposing the raw Bundle.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `title` | `String` | Title text. |
| `snippet` | `String` | Snippet text. |
| `score` | `float` | Relevance score. |
| `extraInfos` | `Bundle` | Key-value metadata. |

## API Reference

### Getters
*   `getTitle()`
*   `getSnippet()`
*   `getScore()`
*   `getExtraInfos()`

### Builder
*   Constructs with Title and ExtraInfos (mandatory).
*   Setters for Snippet and Score.

## Java-to-C++ Translation Guide

| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `String` | `std::string` / `String16` | |
| `Bundle` | `android::os::Bundle` | |
| `float` | `float` | Standard IEEE 754. |

## Test Cases & Validation
1.  **Bundle Integrity**:
    *   Put various types (String, Double, Boolean, Parcelable) into ExtraInfos.
    *   Parcel/Unparcel.
    *   Verify types and values are preserved.

## Implementation Risks
*   **Type Safety in Bundle**: The `Bundle` relies on string keys and dynamic types. C++ code reading this must carefully check types before casting to avoid runtime errors (e.g., expecting a Double for `EXTRAINFO_APP_STAR_RATING` but getting a Float or String).

## Questions for C++ Team
*   Should the C++ class provide typed getters for the known `EXTRAINFO_` keys (e.g., `getAppStarRating()`) or just expose the generic Bundle?
