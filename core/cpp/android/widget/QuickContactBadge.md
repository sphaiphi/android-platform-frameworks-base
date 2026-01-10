# QuickContactBadge - Reverse Engineering Documentation

## Executive Summary
`QuickContactBadge` is an `ImageView` that displays a contact's photo. When clicked, it opens the QuickContact dialog (a system dialog showing communication options like call, email, SMS).

## Architecture Overview
*   **Inheritance**: `ImageView` -> `QuickContactBadge`.
*   **Dependencies**: `ContactsContract` API.

## Detailed Functionality
*   **Assignment**: `assignContactUri`, `assignContactFromEmail`, etc.
*   **Query**: If assigned by email/phone, it performs an async query (`QueryHandler`) to find the Contact URI.
*   **Click**: Triggers `QuickContact.showQuickContact`.
*   **Overlay**: Draws a small overlay icon (triangle) to indicate interactivity (deprecated style).

## Java-to-C++ Translation Guide
*   **System Integration**: Depends entirely on the Android Contacts Intent system.

## Implementation Risks
*   **Privacy**: Accessing contacts requires permissions.
