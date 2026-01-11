# ConfirmationAlreadyPresentingException - Reverse Engineering Documentation

## Executive Summary
Exception thrown when `ConfirmationPrompt.presentPrompt()` is called while another prompt is already being presented.

## Java-to-C++ Translation Guide
*   Map to a specific `service_specific_exception` or a custom error code in the C++ result type (e.g., `std::expected` or `android::base::Result`).
*   Corresponds to `AndroidProtectedConfirmation.ERROR_OPERATION_PENDING`.
