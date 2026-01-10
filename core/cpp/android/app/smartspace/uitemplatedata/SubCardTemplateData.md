# SubCardTemplateData - Reverse Engineering Documentation

## Executive Summary
`SubCardTemplateData` extends `BaseTemplateData` to add a simple secondary card containing just an icon and text.

## Architecture Overview
- **Package**: `android.app.smartspace.uitemplatedata`
- **Parent**: `BaseTemplateData`.
- **Template Type**: `UI_TEMPLATE_SUB_CARD`.

## Detailed Functionality
Adds `mSubCardIcon`, `mSubCardText`, and `mSubCardAction`.

## Data Model
- `Icon` (Non-null)
- `Text` (Nullable)
- `TapAction` (Nullable)

## Java-to-C++ Translation Guide
- Standard inheritance and field mapping.

## Test Cases & Validation
- `mSubCardIcon` is required (Non-null).
