# TextPaint - Reverse Engineering Documentation

## Executive Summary
Extension of `Paint` that adds fields specific to text layout and span styling.

## Data Fields
- **`bgColor`**: Background color.
- **`baselineShift`**: Vertical shift.
- **`linkColor`**: Color for links.
- **`underlineColor`, `underlineThickness`**: Custom underline styles.
- **`density`**: Display density.

## Java-to-C++ Translation Guide
- **Struct**: Extend the base `Paint` struct in C++ to include these extra fields.
