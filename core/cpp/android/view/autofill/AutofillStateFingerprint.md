# AutofillStateFingerprint - Reverse Engineering Documentation

## Executive Summary
Helper class to store and compute fingerprints of autofillable views. Used to handle relayouts (e.g., when the UI changes while autofill is active) to try and map old field IDs to new ones or verify if the view is the same.

## Logic
*   **Fingerprint**: Computed hash based on View properties (id, input type, hint, position relative to neighbors, etc.).
*   **`attemptRefill`**: Tries to find views in the current hierarchy that match stored fingerprints of failed fills and re-applies autofill.

## Java-to-C++ Translation Guide
*   **Hashing**: Hash combination logic.
*   **View Access**: Accesses View properties.
