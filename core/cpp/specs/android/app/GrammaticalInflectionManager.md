# GrammaticalInflectionManager - Reverse Engineering Documentation

## Executive Summary
`GrammaticalInflectionManager` allows apps to control grammatical gender settings (terms of address) for localization purposes.

## Architecture Overview
*   **Pattern**: Service Wrapper.
*   **Service**: `IGrammaticalInflectionManager`.

## Detailed Functionality
*   `setRequestedApplicationGrammaticalGender`: Sets app-specific gender.
*   `getApplicationGrammaticalGender`: Gets current value.
*   `setSystemWideGrammaticalGender`: Sets global gender (privileged).

## Java-to-C++ Translation Guide
*   Binder proxy.

## Implementation Risks
*   None.
