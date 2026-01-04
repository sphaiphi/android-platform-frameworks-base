# RecognizerResultsIntent - Reverse Engineering Documentation

## Executive Summary
`RecognizerResultsIntent` defines constants for Intents used to display speech recognition results, specifically for voice search. It defines how recognition candidates should be accompanied by URLs, HTML, or HTTP headers for rendering.

## API Reference

### Actions
- `ACTION_VOICE_SEARCH_RESULTS`: Intent sent to display search results.

### Result Extras
- `EXTRA_VOICE_SEARCH_RESULT_STRINGS`: Parallel array of recognition candidates (String list).
- `EXTRA_VOICE_SEARCH_RESULT_URLS`: Parallel array of URLs for candidates.
- `EXTRA_VOICE_SEARCH_RESULT_HTML`: Parallel array of HTML content for candidates. Uses `inline:` URI scheme.
- `EXTRA_VOICE_SEARCH_RESULT_HTML_BASE_URLS`: Parallel array of base URLs for the HTML content.
- `EXTRA_VOICE_SEARCH_RESULT_HTTP_HEADERS`: Parallel array of `Bundle` containing HTTP headers for the URLs.

### URI Schemes
- `URI_SCHEME_INLINE`: "inline" - used for `EXTRA_VOICE_SEARCH_RESULT_HTML`.

## Java-to-C++ Translation Guide

### Implementation
- Define these as static constants in a namespace (e.g., `android::speech::RecognizerResultsIntent`).
- These are key-value pairs for use with `Intent` and `Bundle`.
