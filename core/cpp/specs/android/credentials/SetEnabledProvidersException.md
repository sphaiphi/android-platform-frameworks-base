# SetEnabledProvidersException - Reverse Engineering Documentation

## Executive Summary
Exception thrown when `setEnabledProviders` fails.

## Architecture
- Extends `Exception`.
- Holds a type string (`mType`) and message.

## Java-to-C++ Translation Guide
- Map to `std::expected<void, SetEnabledProvidersException>`.
