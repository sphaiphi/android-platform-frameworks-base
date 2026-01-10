# Html - Reverse Engineering Documentation

## Executive Summary
Converts HTML strings to `Spanned` text (styled text) and vice versa.

## Core Functionality
- **`fromHtml`**: Parses HTML using a SAX parser (TagSoup). Converts tags (`<b>`, `<i>`, `<font>`, `<a>`, `<img>`, etc.) into spans (`StyleSpan`, `URLSpan`, `ImageSpan`).
- **`toHtml`**: Converts `Spanned` text into HTML markup by iterating over spans.

## Key Classes
- **`HtmlToSpannedConverter`**: Handles the SAX callbacks (`startElement`, `endElement`, `characters`) to build the `SpannableStringBuilder`. Uses a stack-like approach (via `getLast` logic) to handle nested tags.

## Java-to-C++ Translation Guide
- **Parsing**: Requires an HTML parser. Libxml2 HTML module or a lightweight parser.
- **Span Generation**: Mapping HTML tags to Span structs.
- **CSS Colors**: Parses basic CSS colors.
