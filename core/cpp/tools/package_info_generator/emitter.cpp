// emitter.cpp — C++ header emitter for package-info.java files
// Converts Java annotations to // @<AnnotationName> comment markers
// and generates Doxygen-compliant /** ... */ blocks

#include "emitter.h"
#include <sstream>
#include <regex>
#include <algorithm>

namespace android::tools::package_info_generator {

namespace {

// Clean a single line of javadoc for C++ output
std::string clean_javadoc_line(const std::string& line) {
    std::string result = line;
    
    // Remove leading whitespace and asterisk
    std::regex asterisk_regex(R"(^\s*\*\s?)");
    result = std::regex_replace(result, asterisk_regex, "");
    
    // Convert Java @link/@see to Doxygen-compatible format
    std::regex java_link_regex(R"(\{@link\s+([\w.]+)\})");
    result = std::regex_replace(result, java_link_regex, "@ref \\1");
    
    // Convert &lt; and &gt; to angle brackets for Doxygen
    std::size_t pos = 0;
    while ((pos = result.find("&lt;", pos)) != std::string::npos) {
        result.replace(pos, 4, "<");
        pos += 1;
    }
    while ((pos = result.find("&gt;", pos)) != std::string::npos) {
        result.replace(pos, 4, ">");
        pos += 1;
    }
    
    return result;
}

} // namespace

std::string emit_header(const ParserResult& parsed, const std::string& output_path) {
    std::ostringstream output;
    
    // Generate Doxygen comment block
    output << "/**\n";
    output << " * @file " << output_path << "\n";
    output << " * @brief Package information for " << parsed.package_name << ".\n";
    output << " *\n";
    
    // Emit javadoc content
    if (!parsed.javadoc.empty()) {
        // Remove /* and */ delimiters
        std::string javadoc_content = parsed.javadoc;
        if (javadoc_content.substr(0, 3) == "/**") {
            javadoc_content = javadoc_content.substr(3);
        }
        if (javadoc_content.size() >= 2 && javadoc_content.substr(javadoc_content.size() - 2) == "*/") {
            javadoc_content = javadoc_content.substr(0, javadoc_content.size() - 2);
        }
        
        // Process each line
        std::istringstream stream(javadoc_content);
        std::string line;
        bool first_content = true;
        while (std::getline(stream, line)) {
            std::string cleaned = clean_javadoc_line(line);
            if (!cleaned.empty() && cleaned != " ") {
                if (first_content) {
                    output << " " << cleaned << "\n";
                    first_content = false;
                } else {
                    output << " * " << cleaned << "\n";
                }
            }
        }
    }
    
    // Emit annotations as // @AnnotationName
    for (const auto& annotation : parsed.annotations) {
        output << " * @hide\n"; // Default to @hide for all annotations
        output << " */\n";
        output << "// @" << annotation << "\n";
        output << " */\n";
    }
    
    // Close the main comment block
    output << " */\n";
    output << "\n";
    
    // Generate include guard
    std::string guard = parsed.package_name;
    std::regex guard_regex(R"([^a-zA-Z0-9_])");
    guard = std::regex_replace(guard, guard_regex, "_");
    
    output << "#ifndef " << guard << "_H\n";
    output << "#define " << guard << "_H\n";
    output << "\n";
    output << "// Package information header generated from package-info.java\n";
    output << "\n";
    output << "#endif // " << guard << "_H\n";
    
    return output.str();
}

} // namespace android::tools::package_info_generator
