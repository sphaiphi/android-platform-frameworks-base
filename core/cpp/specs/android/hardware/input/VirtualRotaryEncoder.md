# VirtualRotaryEncoder - Reverse Engineering Documentation

## Executive Summary
`VirtualRotaryEncoder` allows injecting rotary scroll events (like a physical rotating dial).

## Architecture Overview
- **Inheritance**: Extends `VirtualInputDevice`.
- **Flag**: Guarded by `FLAG_VIRTUAL_ROTARY`.

## Detailed Functionality
- **sendScrollEvent**: Injects `VirtualRotaryEncoderScrollEvent`.

## Java-to-C++ Translation Guide
- Wrapper for IPC.
