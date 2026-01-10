# WebResourceResponse - Reverse Engineering Documentation

## Executive Summary
`WebResourceResponse` allows the application to provide custom response data for an intercepted request.

## Detailed Functionality
*   **Constructors**: Takes MimeType, Encoding, and InputStream.
*   **Status**: Can set Status Code and Reason Phrase.
*   **Headers**: Can set response headers.
*   **Data**: Provides an `InputStream` for the body.

## Java-to-C++ Translation Guide
*   **URLResponse**: Maps to a synthesized URL response in the network stack. The `InputStream` must be bridged to a data pipe or stream reader in C++.
