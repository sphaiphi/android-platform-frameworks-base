# InlineSuggestion - Reverse Engineering Documentation

## Executive Summary
Represents a single inline suggestion (e.g., Autofill chip on keyboard). Can be inflated into a View.

## Architecture
*   **Content Provider**: Uses `IInlineContentProvider` to fetch content from the source (e.g., Autofill Service) via SurfaceControl.
*   **Inflation**: `inflate` method renders the content.

## Java-to-C++ Translation Guide
*   **SurfaceControl**: Heavy UI/Graphics dependency.
