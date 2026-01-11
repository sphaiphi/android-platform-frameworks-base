# RecognitionSupport - Reverse Engineering Documentation

## Executive Summary
`RecognitionSupport` is a data class (Parcelable) that encodes the level of support a `SpeechRecognizer` provides for a specific request. It details supported languages (installed, pending, online) for the recognition task.

## Data Model

### Core Fields (Lists of Strings)
- `mInstalledOnDeviceLanguages`: Languages ready for on-device use.
- `mPendingOnDeviceLanguages`: Languages scheduled for download.
- `mSupportedOnDeviceLanguages`: Languages supported but needing download.
- `mOnlineLanguages`: Languages supported via remote (server) implementation.

## API Reference

### Builder
- `Builder()`
- `setInstalledOnDeviceLanguages(List<String>)` / `addInstalledOnDeviceLanguage(String)`
- `setPendingOnDeviceLanguages(List<String>)` / `addPendingOnDeviceLanguage(String)`
- `setSupportedOnDeviceLanguages(List<String>)` / `addSupportedOnDeviceLanguage(String)`
- `setOnlineLanguages(List<String>)` / `addOnlineLanguage(String)`
- `build()`

### Accessors
- `getInstalledOnDeviceLanguages()`
- `getPendingOnDeviceLanguages()`
- `getSupportedOnDeviceLanguages()`
- `getOnlineLanguages()`

### Standard Methods
- `toString()`, `equals()`, `hashCode()`.
- Parcelable implementation.

## Java-to-C++ Translation Guide

### Class Mapping
- Struct or class `RecognitionSupport`.

### Fields
- `std::vector<std::string> installed_on_device_languages`
- `std::vector<std::string> pending_on_device_languages`
- `std::vector<std::string> supported_on_device_languages`
- `std::vector<std::string> online_languages`

### Serialization
- Implement `Parcelable` logic reading/writing the string lists.
