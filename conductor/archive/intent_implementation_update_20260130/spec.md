# Specification: Native Intent Implementation Update

## 1. Overview
This track focuses on updating the C++ implementation of `android::content::Intent` to match the feature set and behavior of the Java `android.content.Intent` class. The goal is to achieve high API parity, ensure strict IPC compatibility for cross-language communication, and leverage modern C++23 standards for safety and performance. This includes implementing necessary dependencies like `ComponentName`, `Uri`, `Rect`, and `ClipData` to support the full `Intent` structure.

## 2. Functional Requirements

### 2.1 Intent Structure & Data Parity
The `Intent` class must support the following fields and their corresponding accessors/mutators:
*   **Action:** `std::string` (already partially present, needs verification).
*   **Data:** `android::net::Uri` (New dependency).
*   **Type:** `std::string` (MIME type).
*   **Identifier:** `std::string`.
*   **Package:** `std::string`.
*   **Component:** `android::content::ComponentName` (New dependency).
*   **Flags:** `int32_t` (Bitmask).
*   **Categories:** `std::set<std::string>` or `std::vector<std::string>`.
*   **Extras:** `android::os::Bundle` (Existing, may need updates).
*   **SourceBounds:** `android::graphics::Rect` (New dependency).
*   **ClipData:** `android::content::ClipData` (New dependency).
*   **Selector:** `android::content::Intent` (Recursive structure).

### 2.2 IPC Support (Parcelable)
*   **Serialization:** Implement `writeToParcel(AParcel* parcel)` to match the Java `Intent.writeToParcel` logic byte-for-byte.
*   **Deserialization:** Implement `readFromParcel(const AParcel* parcel)` to match the Java `Intent.readFromParcel` logic.
*   **Dependencies:** All dependent classes (`Uri`, `ComponentName`, `Rect`, `ClipData`) must also implement the `Parcelable` interface (or NDK equivalent) to support deep object graphs.

### 2.3 API Methods
Implement C++ equivalents for key Java methods, including:
*   `setPackage`, `getPackage`
*   `setComponent`, `getComponent`
*   `setData`, `getData`, `setDataAndType`
*   `addCategory`, `removeCategory`, `hasCategory`
*   `setFlags`, `addFlags`, `getFlags`
*   `fillIn` (Basic implementation)
*   `filterEquals`
*   `cloneFilter`

## 3. Non-Functional Requirements
*   **Modern C++:** Use `std::expected` for error handling (e.g., parsing errors, missing fields). Use `std::optional` for nullable fields.
*   **Memory Management:** Use strict RAII. No raw pointers for ownership.
*   **Testing:** Comprehensive unit tests (`gtest`) verifying:
    *   Field access/mutation.
    *   Parcel read/write compatibility (ideally against "golden" blobs generated from Java).
    *   Equality checks (`filterEquals`).

## 4. Dependencies to Implement
To support `Intent`, the following must be implemented with Parcelable support:
1.  `android::content::ComponentName`
2.  `android::net::Uri`
3.  `android::graphics::Rect`
4.  `android::content::ClipData`

## 5. Acceptance Criteria
*   [ ] `Intent` class structure matches Java definition.
*   [ ] All dependencies (`ComponentName`, `Uri`, `Rect`, `ClipData`) are implemented and testable.
*   [ ] `writeToParcel` and `readFromParcel` successfully round-trip complex Intent objects.
*   [ ] Error handling uses `std::expected`.
*   [ ] Unit tests pass for all new functionality.
