# MailTo.java - Reverse Engineering Documentation

## Executive Summary
`MailTo` is a URL parser specifically designed for the `mailto:` URI scheme (RFC 2368). It extracts standard email headers like `to`, `cc`, `subject`, and `body` from a raw URI string.

## Architecture Overview
- **Type**: Utility/Parser Class
- **Package**: `android.net`
- **Dependencies**: `android.net.Uri` (for parsing the scheme-specific part).

## Detailed Functionality

### Parsing Logic
1.  **Validation**: Checks if the URL starts with `mailto:`.
2.  **Scheme Stripping**: Removes the scheme to parse the rest.
3.  **Query Parsing**: Uses `Uri` to parse the query string (headers).
    -   Splits by `&` and then `=`.
    -   Decodes keys and values.
    -   Stores them in a `HashMap` (keys lowercased).
4.  **Path Handling**: The "path" part of the URI (before `?`) is treated as the primary `to` address. It's appended to any `to` header found in the query.

### Data Model
-   `mHeaders`: `HashMap<String, String>` storing parsed headers. Keys are lowercase.

### API Reference
-   `isMailTo(String url)`: Static check.
-   `parse(String url)`: Static factory.
-   `getTo()`, `getCc()`, `getSubject()`, `getBody()`: Accessors for common headers.
-   `getHeaders()`: Access to the raw map.

## Java-to-C++ Translation Guide

### Implementation
```cpp
class MailTo {
public:
    static bool isMailTo(const std::string& url);
    static MailTo parse(const std::string& url);

    std::string getTo() const;
    // ... other getters

private:
    std::map<std::string, std::string> headers_;
};
```

### Parsing
Can utilize a generic URI parser (if available in C++ codebase) or simple string manipulation.
-   Find `?`. Split parameters.
-   URL-decode is essential.

## Edge Cases
-   **Multiple To Addresses**: The class joins the path `to` and the query `to` with a comma (logic is inside `parse`).
-   **Case Sensitivity**: Header keys are normalized to lowercase.
