# QuickViewConstants - Reverse Engineering Documentation

## Executive Summary
`QuickViewConstants` defines constants for the `Intent.ACTION_QUICK_VIEW` intent, specifically for the `Intent.EXTRA_QUICK_VIEW_FEATURES` extra.

## Constants
- `FEATURE_VIEW`: "android:view"
- `FEATURE_EDIT`: "android:edit"
- `FEATURE_DELETE`: "android:delete"
- `FEATURE_SEND`: "android:send"
- `FEATURE_DOWNLOAD`: "android:download"
- `FEATURE_PRINT`: "android:print"

## Java-to-C++ Translation Guide
- **Constants**: `static const char*` or `constexpr`.

## Implementation Risks
- None.