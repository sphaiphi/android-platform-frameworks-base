# Contacts - Reverse Engineering Documentation

## Executive Summary
`Contacts` is the **deprecated** predecessor to `ContactsContract`. It supports the old `contacts` authority.

## Architecture Overview
- **Authority**: `contacts`.
- **Tables**: `People`, `Groups`, `Phones`, `ContactMethods`, `Organizations`.

## Java-to-C++ Translation Guide
-   **Usage**: Avoid. Use `ContactsContract` logic instead.
