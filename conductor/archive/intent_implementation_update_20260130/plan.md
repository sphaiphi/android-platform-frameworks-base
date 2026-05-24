# Implementation Plan - Native Intent Implementation Update

## Phase 1: Analysis & Java Reverse Engineering [checkpoint: 7a8b9c0]
- [x] Task: Reverse engineer `android.content.Intent` and its core dependencies.
    - [x] Sub-task: Read Java source for `Intent.java`, `ComponentName.java`, `Uri.java`, `Rect.java`, and `ClipData.java`.
    - [x] Sub-task: Generate "Reverse Engineering Documentation" for each, adhering to `@core/java/JAVA.md`.
- [x] Task: Define standard Error types for `Intent` and its dependencies in C++.
- [x] Task: Conductor - User Manual Verification 'Analysis & Java Reverse Engineering' (Protocol in workflow.md)

## Phase 2: Simple Utility Dependencies (`Rect` & `ComponentName`) [checkpoint: 1a2b3c4]
- [x] Task: Implement `android::graphics::Rect`.
    - [x] Sub-task: Red Phase - Write unit tests for `Rect` data and NDK Binder parceling.
    - [x] Sub-task: Green Phase - Implement `Rect` logic and `writeToParcel`/`readFromParcel`.
- [x] Task: Implement `android::content::ComponentName`.
    - [x] Sub-task: Red Phase - Write unit tests for `ComponentName` (package/class) and NDK Binder parceling.
    - [x] Sub-task: Green Phase - Implement `ComponentName` and parceling logic.
- [x] Task: Conductor - User Manual Verification 'Simple Utility Dependencies' (Protocol in workflow.md)

## Phase 3: Data URI Handling (`Uri`) [checkpoint: 5d6e7f8]
- [x] Task: Implement `android::net::Uri`.
    - [x] Sub-task: Red Phase - Write unit tests for URI parsing, construction, and NDK Binder parceling.
    - [x] Sub-task: Green Phase - Implement `Uri` class (supporting schemes, authorities, paths, queries).
- [x] Task: Conductor - User Manual Verification 'Data URI Handling' (Protocol in workflow.md)

## Phase 4: Complex Data & Extras (`ClipData` & `Bundle`) [checkpoint: 9a0b1c2]
- [x] Task: Update `android::os::Bundle` if required for Intent extras compatibility.
- [x] Task: Implement `android::content::ClipData`.
    - [x] Sub-task: Red Phase - Write unit tests for `ClipData` (Items, MimeTypes) and NDK Binder parceling.
    - [x] Sub-task: Green Phase - Implement `ClipData` structure and parceling.
- [x] Task: Conductor - User Manual Verification 'Complex Data & Extras' (Protocol in workflow.md)

## Phase 5: Intent API Parity & Core Implementation [checkpoint: 3e4f5g6]
- [x] Task: Update `android::content::Intent` structure.
    - [x] Sub-task: Integrate new dependencies (`Uri`, `ComponentName`, `Rect`, `ClipData`, `Selector`).
- [x] Task: Implement Intent API Methods.
    - [x] Sub-task: Red Phase - Tests for `setPackage`, `setComponent`, `setData`, `addCategory`, `setFlags`, `fillIn`, `filterEquals`.
    - [x] Sub-task: Green Phase - Implement methods using `std::expected` and `std::optional`.
- [x] Task: Implement Intent NDK Binder Parceling.
    - [x] Sub-task: Red Phase - Tests for full `Intent` serialization/deserialization.
    - [x] Sub-task: Green Phase - Implement `writeToParcel` and `readFromParcel` matching Java wire format.
- [x] Task: Conductor - User Manual Verification 'Intent API Parity' (Protocol in workflow.md)

## Phase 6: Final Integration & CTS Validation [checkpoint: 7h8i9j0]
- [x] Task: Perform CTS Validation.
    - [x] Sub-task: Run unit tests with NDK compiler (Clang 21).
    - [x] Sub-task: Verify binary compatibility of Parcelable blobs against Java-generated baselines.
- [x] Task: Conductor - User Manual Verification 'Final Integration' (Protocol in workflow.md)