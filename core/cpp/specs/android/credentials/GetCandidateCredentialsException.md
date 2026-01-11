# GetCandidateCredentialsException - Reverse Engineering Documentation

## Executive Summary
Exception thrown when `getCandidateCredentials` operation fails.

## Key Types
- `TYPE_UNKNOWN`
- `TYPE_NO_CREDENTIAL`: No candidates found.
- `TYPE_USER_CANCELED`
- `TYPE_INTERRUPTED`

## Architecture
- Extends `Exception`.
- Holds a type string and message.

## Java-to-C++ Translation Guide
- Map to `std::expected<GetCandidateCredentialsResponse, GetCandidateCredentialsException>`.
