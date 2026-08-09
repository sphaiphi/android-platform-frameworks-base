// main.cpp — CLI entry point for package_info_generator
// Iterates package-info.java files, invokes parser+emitter, exits with codes 0/1/2/3/4

#include "parser.h"
#include "emitter.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

// Find all package-info.java files recursively
std::vector<fs::path> find_package_info_files(const fs::path& root) {
    std::vector<fs::path> files;
    if (!fs::exists(root) || !fs::is_directory(root)) {
        return files;
    }
    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (entry.is_regular_file() && entry.path().filename() == "package-info.java") {
            files.push_back(entry.path());
        }
    }
    return files;
}

// Convert package-info.java path to C++ header path
// e.g., core/java/android/foo/bar/package-info.java -> core/cpp/include/android/foo/bar/package-info.h
std::string convert_to_cpp_header(const fs::path& java_path, const fs::path& base_dir) {
    std::string rel = java_path.string();
    std::string base = base_dir.string();
    
    // Remove base directory prefix
    if (rel.substr(0, base.size()) == base) {
        rel = rel.substr(base.size());
    }
    
    // Replace .java with .h
    if (rel.size() >= 5 && rel.substr(rel.size() - 5) == ".java") {
        rel = rel.substr(0, rel.size() - 5) + ".h";
    }
    
    // Replace java/ with cpp/include/
    std::size_t pos = rel.find("/java/");
    if (pos != std::string::npos) {
        rel.replace(pos, 6, "/cpp/include/");
    }
    
    return rel;
}

} // namespace

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: package_info_generator <java_source_dir>\n";
        return 4;
    }
    
    fs::path java_dir = argv[1];
    if (!fs::exists(java_dir) || !fs::is_directory(java_dir)) {
        std::cerr << "Error: Directory not found: " << java_dir << "\n";
        return 2;
    }
    
    auto files = find_package_info_files(java_dir);
    if (files.empty()) {
        std::cerr << "No package-info.java files found in: " << java_dir << "\n";
        return 0;
    }
    
    int errors = 0;
    for (const auto& file : files) {
        // Skip com.android.internal files
        if (file.string().find("com/android/internal") != std::string::npos) {
            continue;
        }
        
        try {
            // Parse the package-info.java file
            auto result = android::tools::package_info_generator::parse_package_info(file);
            
            // Generate C++ header path
            std::string output_path = convert_to_cpp_header(file, java_dir);
            
            // Emit the header
            std::string header = emit_header(result, output_path);
            
            // Create output directory if needed
            fs::path output_file = output_path;
            fs::path output_dir = output_file.parent_path();
            if (!fs::exists(output_dir)) {
                fs::create_directories(output_dir);
            }
            
            // Write the header
            std::ofstream out(output_path);
            if (!out.is_open()) {
                std::cerr << "Error: Cannot write to: " << output_path << "\n";
                errors++;
                continue;
            }
            out << header;
            out.close();
            
            std::cout << "Generated: " << output_path << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error processing " << file << ": " << e.what() << "\n";
            errors++;
        }
    }
    
    if (errors > 0) {
        std::cerr << errors << " error(s) occurred\n";
        return 1;
    }
    
    return 0;
}
