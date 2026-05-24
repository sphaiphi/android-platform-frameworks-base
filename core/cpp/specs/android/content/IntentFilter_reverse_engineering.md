# android.content.IntentFilter - Reverse Engineering Documentation

## Executive Summary
`IntentFilter` is a structured description of Intent values to be matched. It matches against actions, categories, and data (type, scheme, authority, path) in an Intent. It is a fundamental component for Android's implicit intent resolution mechanism. The C++ implementation must provide high-performance matching capabilities to support system services.

## Architecture Overview
- **Class:** `IntentFilter`
- **Package:** `android.content`
- **Implements:** `Parcelable`
- **Key Relationships:**
    - Uses `PatternMatcher` for path and scheme-specific part matching.
    - Uses `Uri` (from `android.net`) for data resolution.
    - Used by `PackageManager` and `ActivityManager` for resolving components.

## Detailed Functionality

### Core Matching Rules
A match is based on three conditions:
1.  **Action:** If the filter specifies actions, the Intent's action must match one of them. If the filter specifies no actions, it only matches Intents with no action.
2.  **Category:** The Intent must have *all* categories specified in the filter. Extra categories in the filter not in the Intent are ignored.
3.  **Data:** Both the data type and the data scheme+authority+path must match.

### Constants (Match Results)
The `match` methods return an integer composed of a **Category** and an **Adjustment**.

**Categories (High 8 bits):**
- `MATCH_CATEGORY_EMPTY` (0x0100000): Matched intent with no data.
- `MATCH_CATEGORY_SCHEME` (0x0200000): Matched scheme.
- `MATCH_CATEGORY_HOST` (0x0300000): Matched scheme + authority host.
- `MATCH_CATEGORY_PORT` (0x0400000): Matched scheme + authority host + port.
- `MATCH_CATEGORY_PATH` (0x0500000): Matched scheme + authority + path.
- `MATCH_CATEGORY_SCHEME_SPECIFIC_PART` (0x0580000): Matched scheme + ssp.
- `MATCH_CATEGORY_TYPE` (0x0600000): Matched MIME type.

**Error Codes (Negative values):**
- `NO_MATCH_TYPE` (-1)
- `NO_MATCH_DATA` (-2)
- `NO_MATCH_ACTION` (-3)
- `NO_MATCH_CATEGORY` (-4)

### Data Structures

#### 1. Actions
- **Type:** `ArraySet<String>` (Java) -> `std::vector<std::string>` or `std::set<std::string>` (C++)
- **Behavior:** Unique set of action strings.
- **Match Logic:** `matchAction(String action)` checks for existence.

#### 2. Categories
- **Type:** `ArrayList<String>` (Java) -> `std::vector<std::string>` (C++)
- **Behavior:** List of category strings.
- **Match Logic:** `matchCategories(Set<String> categories)` ensures all categories in the *Intent* are present in the *Filter*. **Note:** This is the reverse of standard set inclusion. The *Intent's* categories must be a subset of the *Filter's* categories? **Correction:** The JavaDoc says: "Categories match if *all* of the categories in the Intent match categories given in the filter." This means Intent Categories $\subseteq$ Filter Categories.

#### 3. Data Schemes
- **Type:** `ArrayList<String>`
- **Behavior:** List of schemes (e.g., "http", "content"). Case-sensitive in implementation (though RFC says otherwise).
- **Special Case:** If no schemes are specified, it matches Intents with no scheme, or "content:" or "file:" schemes (MIME-type only match).

#### 4. Data Types (MIME)
- **Type:** `ArrayList<String>`
- **Behavior:** List of MIME types (e.g., "image/png", "audio/*").
- **Wildcards:** Supports partial types (e.g., "audio/*").
- **Match Logic:** Checked in `matchData`.

#### 5. Data Authorities
- **Type:** `ArrayList<AuthorityEntry>`
- **Inner Class `AuthorityEntry`:**
    - `mHost`: String (can optionally start with `*` for wildcard).
    - `mPort`: int.
    - `match(Uri data)`: Checks host and port.

#### 6. Data Paths
- **Type:** `ArrayList<PatternMatcher>`
- **Inner Class `PatternMatcher`:**
    - `mPath`: String.
    - `mType`: LITERAL, PREFIX, GLOB.
    - `match(String path)`: Checks path against pattern.

## API Reference (Key Methods)

### `void addAction(String action)`
Adds an action to the filter.

### `void addCategory(String category)`
Adds a category to the filter.

### `void addDataScheme(String scheme)`
Adds a scheme. Note: Java implementation interns strings.

### `void addDataType(String type)`
Adds a MIME type. Throws exception if malformed.

### `void addDataAuthority(String host, String port)`
Adds an authority.

### `void addDataPath(String path, int type)`
Adds a path with a matching type (LITERAL, PREFIX, GLOB).

### `int match(ContentResolver resolver, Intent intent, boolean resolve, String logTag)`
**Not strictly part of IntentFilter state, but the primary logic.**
This usually delegates to `matchAction`, `matchCategories`, and `matchData`.

### `int matchData(String type, String scheme, Uri data)`
The core data matching logic.
- **Parameters:**
    - `type`: MIME type from Intent.
    - `scheme`: Scheme from Intent.
    - `data`: URI from Intent.
- **Logic:**
    1. Check Schemes: If filter has schemes, Intent scheme must match one.
    2. Check Authorities: If matched scheme, and filter has authorities, Intent authority must match.
    3. Check Paths: If matched authority, and filter has paths, Intent path must match.
    4. Check Types: If filter has types, Intent type must match (handling wildcards).

## Java-to-C++ Translation Guide

### Data Types
- `String` -> `std::string`
- `ArrayList` -> `std::vector`
- `ArraySet` -> `std::vector` (with sorted unique constraint) or `std::set`
- `Uri` -> `android::net::Uri` (Need to verify if this exists or use a simple struct for now)
- `PatternMatcher` -> `android::os::PatternMatcher` (Need to implement or stub)

### Memory Management
- Java uses GC. C++ must use RAII/Smart Pointers.
- `IntentFilter` is generally a value object, but complex internal lists might benefit from `std::shared_ptr` if shared, though standard `std::vector` ownership is preferred for simplicity and cache locality.

### Thread Safety
- Java implementation is **not** thread-safe for mutations.
- C++ implementation should follow suit (not thread-safe).

### Parcelable
- Implement `android::os::Parcelable` interface.
- `writeToParcel(Parcel* parcel)`
- `readFromParcel(const Parcel* parcel)`

## Implementation Risks
1.  **MIME Type Parsing:** Java has logic to handle `*` in MIME types. C++ needs to replicate this "partial type" logic accurately.
2.  **Wildcard Matching:** `AuthorityEntry` and `PatternMatcher` have specific wildcard rules (glob, prefix, suffix) that must be exact.
3.  **Case Sensitivity:** Java doc explicitly states Android matching is case-sensitive, violating RFCs. C++ must enforce this case-sensitivity.

## Questions for C++ Team
- Is there an existing `PatternMatcher` implementation in C++?
- Is there an existing `Uri` class in C++? (If not, `matchData` signature might need `std::string scheme, std::string authority, std::string path` breakdown).
