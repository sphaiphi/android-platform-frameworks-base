# DigitsKeyListener - Reverse Engineering Documentation

## Executive Summary
Input filter for numeric input. Configurable to accept signed or decimal numbers.

## Logic
- **`mSign`**: If true, allows sign (plus/minus) at the start.
- **`mDecimal`**: If true, allows one decimal separator.
- **Locale**: Determines the actual characters for digits, sign, and decimal separator (e.g. comma vs dot).

## Java-to-C++ Translation Guide
- **Filtering**: State machine to enforce "at most one decimal point", "sign only at start".
