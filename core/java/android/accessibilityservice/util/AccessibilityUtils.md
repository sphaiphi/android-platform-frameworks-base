
# AccessibilityUtils - Reverse Engineering Documentation

## Executive Summary
`AccessibilityUtils` is a final, internal (`@hide`) utility class containing static methods used by the accessibility framework, primarily for handling resources associated with `AccessibilityServiceInfo` and `AccessibilityShortcutInfo`. Its main functions are to sanitize HTML content and to safely load drawable resources, preventing common security and performance issues.

## Architecture Overview
*   **Static Utility Class**: The class has a private constructor, cannot be instantiated, and all its methods are `static`. This is a common pattern for stateless helper functions.
*   **Focused Responsibility**: The class has two distinct responsibilities:
    1.  **HTML Sanitization**: Filtering HTML strings to remove unsupported or potentially unsafe tags.
    2.  **Safe Image Loading**: Loading drawable resources while validating their dimensions to prevent performance problems from oversized images.

## Detailed Functionality

### `getFilteredHtmlText(@NonNull String text)`
*   **Purpose**: To sanitize an HTML string intended for display in system UI (like the accessibility settings pages). This prevents services from using malicious or layout-breaking HTML.
*   **Algorithm**:
    1.  It defines a list of unsupported tags (currently just the `<a>` anchor tag).
    2.  It iterates through the list of unsupported tags and uses a regular expression to replace both the opening (`<tag ...>`) and closing (`</tag>`) tags with a benign, non-functional tag (`<invalidtag>`). The regex is case-insensitive.
    3.  It performs a separate, more specific sanitization for the `<img>` tag. It uses a negative lookahead regular expression (`(?!...)`) to find any `<img>` tag that does *not* have a `src` attribute starting with the exact prefix `"R.drawable."`. This enforces a strict convention where images must be local drawable resources. Invalid `<img>` tags are also replaced with `<invalidtag>`.
*   **C++ Implementation Guidance**: This functionality can be replicated using a C++ regular expression library (like the standard `<regex>` library). The patterns and replacement logic can be translated directly.

### `loadSafeAnimatedImage(@NonNull Context context, @NonNull ApplicationInfo applicationInfo, @StringRes int resId)`
*   **Purpose**: To load a drawable resource (potentially animated) from an accessibility service's package while ensuring it is not dangerously large.
*   **Algorithm**:
    1.  It gets the `PackageManager` and uses it to load the `Drawable` from the specified `applicationInfo` (package) and resource ID.
    2.  It checks the intrinsic width and height of the loaded drawable.
    3.  It compares the drawable's dimensions against the screen's width and height (obtained via `getScreenWidthPixels` and `getScreenHeightPixels`).
    4.  If the drawable is wider or taller than the screen, it returns `null`.
    5.  Otherwise, it returns the `Drawable`.
*   **C++ Implementation Guidance**: A C++ version would need access to:
    *   A resource loading mechanism to get an image from a package, given a resource ID.
    *   A way to decode the image header to get its dimensions without loading the entire bitmap into memory.
    *   A way to get the current display's dimensions.
    The core logic of comparing image size to screen size is straightforward.

### `getScreenWidthPixels()` and `getScreenHeightPixels()`
*   **Purpose**: Private helper methods to get the physical dimensions of the screen in pixels.
*   **Algorithm**:
    1.  Gets the `Resources` object from the context.
    2.  Reads the screen width/height in density-independent pixels (`dp`) from the device's configuration (`resources.getConfiguration().screenWidthDp`).
    3.  Uses `TypedValue.applyDimension` to convert the `dp` value into physical pixels based on the screen's density.
*   **Java-Specific Notes**: This is the standard Android way to convert `dp` units to pixels.
*   **C++ Implementation Guidance**: A C++ equivalent running on Android could use the `AScreen` NDK API or similar system services to get the display dimensions. In a different environment, it would call the appropriate display metrics API for that platform.

## Data Model
The class is stateless and only defines a few `static final` constants for its internal logic (e.g., `IMG_PREFIX`, `UNSUPPORTED_TAG_LIST`).

## Java-to-C++ Translation Guide
*   **Namespace with Free Functions**: This class translates well to a C++ namespace containing free functions (e.g., `namespace accessibility_utils { ... }`). Since the methods are stateless, there is no need for a class instance.
*   **Regular Expressions**: C++'s `<regex>` can be used for the HTML sanitization. The patterns are simple enough to be translated directly.
*   **Resource and Context Dependency**: The main challenge is that all methods depend on an Android `Context` or `PackageManager` to access resources and device configuration. A C++ port would need to have equivalent dependencies injected or available. For example, the function signatures would change to accept pointers to C++ resource manager or device metrics objects.
    ```cpp
    // Example C++ header
    namespace accessibility_utils {

    std::string getFilteredHtmlText(const std::string& text);

    // This would need C++ equivalents for Drawable, ApplicationInfo, etc.
    stdCshared_ptr<Drawable> loadSafeAnimatedImage(
        const CppContext& context,
        const ApplicationInfo& appInfo,
        int resourceId);

    } // namespace accessibility_utils
    ```

## Implementation Risks
*   **Regex Performance**: While likely not an issue for the small, targeted replacements here, complex regex on large HTML strings can be slow. The current patterns are efficient.
*   **Resource Access**: A C++ reimplementation will be tightly coupled to the C++ environment's ability to access application resources and display metrics. If these are not available, the functions cannot be ported directly.
*   **Divergence**: The list of unsupported tags or the image `src` prefix convention could change in future Android versions. The C++ implementation would need to be kept in sync with the Java source.

## Questions for C++ Team
*   What regular expression library should be used in the C++ implementation?
*   How will the C++ code access application resources (to load drawables) and get screen dimensions? What are the C++ equivalents of `Context` and `PackageManager` in our target environment?
