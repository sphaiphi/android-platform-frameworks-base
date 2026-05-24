# AutofillOptions - Reverse Engineering Documentation

## Executive Summary
`AutofillOptions` encapsulates configuration options for Autofill in a given package. It controls logging levels, compatibility mode, and augmented autofill allowlisting.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Relationship:** Passed from system service to app on creation.

## Detailed Functionality
- **`isAugmentedAutofillEnabled(Context context)`**: Checks if the specific context (activity) is allowlisted for augmented autofill.
- **`isAutofillDisabledLocked(ComponentName componentName)`**: Checks if autofill is temporarily disabled for an activity (backoff mechanism).

## Data Model
- `loggingLevel`: `int`
- `compatModeEnabled`: `boolean`
- `augmentedAutofillEnabled`: `boolean`
- `whitelistedActivitiesForAugmentedAutofill`: `ArraySet<ComponentName>`
- `appDisabledExpiration`: `long`
- `disabledActivities`: `ArrayMap<String, Long>`

## API Reference
- `public boolean isAugmentedAutofillEnabled(@NonNull Context context)`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard Parcelable mapping.
- **Collections**: `ArraySet` -> `std::set` or `std::unordered_set`. `ArrayMap` -> `std::map` or `std::unordered_map`.

## Implementation Risks
- **System Clock**: Uses `SystemClock.elapsedRealtime()`. Ensure C++ equivalent uses the same clock source (boot time).
