# ContactsInternal - Reverse Engineering Documentation

## Executive Summary
`ContactsInternal` provides internal helper methods for the Contacts provider, specifically for starting "Quick Contact" dialogs and handling enterprise (work profile) contact lookup intents.

## Architecture Overview
- **Role**: Helper class.
- **Dependencies**: `ContactsContract`, `DevicePolicyManager`.

## Detailed Functionality
-   **Quick Contact**: `startQuickContactWithErrorToast` parses the URI to determine if it refers to a managed profile contact and delegates to `DevicePolicyManager` if so.
-   **URI Parsing**: Checks for lookup keys starting with `ENTERPRISE_CONTACT_LOOKUP_PREFIX`.

## API Reference
-   `startQuickContactWithErrorToast(...)`.

## Java-to-C++ Translation Guide
-   **Intent Handling**: Logic involves parsing Intent data URIs and potentially modifying them or calling system services.
