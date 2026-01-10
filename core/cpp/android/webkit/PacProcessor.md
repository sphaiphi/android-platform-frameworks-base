# PacProcessor - Reverse Engineering Documentation

## Executive Summary
`PacProcessor` provides an interface to evaluate Proxy Auto-Config (PAC) scripts. It allows embedding applications to resolve proxies for URLs based on a PAC file.

## Architecture Overview
*   **Factory**: `createInstance()`.
*   **Context**: Can be bound to a specific `Network`.

## Detailed Functionality
*   **`setProxyScript(String script)`**: Loads the JS PAC script.
*   **`findProxyForUrl(String url)`**: Executes the script's `FindProxyForURL` function and returns the proxy string.

## Java-to-C++ Translation Guide
*   **JS Engine**: PAC evaluation requires a JavaScript engine (V8 or similar) running in a restricted context.
*   **Networking**: Needs to support DNS resolution functions (dnsResolve, myIpAddress) within the PAC context.
