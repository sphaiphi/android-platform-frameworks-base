# ComponentName - Reverse Engineering Documentation

## Executive Summary
`ComponentName` uniquely identifies an application component (Activity, Service, BroadcastReceiver, ContentProvider). It consists of a package name and a class name.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`, `Cloneable`, `Comparable<ComponentName>`.
- **Immutability:** Immutable class.

## Detailed Functionality
- **Flattening**: Can be flattened to a string (`package/class` or `package/.shortClass`).
- **Unflattening**: Parsed back from string.
- **Short Class Name**: If class name starts with package name, it can be abbreviated with `.ClassName`.

## Data Model
- `mPackage`: `String` (Non-null).
- `mClass`: `String` (Non-null).

## API Reference
- `public String getPackageName()`
- `public String getClassName()`
- `public static ComponentName unflattenFromString(String str)`
- `public String flattenToString()`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.
- **String Handling**: String manipulation for flatten/unflatten.

## Implementation Risks
- **Null Safety**: Constructors throw NPE if args are null.
