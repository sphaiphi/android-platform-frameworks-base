# SharedPreferences - Reverse Engineering Documentation

## Executive Summary
`SharedPreferences` is an interface for accessing and modifying preference data (key-value pairs) returned by `Context.getSharedPreferences`. It allows persistent storage of primitive data types.

## Architecture Overview
- **Type:** Interface.
- **Implementer:** `SharedPreferencesImpl` (internal class, likely not in this directory).

## Inner Interfaces
- `OnSharedPreferenceChangeListener`: Callback for changes.
- `Editor`: Interface for modifying values (transactional).

## API Reference
- `Map<String, ?> getAll()`
- `String getString(String key, String defValue)`
- ... (getters for other types)
- `Editor edit()`
- `void registerOnSharedPreferenceChangeListener(...)`

## Editor API
- `Editor putString(...)`
- `Editor remove(String key)`
- `Editor clear()`
- `boolean commit()`: Synchronous save.
- `void apply()`: Asynchronous save.

## Java-to-C++ Translation Guide
- **Interface**: Pure virtual classes.
- **Map**: `std::map`.
- **Variant**: Values are variants.

## Implementation Risks
- **Concurrency**: `apply()` writes to disk asynchronously. `commit()` writes synchronously. Handling the backing file safely (atomic writes) is crucial.