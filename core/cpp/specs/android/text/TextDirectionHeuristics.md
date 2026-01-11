# TextDirectionHeuristics - Reverse Engineering Documentation

## Executive Summary
Standard implementations of `TextDirectionHeuristic`.

## Implementations
- **`LTR`**: Always LTR.
- **`RTL`**: Always RTL.
- **`FIRSTSTRONG_LTR`**: LTR unless first strong Bidi char is RTL.
- **`FIRSTSTRONG_RTL`**: RTL unless first strong Bidi char is LTR.
- **`ANYRTL_LTR`**: RTL if *any* RTL char exists, else LTR.
- **`LOCALE`**: Based on Locale script.

## Logic
- Scans text for Bidi character types (Strong L, Strong R, Weak, etc.) and decides based on the strategy.

## Java-to-C++ Translation Guide
- **ICU**: Use `u_charDirection` to get character properties. Reimplement the scanning logic.
