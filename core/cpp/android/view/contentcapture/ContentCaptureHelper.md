# ContentCaptureHelper - Reverse Engineering Documentation

## Executive Summary
Static helper class for logging, string redaction (PII protection), and collection conversion.

## Key Methods
*   **`getSanitizedString`**: Returns "length_chars" instead of actual text if PII might be involved (though implementation here looks like it always redacts).
*   **`setLoggingLevel`**: Configures `sDebug` and `sVerbose`.

## Java-to-C++ Translation Guide
*   **Static Utils**: Direct translation to static functions/namespace.
