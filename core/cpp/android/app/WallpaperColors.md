# WallpaperColors - Reverse Engineering Documentation

## Executive Summary
`WallpaperColors` encapsulates the visual color profile of a wallpaper. It identifies the most visually representative colors (Primary, Secondary, Tertiary) and provides "hints" to the system about how to adapt the UI (e.g., whether to use dark text or a dark theme). It uses color quantization and scoring algorithms to extract these colors from bitmaps or drawables.

## Architecture Overview
- **Structure**:
    - `mMainColors`: An ordered list of up to 3 dominant colors.
    - `mAllColors`: A map tracking the population (frequency) of all extracted colors.
    - `mColorHints`: Bitmask of hints (`HINT_SUPPORTS_DARK_TEXT`, `HINT_SUPPORTS_DARK_THEME`).
- **Inheritance**: Implements `Parcelable`.
- **Core Algorithms**:
    - **Quantization**: Uses `CelebiQuantizer` (or `VariationalKMeansQuantizer` on low-ram devices) to reduce the image to a manageable palette.
    - **Scoring**: Ranks colors based on chroma and population frequency.
    - **Luminance Analysis**: Calculates mean luminance to determine if the wallpaper is "bright" or "dark".

## Detailed Functionality

### Color Extraction (`fromBitmap`)
**Purpose**: Generates a color profile from a raw image.
**Algorithm**:
1. Resizes the bitmap to a maximum area (`MAX_WALLPAPER_EXTRACTION_AREA`) to keep processing efficient.
2. Applies quantization to get a list of swatches.
3. Calculates dark hints by analyzing pixels and adjusting for potential wallpaper dimming.
4. Scores and selects the top 3 colors, ensuring they are visually distinct (at least 15 degrees difference in hue).

### UI Adaptation Hints
**Logic**: 
- `HINT_SUPPORTS_DARK_TEXT`: Set if the mean luminance is high enough and there aren't too many dark pixels that would make text unreadable.
- `HINT_SUPPORTS_DARK_THEME`: Set if the primary color's luminance is below a certain threshold (`DARK_THEME_MEAN_LUMINANCE`).

### Serialization
**Mechanism**: Writes the count and ARGB values of main colors, the full color-population map, and the hints to a `Parcel`.

## API Reference
- `public Color getPrimaryColor()`: Most dominant color.
- `public int getColorHints()`: UI adaptation flags.
- `public static WallpaperColors fromBitmap(Bitmap bitmap)`: Extraction trigger.
- `public static WallpaperColors fromDrawable(Drawable drawable)`: Extraction trigger.

## Java-to-C++ Translation Guide
- **Color Library**: Use `android::uirenderer` or a native color manipulation library.
- **Quantization**: Port the `Celebi` or K-Means algorithm to C++.
- **Luminance Math**: Replicate the HSL and luminance calculations using standard color science formulas (e.g., Rec. 709).
- **Matrix/Vector Ops**: Use `std::map` or `std::vector` for the internal palette management.

## Implementation Risks
- **Performance**: pixel-by-pixel analysis is CPU-intensive. C++ implementation should use SIMD instructions if possible and strictly enforce the maximum processing area.
- **Visual Accuracy**: Ensuring that the hue-difference scoring matches the Java implementation is critical for UI consistency across updates.
- **Memory Management**: Bitmaps passed to `fromBitmap` should be handled carefully to avoid duplication.
