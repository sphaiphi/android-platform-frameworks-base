# Formatter - Reverse Engineering Documentation

## Executive Summary
Utilities for formatting file sizes (bytes) and IP addresses.

## API Reference
- **`formatFileSize`**: "10 MB".
- **`formatShortFileSize`**: Shorter precision.
- **`formatIpAddress`**: Deprecated IPv4 formatting.

## Logic
- **Rounding**: `RoundedBytesResult` calculates value and units (KB, MB, GB, etc.). Uses SI (1000) or IEC (1024) units based on flags.
- **Localization**: Uses `MeasureFormat` (ICU) for localized unit strings.

## Java-to-C++ Translation Guide
- **ICU**: Use `MeasureFormat`.
- **Math**: Replicate the rounding logic.
