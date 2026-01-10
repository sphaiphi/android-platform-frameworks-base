# FontConfig - Reverse Engineering Documentation

## Executive Summary
Data class representing the system font configuration (parsed from `fonts.xml` or similar). It describes font families, aliases, and specific font files.

## Data Model
- **`mFamilies`** (`List<FontFamily>`): List of font families.
- **`mAliases`** (`List<Alias>`): List of aliases (e.g. "sans-serif-medium" -> "sans-serif" weight 500).

### Inner Class: `Font`
- Represents a single font file.
- Fields: `mFile`, `mOriginalFile`, `mPostScriptName`, `mStyle` (weight, slant), `mFontVariationSettings`, `mTtcIndex`.

### Inner Class: `FontFamily`
- Represents a collection of `Font`s (e.g., Regular, Bold, Italic for "Roboto").
- Fields: `mFonts` (List), `mLocaleList`, `mVariant` (Compact/Elegant).

### Inner Class: `Alias`
- Maps a name to an original family with a target weight.

## Java-to-C++ Translation Guide
- **Structs**: Direct mapping to C++ structs/classes.
- **Usage**: Used by the font loading engine (Minikin) to initialize the system font collection.
