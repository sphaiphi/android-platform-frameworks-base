# NoCopySpan - Reverse Engineering Documentation

## Executive Summary
Marker interface. Spans implementing this are NOT copied when `SpannableString` is copied or when a slice is taken. They are typically used for internal state (like `TextWatcher`s or internal layout listeners) that shouldn't be duplicated.

## Java-to-C++ Translation Guide
- **Flag**: A flag in the Span structure indicating "Do Not Copy".
