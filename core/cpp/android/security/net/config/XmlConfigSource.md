# XmlConfigSource - Reverse Engineering Documentation

## Executive Summary
Parses the Network Security Config from an XML resource.

## Functionality
*   **Parsing**: Handles `<network-security-config>`, `<base-config>`, `<domain-config>`, `<debug-overrides>`, `<pin-set>`, `<trust-anchors>`, `<certificates>`.
*   **Inheritance**: Builds the config hierarchy (base -> domain -> specific domain).
*   **Debug Overrides**: Loads separate debug config if application is debuggable.

## Java-to-C++ Translation Guide
*   XML Parsing logic (using `libxml2` or similar in C++).
*   Must match the parsing rules exactly (attribute names, nesting).
