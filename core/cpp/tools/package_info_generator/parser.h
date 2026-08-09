// parser.h — Java package-info.java parser interface
#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace android::tools::package_info_generator {

struct ParserResult {
    std::string package_name;
    std::string javadoc;
    std::vector<std::string> annotations;
};

/// Parse a package-info.java file and extract package name, javadoc block, and annotations.
/// @throws std::runtime_error if file not found or cannot be opened
ParserResult parse_package_info(const std::filesystem::path& input_path);

} // namespace android::tools::package_info_generator
