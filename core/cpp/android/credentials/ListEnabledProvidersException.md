# ListEnabledProvidersException - Reverse Engineering Documentation

## Executive Summary
Exception thrown when listing enabled providers fails.

## Architecture
- Extends `Exception`.
- Holds a type string (`mType`) and message.
- No specific constants defined in class, uses generic types.

## Java-to-C++ Translation Guide
- Map to `std::expected<ListEnabledProvidersResponse, ListEnabledProvidersException>`.
