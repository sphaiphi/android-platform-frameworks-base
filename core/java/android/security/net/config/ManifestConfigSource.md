# ManifestConfigSource - Reverse Engineering Documentation

## Executive Summary
`ConfigSource` that loads configuration from the `AndroidManifest.xml` metadata (`android:networkSecurityConfig`).

## Functionality
*   Checks `ApplicationInfo` for `networkSecurityConfigRes`.
*   If present, delegates to `XmlConfigSource`.
*   If absent, creates a default config based on `usesCleartextTraffic` flag.

## Java-to-C++ Translation Guide
*   Requires parsing AndroidManifest or accessing `Am.getAppInfo`.
