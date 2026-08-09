// parser.cpp — Java package-info.java parser
// Extracts package name, javadoc block, and annotations from package-info.java files

#include "parser.h"
#include <regex>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>

namespace android::tools::package_info_generator {

namespace fs = std::filesystem;

ParserResult parse_package_info(const fs::path& input_path) {
    if (!fs::exists(input_path)) {
        throw std::runtime_error("File not found: " + input_path.string());
    }

    std::ifstream file(input_path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + input_path.string());
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    ParserResult result;

    // Extract package declaration
    std::regex package_regex(R"(package\s+([\w.]+)\s*;)");
    std::smatch package_match;
    if (std::regex_search(content, package_match, package_regex)) {
        result.package_name = package_match[1].str();
    }

    // Extract javadoc block (/** ... */)
    std::regex javadoc_regex(R"(/\*\*[\s\S]*?\*/)");
    std::smatch javadoc_match;
    if (std::regex_search(content, javadoc_match, javadoc_regex)) {
        result.javadoc = javadoc_match[0].str();
    }

    // Extract annotations from javadoc and class-level annotations
    std::regex annotation_regex(R"(@(\w+)(?:\s*\([^)]*\))?)"  );
    std::sregex_iterator it(content.begin(), content.end(), annotation_regex);
    std::sregex_iterator end;

    for (; it != end; ++it) {
        std::string annotation = (*it)[1].str();
        // Skip common javadoc tags that aren't annotations
        if (annotation != "param" && annotation != "return" &&
            annotation != "see" && annotation != "link" &&
            annotation != "throws" && annotation != "deprecated") {
            result.annotations.push_back(annotation);
        }
    }

    return result;
}

} // namespace android::tools::package_info_generator
