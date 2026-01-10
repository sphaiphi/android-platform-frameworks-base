# LocaleConfig - Reverse Engineering Documentation

## Executive Summary
`LocaleConfig` represents an application's supported locale configuration. It is used to specify which languages an app supports, either via an XML resource file referenced in the manifest or dynamically provided as an override. This information is primarily used for per-app language preferences introduced in Android 13.

## Architecture Overview
- **Data Source**: 
    1. Static: XML file with `<locale-config>` element.
    2. Dynamic: Set via `LocaleManager.setOverrideLocaleConfig`.
- **Core Components**:
    - `LocaleList mLocales`: The actual list of supported locales.
    - `Locale mDefaultLocale`: Optional default locale for the app.
    - `int mStatus`: Tracking the success or failure of reading/parsing the config.
- **Serialization**: Implements `Parcelable` for IPC.

## Detailed Functionality

### Constructor(Context context)
**Purpose**: Initializes the `LocaleConfig` by checking for overrides and then falling back to the manifest-defined XML.
**Algorithm**:
1. Tries to retrieve the override config from `LocaleManager`.
2. If no override exists, reads the `android:localeConfig` resource ID from the application's metadata.
3. If a resource ID is found, calls `parseLocaleConfig` to extract the data.

### parseLocaleConfig(XmlResourceParser parser, Resources res)
**Purpose**: Parses the XML structure to extract the list of supported language tags.
**Algorithm**:
1. Locates the root `<locale-config>` tag.
2. Extracts the `defaultLocale` attribute if present.
3. Iterates through child `<locale>` tags and collects their `name` attributes.
4. Converts the collection of names into a `LocaleList`.

### isSameLocaleConfig(LocaleConfig other)
**Purpose**: Compares two `LocaleConfig` objects for equality, regardless of the order of locales in the list.
**Logic**: Sorts the language tags of both lists and performs a list comparison.

## API Reference
- `public LocaleList getSupportedLocales()`: Returns the list of supported locales.
- `public Locale getDefaultLocale()`: Returns the optional default locale.
- `public int getStatus()`: Returns the initialization status (`SUCCESS`, `NOT_SPECIFIED`, `PARSING_FAILED`).
- `public boolean containsLocale(Locale locale)`: Checks if a specific locale is supported.

## Java-to-C++ Translation Guide
- **XML Parsing**: Use `libxml2` or a similar C++ XML library to parse the `<locale-config>` structure.
- **Locale Handling**: Map to `std::locale` or `android::LocaleList` in the native layer.
- **Metadata Access**: Use the NDK `AAssetManager` and `APackageManager` equivalents to access application resources and manifest metadata.

## Implementation Risks
- **Backward Compatibility**: Ensure that the C++ implementation handles cases where the XML resource is missing or malformed gracefully, matching the Java `mStatus` behavior.
- **Locale Matching**: Use `LocaleList.matchesLanguageAndScript` logic to ensure consistency with Android's locale resolution algorithms.
