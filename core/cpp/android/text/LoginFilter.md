# LoginFilter - Reverse Engineering Documentation

## Executive Summary
Deprecated `InputFilter` for username/password restrictions.

## Functionality
- **`filter`**: Checks characters against `isAllowed`.
- **`UsernameFilterGMail`**: Allows specific chars for GMail.
- **`UsernameFilterGeneric`**: Generic set of allowed chars.
- **`PasswordFilterGMail`**: Latin-1 restriction.

## Java-to-C++ Translation Guide
- **Deprecated**: Low priority.
