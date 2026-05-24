#pragma once

#include <string>
#include <memory>
#include <expected_shim.h>

namespace android::content {

enum class ContextError {
    service_not_found,
    permission_denied
};

class Context {
public:
    virtual ~Context() = default;

    [[nodiscard]] virtual auto get_system_service(std::string_view name) -> std::expected<void*, ContextError> = 0;
    
    // Add other essential methods as needed
    [[nodiscard]] virtual auto get_package_name() const -> std::string = 0;
    [[nodiscard]] virtual auto get_files_dir() const -> std::string = 0;
    [[nodiscard]] virtual auto get_cache_dir() const -> std::string = 0;
};

} // namespace android::content
