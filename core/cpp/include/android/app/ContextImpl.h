#pragma once

#include <android/content/Context.h>
#include <string>
#include <memory>

namespace android::app {

/**
 * Concrete implementation of the Context API.
 * 
 * ContextImpl provides the core implementation of the Android application environment.
 * It handles resource access, file system operations, and system service retrieval.
 */
class ContextImpl : public android::content::Context {
public:
    ContextImpl();
    ~ContextImpl() override = default;

    /**
     * Retrieve a system-level service by name.
     * @param name The name of the service (e.g., "activity", "window").
     * @return A pointer to the service or a ContextError if not found.
     */
    [[nodiscard]] auto get_system_service(std::string_view name) -> std::expected<void*, android::content::ContextError> override;
    
    /**
     * Get the package name of the application.
     */
    [[nodiscard]] auto get_package_name() const -> std::string override;

    /**
     * Get the absolute path to the directory on the filesystem where files are stored.
     */
    [[nodiscard]] auto get_files_dir() const -> std::string override;

    /**
     * Get the absolute path to the directory on the filesystem where cache files are stored.
     */
    [[nodiscard]] auto get_cache_dir() const -> std::string override;

    /**
     * Set the package name (internal use).
     */
    void set_package_name(std::string_view name);

    /**
     * Set the files directory path (internal use).
     */
    void set_files_dir(std::string_view path);

    /**
     * Set the cache directory path (internal use).
     */
    void set_cache_dir(std::string_view path);

private:
    std::string package_name_;
    std::string files_dir_;
    std::string cache_dir_;
};

} // namespace android::app
