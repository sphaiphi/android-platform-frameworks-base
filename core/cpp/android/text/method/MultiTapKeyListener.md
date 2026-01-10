# MultiTapKeyListener - Reverse Engineering Documentation

## Executive Summary
Handles 12-key (T9) text entry. Pressing a key multiple times cycles through characters (e.g., 2 -> a -> b -> c -> 2).

## Logic
- **`sRecs`**: Maps key codes to character sequences.
- **Timeout**: Uses a `Handler` to commit the character after a delay.
- **Span**: Uses `TextKeyListener.ACTIVE` span to track the currently composing character.

## Java-to-C++ Translation Guide
- **Legacy**: Mostly relevant for feature phones.
- **Timer**: Requires platform timer mechanism.
