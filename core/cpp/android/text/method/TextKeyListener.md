# TextKeyListener - Reverse Engineering Documentation

## Executive Summary
The main KeyListener. Delegates to `QwertyKeyListener` or `MultiTapKeyListener` based on keyboard type. Manages settings (Auto-cap, Auto-text, etc.).

## Logic
- **`getKeyListener`**: Factory logic to pick specific listener.
- **`updatePrefs`**: Observes system settings.

## Java-to-C++ Translation Guide
- **Controller**: Central controller for hardware keyboard input.
