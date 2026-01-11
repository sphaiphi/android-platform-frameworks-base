# JavascriptInterface - Reverse Engineering Documentation

## Executive Summary
`JavascriptInterface` is an annotation used to mark public methods in Java objects that should be exposed to JavaScript code running in the `WebView`.

## Detailed Functionality
*   **Security**: Starting from API 17 (Jelly Bean MR1), only methods with this annotation are accessible from JS. This prevents malicious JS from accessing arbitrary methods via reflection on injected Java objects.

## Java-to-C++ Translation Guide
*   **Binding**: The C++ implementation needs to inspect the Java object (via JNI), look for methods with this annotation, and build a JS wrapper object (e.g., V8 object template) that delegates calls back to the Java method.
