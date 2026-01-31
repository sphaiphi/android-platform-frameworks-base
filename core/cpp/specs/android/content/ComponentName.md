# android.content.ComponentName - Reverse Engineering Documentation

## Executive Summary
`ComponentName` is an identifier for a specific application component. It encapsulates two strings: the package name and the class name.

## Architecture Overview
- **Structure**: Immutable value object.
- **Fields**:
    - `mPackage`: String (NonNull)
    - `mClass`: String (NonNull)

## Detailed Functionality

### Construction
- Basic constructor requires NonNull `pkg` and `cls`.
- `createRelative(pkg, cls)`: If `cls` starts with `.`, prepends `pkg`.

### String Representation
- `flattenToString()`: Returns `package/class`.
- `flattenToShortString()`: Returns `package/class`, but abbreviates class if it's a suffix of package.
- `unflattenFromString(String)`: Reverse of `flattenToString()`. Handles the `./` relative notation.

### Equality & Comparison
- `equals()`: Compares package and class strings.
- `compareTo()`: Compares package string first, then class string.

## Data Model
- `mPackage`: `java.lang.String`
- `mClass`: `java.lang.String`

## API Reference
- `getPackageName()`: Returns the package name.
- `getClassName()`: Returns the full class name.
- `getShortClassName()`: Returns the class name, abbreviated if possible.

## Java-to-C++ Translation Guide
- **String Handling**: Use `std::string` or `std::string_view`.
- **Parceling**:
    - `writeToParcel`: Write `mPackage` then `mClass` as strings.
    - `readFromParcel`: Read `mPackage` then `mClass`.
- **Immutability**: The C++ class should be immutable after construction.

## Test Cases & Validation
- Construction with nulls throws NPE.
- `createRelative` logic for `.` prefix.
- `flatten`/`unflatten` round-trip.
- Parcel round-trip.

## Implementation Risks
- String interning in Java (`intern()`) is used during unparcelling. C++ might need a string pool if performance is critical, but likely not necessary for a value object.