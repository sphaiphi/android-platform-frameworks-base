# Linkify - Reverse Engineering Documentation

## Executive Summary
Utility to automatically add `URLSpan`s to text matching patterns (Web URLs, Emails, Phone numbers, Maps).

## Functionality
- **`addLinks`**: Scans text with Regex patterns and adds spans.
- **Patterns**: Uses `Patterns` class (not provided here but standard Android util).
- **Filters**: Supports `MatchFilter` (e.g. excluding email domains) and `TransformFilter`.

## Java-to-C++ Translation Guide
- **Regex**: Uses `java.util.regex`. C++ `std::regex` or `re2` (used by Android/Chrome) should be used.
