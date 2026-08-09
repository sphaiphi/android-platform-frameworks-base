// emitter.h — C++ header emitter for package-info.java files
#pragma once

#include "parser.h"
#include <string>

namespace android::tools::package_info_generator {

/// Emit a C++ header from parsed package-info.java content.
/// Returns the generated header string.
std::string emit_header(const ParserResult& parsed, const std::string& output_path);

} // namespace android::tools::package_info_generator
