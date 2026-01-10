# PersistableBundle - Reverse Engineering Documentation

## Executive Summary
`PersistableBundle` is a variant of `Bundle` restricted to values that can be safely persisted to disk (XML) and restored. It disallows `Parcelable`, `Binder`, `Serializable` (except specific types), etc.

## Architecture Overview
-   **Inheritance**: Extends `BaseBundle`.
-   **Constraints**: Only allows: `int`, `long`, `double`, `String`, `int[]`, `long[]`, `double[]`, `String[]`, and nested `PersistableBundle`.
-   **Persistence**: `saveToXml` / `restoreFromXml`.

## Detailed Functionality
-   **XML Format**: Custom XML tag structure (`<bundle>`, `<int>`, `<string>`, etc.) handled by `XmlUtils` or internal logic.
-   **Filtering**: `put*` methods check types. `unparcel` validates contents.

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: `android::os::PersistableBundle` (Binder).
-   **Serialization**: C++ Binder supports `PersistableBundle` natively.
-   **XML**: The C++ implementation of `PersistableBundle` might not have XML serialization logic built-in unless ported from `libs/binder` or `libutils`. In Android, the XML parsing is often done in Java system services.

## Implementation Risks
-   **Invalid Types**: If a `Bundle` is cast to `PersistableBundle` (copy constructor) containing invalid types, they are dropped during XML saving.
