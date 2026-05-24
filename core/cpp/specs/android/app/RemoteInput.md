# RemoteInput - Reverse Engineering Documentation

## Executive Summary
`RemoteInput` specifies input to be collected from a user (like a text reply) and passed along with an intent via a `PendingIntent`. It is the core mechanism behind "Direct Reply" in notifications. It supports text entry, predefined choices, and specialized data types (like images or audio).

## Architecture Overview
- **Structure**:
    - `mResultKey`: The key used to retrieve the result from the `Bundle`.
    - `mLabel`: Prompt text shown to the user.
    - `mChoices`: Array of predefined strings for quick replies.
    - `mFlags`: Bitmask including `FLAG_ALLOW_FREE_FORM_INPUT`.
    - `mAllowedDataTypes`: Set of MIME types for non-textual inputs.
    - `mExtras`: Additional metadata.
- **Inheritance**: Implements `Parcelable`.
- **Identity**: Constructed via `RemoteInput.Builder`.

## Detailed Functionality

### Input Collection and Transport
**Purpose**: Bridging user input from the notification shade back to the app.
**Mechanism**:
1. App attaches a `RemoteInput` to a `Notification.Action`.
2. System UI shows a text field.
3. User enters text or selects a choice.
4. System UI puts the result into an `Intent` extra (`EXTRA_RESULTS_DATA`) and triggers the `PendingIntent`.
5. App receives the intent and uses `getResultsFromIntent(intent)` to retrieve the input.

### Data Types and Free Form
**Logic**: 
- `allowFreeFormInput`: If true, user can type anything. If false, they must pick from `mChoices`.
- `mAllowedDataTypes`: Allows the app to request media. Results for these are retrieved via `getDataResultsFromIntent`.

### Static Helpers
**Purpose**: Abstracting the complexity of intent manipulation.
- `addResultsToIntent`: Populates an intent with results (used by SystemUI/collection services).
- `getResultsFromIntent`: Extracts the result bundle (used by the receiving app).
- `setResultsSource`: Tracks if the input was typed or chosen from a list.

## API Reference
- `public String getResultKey()`: Returns lookup key.
- `public CharSequence getLabel()`: Returns user prompt.
- `public static Bundle getResultsFromIntent(Intent intent)`: Helper for result extraction.
- `public static Map<String, Uri> getDataResultsFromIntent(...)`: Helper for media results.

## Java-to-C++ Translation Guide
- **Result Key Mapping**: Use `std::string` or `android::String16` for key management.
- **Intent Manipulation**: C++ implementation must match the key-value structure used in `EXTRA_RESULTS_DATA`.
- **ClipData**: The transfer of results often uses the `ClipData` field of the intent for security and cross-process stability. C++ layer must support `android::content::ClipData`.

## Implementation Risks
- **Key Collisions**: Multiple `RemoteInput` objects in the same action must have unique result keys.
- **Security**: Because results are passed via `PendingIntent`, the C++ receiving logic must verify the source and intent filters.
- **MIME Type Matching**: Handling of `mAllowedDataTypes` requires a robust MIME registry or simple string set comparison.
