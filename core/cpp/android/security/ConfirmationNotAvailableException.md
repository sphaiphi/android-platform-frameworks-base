# ConfirmationNotAvailableException - Reverse Engineering Documentation

## Executive Summary
Exception thrown when `ConfirmationPrompt` cannot be displayed because the environment lacks facilities (e.g., no hardware support) or an incompatible service (Accessibility) is running.

## Java-to-C++ Translation Guide
*   Map to error code.
*   Corresponds to `AndroidProtectedConfirmation.ERROR_UNIMPLEMENTED` or logic checks in `ConfirmationPrompt`.
