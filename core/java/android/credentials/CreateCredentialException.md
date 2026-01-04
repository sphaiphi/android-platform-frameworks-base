# CreateCredentialException - Reverse Engineering Documentation

## Executive Summary
Exception thrown when `createCredential` operation fails.

## Key Types
- `TYPE_UNKNOWN`
- `TYPE_NO_CREATE_OPTIONS`: No provider could handle the creation request.
- `TYPE_USER_CANCELED`: User cancelled the flow.
- `TYPE_INTERRUPTED`: System interruption.

## Architecture
- Extends `Exception`.
- Holds a type string and message.

## Java-to-C++ Translation Guide
- Map to `std::expected<CreateCredentialResponse, CreateCredentialException>`.
