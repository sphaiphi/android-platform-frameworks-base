# HeadToHeadTemplateData - Reverse Engineering Documentation

## Executive Summary
`HeadToHeadTemplateData` is a specialized template for sports scores or competitive events. It displays two competitors with icons and text, alongside the standard base card info.

## Architecture Overview
- **Package**: `android.app.smartspace.uitemplatedata`
- **Parent**: `BaseTemplateData`.
- **Template Type**: `UI_TEMPLATE_HEAD_TO_HEAD`.

## Detailed Functionality

### Data Extension
Adds specific fields for the match-up:
- Title
- Competitor 1 (Icon, Text)
- Competitor 2 (Icon, Text)
- Action

### Serialization
- Calls `super`.
- Writes Title, Icons, Texts, Action in order.

## Data Model
Standard `Text`, `Icon`, and `TapAction` fields.

## Java-to-C++ Translation Guide
- Straightforward mapping of fields.

## Test Cases & Validation
- Nullability checks on all fields.
