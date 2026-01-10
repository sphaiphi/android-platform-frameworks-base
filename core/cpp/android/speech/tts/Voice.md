# Voice - Reverse Engineering Documentation

## Executive Summary
`Voice` represents a specific text-to-speech voice provided by an engine. Each engine can offer multiple voices per locale, each with different quality, latency, and connectivity requirements.

## Data Model

### Core Fields
- `mName` (String): Unique identifier for the voice.
- `mLocale` (Locale): The language and region.
- `mQuality` (int): 100 (Very Low) to 500 (Very High).
- `mLatency` (int): 100 (Very Low) to 500 (Very High).
- `mRequiresNetworkConnection` (boolean).
- `mFeatures` (Set\<String\>): Features supported by the voice (e.g., "networkTts").

## API Reference

### Accessors
- `getName()`
- `getLocale()`
- `getQuality()`
- `getLatency()`
- `isNetworkConnectionRequired()`
- `getFeatures()`

### Standard Methods
- `toString()`, `equals()`, `hashCode()`.
- Parcelable implementation.

## Java-to-C++ Translation Guide
- Map to a struct or class `Voice`.
- Use a bitmask or set for features.
- Implement Parcelable read/write logic.
