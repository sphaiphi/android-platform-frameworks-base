# SubImageTemplateData - Reverse Engineering Documentation

## Executive Summary
`SubImageTemplateData` extends `BaseTemplateData` to display a list of texts alongside a list of images (which can represent a GIF animation).

## Architecture Overview
- **Package**: `android.app.smartspace.uitemplatedata`
- **Parent**: `BaseTemplateData`.
- **Template Type**: `UI_TEMPLATE_SUB_IMAGE`.

## Detailed Functionality
- `mSubImageTexts`: List of text lines.
- `mSubImages`: List of frames/images.
- `mSubImageAction`: Tap action.

## Data Model
- `List<Text>`
- `List<Icon>`
- `TapAction`

## Java-to-C++ Translation Guide
- Map Lists to `std::vector`.

## Test Cases & Validation
- Lists are Non-null but can be empty (though Builder checks usually enforce validity, here they are Objects.requireNonNull).
