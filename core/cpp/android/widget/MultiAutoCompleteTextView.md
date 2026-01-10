# MultiAutoCompleteTextView - Reverse Engineering Documentation

## Executive Summary
`MultiAutoCompleteTextView` extends `AutoCompleteTextView` to support multiple values (tokens) in a single field, separated by a delimiter (e.g., comma).

## Architecture Overview
*   **Inheritance**: `AutoCompleteTextView` -> `MultiAutoCompleteTextView`.
*   **Component**: `Tokenizer` interface.

## Detailed Functionality
*   **Tokenizer**: Defines how to find the start/end of the current token (e.g., `CommaTokenizer`).
*   **Filtering**: Instead of filtering based on the whole text, it extracts the substring for the current token range and filters based on that.
*   **Replacement**: When an item is selected, it replaces only the current token range.

## Java-to-C++ Translation Guide
*   **String Parsing**: Requires string manipulation to find delimiters.

## Implementation Risks
*   **Spans**: Preserving spans (formatting) when replacing tokens.
