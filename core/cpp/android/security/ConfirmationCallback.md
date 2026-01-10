# ConfirmationCallback - Reverse Engineering Documentation

## Executive Summary
`ConfirmationCallback` is an abstract class used to receive the result of a `ConfirmationPrompt`. It defines methods for success, dismissal, cancellation, and errors.

## Architecture Overview
*   **Package**: `android.security`
*   **Type**: Abstract Class (Public)
*   **Usage**: Passed to `ConfirmationPrompt.presentPrompt()`.

## API Reference

### Public Methods
*   `void onConfirmed(@NonNull byte[] dataThatWasConfirmed)`: Called when the user approves the prompt. `dataThatWasConfirmed` is a CBOR-encoded map containing the prompt text and extra data, signed by the hardware.
*   `void onDismissed()`: Called when the user rejects/dismisses the prompt.
*   `void onCanceled()`: Called when the prompt is canceled by the application.
*   `void onError(Throwable e)`: Called when a system error occurs.

## Java-to-C++ Translation Guide
*   This would likely translate to a pure virtual class (interface) in C++ or a struct of `std::function` callbacks.
*   **CBOR Data**: The `dataThatWasConfirmed` blob requires a CBOR parser/validator on the receiving side (Relying Party), but for this class, it's just a byte buffer (`std::vector<uint8_t>`).
