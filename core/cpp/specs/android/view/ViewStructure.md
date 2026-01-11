# ViewStructure - Reverse Engineering Documentation

## Executive Summary
`ViewStructure` is a recursive data container used to capture the semantic and visual state of a view hierarchy. it is the primary bridge for features like Autofill, Assist (Google Assistant), and Content Capture, allowing them to "understand" the structure of a UI, including virtual nodes (e.g., in a `WebView` or a Canvas-based drawing).

## Architecture Overview
*   **Role**: Semantic UI snapshot container.
*   **Recursive**: Each `ViewStructure` can contain multiple child `ViewStructure` objects.
*   **Virtual Nodes**: Specifically designed to allow views to report "virtual" children that don't exist as standard `View` objects.

## Detailed Functionality

### 1. Visual Metadata
*   **`setDimens()`**: Captures position, size, and scroll state.
*   **`setVisibility()`** / **`setAlpha()`** / **`setElevation()`**: Stores rendering properties.

### 2. Semantic Data
*   **`setText()`**: Captures the text content, including selection and style spans.
*   **`setClassName()`**: Identifies the type of component (e.g., "android.widget.EditText").
*   **`setContentDescription()`**: Provides the accessibility label.

### 3. Autofill & Credentials
*   **`setAutofillId()`** / **`setAutofillType()`**: links the node to the system's autofill engine.
*   **`setPendingCredentialRequest()`**: Integrates with `CredentialManager` for login/signup flows.

### 4. Asynchronous Population
*   **`asyncNewChild()`** / **`asyncCommit()`**: Allows complex views (like browsers) to build their structure on a background thread without blocking the UI.

## Java-to-C++ Translation Guide
*   **Structure**: Map to a C++ `class ViewStructure` with a `std::vector<std::unique_ptr<ViewStructure>>` for children.
*   **Parcelling**: Marshalling must handle complex objects like `Matrix`, `AutofillId`, and `LocaleList`.

## Implementation Risks
*   **Memory Usage**: Capturing a full tree for a complex app can be memory-intensive.
*   **Sensitive Data**: Contains PII (Personally Identifiable Information); the class includes a `setDataIsSensitive()` flag to ensure data is handled securely by the system.
