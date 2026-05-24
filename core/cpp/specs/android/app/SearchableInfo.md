# SearchableInfo - Reverse Engineering Documentation

## Executive Summary
`SearchableInfo` encapsulates the search-related metadata for an activity, as declared in its manifest (via the `android.app.searchable` meta-data tag). It defines how the search interface should appear (label, hint, icon), how suggestions should be fetched (authority, path), and which intents should be fired when a suggestion is selected.

## Architecture Overview
- **Core Attributes**:
    - **UI**: `mLabelId`, `mHintId`, `mIconId`, `mSearchButtonText`, `mSearchMode`.
    - **Input**: `mSearchInputType`, `mSearchImeOptions`.
    - **Suggestions**: `mSuggestAuthority`, `mSuggestPath`, `mSuggestSelection`, `mSuggestIntentAction`, `mSuggestThreshold`.
    - **Voice**: `mVoiceSearchMode`, `mVoiceLanguageId`, `mVoiceMaxResults`.
- **Inner Classes**:
    - `ActionKeyInfo`: Metadata for specific hardware or soft keys mapped to search actions.
- **Inheritance**: Implements `Parcelable`.

## Detailed Functionality

### Metadata Parsing (`getActivityMetaData`)
**Purpose**: Loads searchable info from an activity's manifest.
**Algorithm**:
1. Locates the XML resource pointed to by the `android.app.searchable` meta-data.
2. Uses `getActivityMetaData(Context context, XmlPullParser xml, ...)` to parse the attributes.
3. Maps standard Android XML attributes (e.g., `suggestAuthority`) to internal fields.

### Voice Search Configuration
**Purpose**: Controls the voice search integration.
**Logic**: Tracks flags for showing the voice button and whether it should launch a web search or a local recognizer.

### Action Key Mapping
**Purpose**: Maps keycodes to custom search messages.
**Mechanism**: Uses a `HashMap` to store `ActionKeyInfo` objects, which define what message (`suggestActionMsg`) should be sent when a specific key is pressed while searching.

## API Reference
- `public ComponentName getSearchActivity()`: Returns the activity this info belongs to.
- `public String getSuggestAuthority()`: Returns the suggestion provider ID.
- `public int getSuggestThreshold()`: Returns the min character count for suggestions.
- `public boolean getVoiceSearchEnabled()`: Checks if voice is supported.

## Java-to-C++ Translation Guide
- **XML Parsing**: Use a native XML parser to read the manifest metadata during system initialization.
- **Data Structure**: Map to a C++ `struct` or class with immutable members.
- **Parceling**: Implement standard `writeToParcel` and `readFromParcel` logic using `libbinder`.

## Implementation Risks
- **Metadata Visibility**: Accessing metadata for other packages requires appropriate permissions (`QUERY_ALL_PACKAGES` on newer Android versions).
- **Resource Resolution**: IDs like `mLabelId` must be resolved using the correct activity context to ensure localized strings are loaded correctly.
- **Consistency**: The parsing logic must strictly match the `com.android.internal.R.styleable.Searchable` definitions.
