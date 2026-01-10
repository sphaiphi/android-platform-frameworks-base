# CaptioningManager - Reverse Engineering Documentation

## Executive Summary
System service for managing video captioning preferences (style, font scale, enabled state).

## Data Model
*   **CaptionStyle**: Inner class defining visual properties (colors, edge types).
*   **Settings**: Reads from `Settings.Secure`.

## Key Methods
*   **`isEnabled`**: Checks if captioning is globally enabled.
*   **`getUserStyle`**: Returns the composite `CaptionStyle`.

## Java-to-C++ Translation Guide
*   **Settings Observer**: Uses `ContentObserver` to watch for settings changes.
