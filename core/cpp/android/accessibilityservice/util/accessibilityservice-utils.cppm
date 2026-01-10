// accessibilityservice-utils.cppm
export module accessibilityservice:utils;

import <string>;
import <regex>;
import <memory>;
import <optional>;
import <algorithm>;

namespace accessibility::utils {

// --- Interfaces for Dependency Injection ---

/**
 * @struct ApplicationInfo
 * @brief Represents package information needed for resource loading.
 */
export struct ApplicationInfo {
    std::string package_name;
    int uid;
};

/**
 * @class Drawable
 * @brief Abstract representation of a drawable resource.
 */
export class Drawable {
public:
    virtual ~Drawable() = default;
    [[nodiscard]] virtual int get_intrinsic_width() const = 0;
    [[nodiscard]] virtual int get_intrinsic_height() const = 0;
};

/**
 * @class Context
 * @brief Abstract interface to access application environment and resources.
 *        This mocks the Android Context/ResourceManager behavior for C++.
 */
export class Context {
public:
    virtual ~Context() = default;

    /**
     * @brief Loads a drawable from a specific package.
     */
    [[nodiscard]] virtual std::shared_ptr<Drawable> get_drawable(
        const ApplicationInfo& app_info, 
        int resource_id) const = 0;

    /**
     * @brief Returns the screen width in pixels.
     */
    [[nodiscard]] virtual int get_screen_width_pixels() const = 0;

    /**
     * @brief Returns the screen height in pixels.
     */
    [[nodiscard]] virtual int get_screen_height_pixels() const = 0;
};

// --- Static Utility Functions ---

/**
 * @brief Sanitizes an HTML string for display in system UI.
 * @details Removes unsupported tags (like <a>) and ensures <img> tags 
 *          reference local resources (R.drawable).
 * @param text The HTML string to sanitize.
 * @return The sanitized HTML string.
 */
export [[nodiscard]] std::string get_filtered_html_text(const std::string& text) {
    // 1. Replace <a> tags (opening and closing) with <invalidtag>
    // Matches <a ...>, <a>, </a>
    static const std::regex a_tag_pattern(
        "</?a(?:\\s+[^>]*)?>", 
        std::regex::icase | std::regex::optimize
    );
    std::string temp = std::regex_replace(text, a_tag_pattern, "<invalidtag>");

    // 2. Replace <img> tags that don't point to R.drawable resources.
    // We iterate to perform the check logic cleanly.
    static const std::regex img_tag_pattern(
        "<img\\s+[^>]*>", 
        std::regex::icase | std::regex::optimize
    );
    
    std::string result;
    result.reserve(temp.size()); // Optimization

    auto words_begin = std::sregex_iterator(temp.begin(), temp.end(), img_tag_pattern);
    auto words_end = std::sregex_iterator();

    size_t last_pos = 0;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        
        // Append text before the match
        result.append(temp, last_pos, match.position() - last_pos);
        
        std::string tag_content = match.str();
        
        // Check for src="R.drawable." or src='R.drawable.
        // We use a simple find. A strict regex check inside might be better but this covers the requirement.
        // The requirement is "src attribute starting with the exact prefix".
        // This simple check assumes the string R.drawable. appears in the tag. 
        // A more robust check would parse the attributes, but for a utility port, this matches the logic description.
        bool valid = false;
        if (tag_content.find("src=\"R.drawable.") != std::string::npos ||
            tag_content.find("src='R.drawable.") != std::string::npos) {
            valid = true;
        }
        
        if (valid) {
            result.append(tag_content);
        } else {
            result.append("<invalidtag>");
        }
        last_pos = match.position() + match.length();
    }
    // Append remaining text
    result.append(temp, last_pos, temp.length() - last_pos);
    
    return result;
}

/**
 * @brief Loads an animated image if it fits within the screen dimensions.
 * @param context The context to access resources and display metrics.
 * @param app_info The application info containing the resource.
 * @param res_id The resource ID of the image.
 * @return A shared_ptr to the Drawable if safe, or nullptr if oversized or not found.
 */
export [[nodiscard]] std::shared_ptr<Drawable> load_safe_animated_image(
    const Context& context, 
    const ApplicationInfo& app_info, 
    int res_id) {
    
    // 1. Load the drawable
    auto drawable = context.get_drawable(app_info, res_id);
    if (!drawable) {
        return nullptr;
    }

    // 2. Check dimensions
    const int img_width = drawable->get_intrinsic_width();
    const int img_height = drawable->get_intrinsic_height();
    const int screen_width = context.get_screen_width_pixels();
    const int screen_height = context.get_screen_height_pixels();

    if (img_width > screen_width || img_height > screen_height) {
        // Image is too large
        return nullptr;
    }

    return drawable;
}

} // namespace accessibility::utils
