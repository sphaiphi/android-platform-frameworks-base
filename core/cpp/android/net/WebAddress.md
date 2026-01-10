# WebAddress.java - Reverse Engineering Documentation

## Executive Summary
`WebAddress` is a parser for user-entered web addresses. It is more lenient than `java.net.URI`, attempting to fix common user errors (missing scheme, etc.) and parsing into scheme, host, port, path, and auth info.

## Architecture Overview
- **Type**: Parser / Data Class
- **Package**: `android.net`.

## Parsing Logic (`sAddressPattern`)
Regex: `(?:(http|https|file)\:\/\/)?(?:([-A-Za-z0-9$_.+!*'(),;?&=]+(?:\:[-A-Za-z0-9$_.+!*'(),;?&=]+)?)@)?([a-zA-Z0-9%_-][a-zA-Z0-9%_.-]*|\[[0-9a-fA-F:.]+\])?(?:\:([0-9]*))?(\/?[^#]*)?.*`
-   Group 1: Scheme (optional).
-   Group 2: Auth Info (optional).
-   Group 3: Host.
-   Group 4: Port (optional).
-   Group 5: Path (optional).

## Normalization
-   Default scheme: `http`.
-   Default port: `80` (http) or `443` (https/wss) if missing.
-   Empty path becomes `/`.

## Java-to-C++ Translation Guide
Regex-based parser. Use `std::regex` or `PCRE` with the supplied pattern.
