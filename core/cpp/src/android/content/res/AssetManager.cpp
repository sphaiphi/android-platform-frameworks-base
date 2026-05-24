#include <android/content/res/AssetManager.h>
#include <filesystem>
#include <fstream>

namespace android::content::res {

auto AssetManager::open(const std::string& path) -> std::expected<std::vector<uint8_t>, AssetError> {
    namespace fs = std::filesystem;
    
    if (!fs::exists(path)) {
        return std::unexpected(AssetError::FileNotFound);
    }

    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return std::unexpected(AssetError::ReadError);
    }

    std::streamsize size = file.tellg();
    if (size < 0) {
        return std::unexpected(AssetError::ReadError);
    }
    
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(static_cast<size_t>(size));
    if (size > 0 && !file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        return std::unexpected(AssetError::ReadError);
    }

    return buffer;
}

auto AssetManager::open_as_span(const std::string& path) -> std::expected<std::vector<uint8_t>, AssetError> {
    // Current implementation returns vector as ownership is required for now.
    // In a full implementation, this might return a memory-mapped span.
    return open(path);
}

} // namespace android::content::res
