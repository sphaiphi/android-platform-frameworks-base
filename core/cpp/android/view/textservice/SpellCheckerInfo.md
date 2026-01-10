# SpellCheckerInfo - Reverse Engineering Documentation

## Executive Summary
Metadata about a Spell Checker Service. It parses the `android.view.textservice.scs` XML resource to extract settings activity name and subtypes.

## Data Model
*   **Service**: `ResolveInfo`.
*   **Identity**: ID, Label, Settings Activity.
*   **Subtypes**: List of `SpellCheckerSubtype`.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **XML Parsing**: Not needed in client-side C++ usually; data would come from Binder.
