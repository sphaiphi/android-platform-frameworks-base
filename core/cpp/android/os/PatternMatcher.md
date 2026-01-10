# PatternMatcher - Reverse Engineering Documentation

## Executive Summary
`PatternMatcher` is a secure, parcelable string matcher used for filtering Intents and paths (e.g., in `IntentFilter` or `UriMatcher`). It supports literal, prefix, simple glob, and advanced glob matching.

## Architecture Overview
-   **Pattern**: Strategy / Matcher.
-   **Algorithm**:
    -   `LITERAL`: String equality.
    -   `PREFIX`: `startsWith`.
    -   `SIMPLE_GLOB`: `.*` style wildcards (manual implementation).
    -   `ADVANCED_GLOB`: Regex-like subsets (parsed into an int array tokens).

## Data Model
-   `mPattern` (String): The pattern.
-   `mType` (int): Type constant.
-   `mParsedPattern` (int[]): Parsed tokens for advanced glob.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::PatternMatcher` (C++ Binder).
-   **Logic**: The `matchGlobPattern` and `matchAdvancedPattern` logic is purely algorithmic and can be ported directly to C++. It performs character-by-character consumption without full regex engine overhead.

## Implementation Risks
-   **Recursion/Complexity**: The advanced glob matcher handles backtracking or sets. Ensure the C++ implementation is robust against stack overflow or ReDoS (though the implementation here seems linear/iterative).
