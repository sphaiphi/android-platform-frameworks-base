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
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        return buffer;
    }

    return std::unexpected(AssetError::ReadError);
}

} // namespace android::content::res
