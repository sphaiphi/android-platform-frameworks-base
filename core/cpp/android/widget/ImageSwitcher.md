# ImageSwitcher - Reverse Engineering Documentation

## Executive Summary
`ImageSwitcher` is a specialized `ViewSwitcher` designed for images. It provides helper methods to set images by URI, Resource ID, or Drawable.

## Architecture Overview
*   **Inheritance**: `ViewSwitcher` -> `ImageSwitcher`.
*   **Role**: Animated Image Transitioner.

## Detailed Functionality
*   **Factory**: Expects the `ViewFactory` to produce `ImageView`s.
*   **Setters**: `setImageResource`, `setImageURI`, `setImageDrawable` call the corresponding method on the *next* view and then switch.

## Java-to-C++ Translation Guide
*   **Convenience**: This is just a helper wrapper around `ViewSwitcher`.

## Implementation Risks
*   None.
