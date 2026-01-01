# VirtualKeyboardConfig - Reverse Engineering Documentation

## Executive Summary
`VirtualKeyboardConfig` adds keyboard-specific configuration: Language Tag and Layout Type.

## Architecture Overview
- **Inheritance**: Extends `VirtualInputDeviceConfig`.
- **Defaults**: "en-Latn-US", "qwerty".

## Detailed Functionality
- **Language Tag**: BCP-47 tag.
- **Layout Type**: String identifier (e.g., "qwerty", "azerty").

## Java-to-C++ Translation Guide
- Add string fields for language and layout.

## Implementation Risks
- Invalid BCP-47 tags might be rejected by lower layers.
