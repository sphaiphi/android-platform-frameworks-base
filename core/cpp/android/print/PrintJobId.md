# PrintJobId - Reverse Engineering Documentation

## Executive Summary
`PrintJobId` is a unique identifier for a print job, typically backed by a UUID string.

## Architecture Overview
- **Type**: Parcelable Data Class (final).
- **Implementation**: Wraps a UUID string.

## Java-to-C++ Translation Guide
-   **String Wrapper**: Simple string wrapper.
