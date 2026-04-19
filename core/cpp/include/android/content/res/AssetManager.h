#pragma once

#include <string>
#include <vector>
#include <expected_shim.h>
#include <cstdint>

#include <span>

namespace android::content::res {

enum class AssetError {
    FileNotFound,
    ReadError,
    Unknown
};

class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    auto open(const std::string& path) -> std::expected<std::vector<uint8_t>, AssetError>;
    auto open_as_span(const std::string& path) -> std::expected<std::vector<uint8_t>, AssetError>;
};

} // namespace android::content::res
