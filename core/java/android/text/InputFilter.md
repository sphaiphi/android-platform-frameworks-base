# InputFilter - Reverse Engineering Documentation

## Executive Summary
Interface to filter or transform text insertions/replacements in an `Editable`.

## API Reference
- **`filter(CharSequence source, int start, int end, Spanned dest, int dstart, int dend)`**:
    - Returns `null` to accept changes.
    - Returns `""` to reject changes.
    - Returns modified `CharSequence` to transform.

## Standard Implementations
- **`AllCaps`**: Forces uppercase. Uses `TextUtils.toUpperCase`.
- **`LengthFilter`**: Limits maximum length.

## Java-to-C++ Translation Guide
- **Callback**: C++ equivalent would be a callback or virtual interface attached to the TextEdit control.
