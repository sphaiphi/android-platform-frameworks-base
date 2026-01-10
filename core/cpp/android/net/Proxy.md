# Proxy.java - Reverse Engineering Documentation

## Executive Summary
`Proxy` is a convenience class for accessing system HTTP proxy settings. It provides methods to get the host, port, and configure the proxy in the running process.

## Architecture Overview
- **Type**: Utility Class
- **Package**: `android.net`
- **Deprecated**: Most methods are deprecated in favor of `ConnectivityManager.getDefaultProxy()`.

## Functionality
-   `getProxy(Context, url)`: Returns a `java.net.Proxy` using `ProxySelector`.
-   `setHttpProxyConfiguration(ProxyInfo)`: Sets Java system properties (`http.proxyHost`, `http.nonProxyHosts`, etc.) and the default `ProxySelector` (PAC vs Default).

## Java-to-C++ Translation Guide
Mainly interacts with Java system properties. In C++, proxy configuration is usually library-specific (e.g., setting CURL options). The global concept applies, but the implementation `System.setProperty` is Java-specific.
