#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <expected>
#include <android/content/Context.h>

namespace android::app {

class ContextImpl;

/**
 * Base class for service fetchers.
 * Each system service has a corresponding fetcher that knows how to create or retrieve it.
 */
class ServiceFetcher {
public:
    virtual ~ServiceFetcher() = default;

    /**
     * Retrieve the service instance for the given context.
     */
    virtual auto get_service(ContextImpl* ctx) -> std::expected<void*, android::content::ContextError> = 0;
};

/**
 * Manages the registration and retrieval of all system services.
 * This is a central repository for services like ActivityManager, PackageManager, etc.
 */
class SystemServiceRegistry {
public:
    /**
     * Retrieve a system service by name for the given context.
     */
    static auto get_system_service(ContextImpl* ctx, std::string_view name) -> std::expected<void*, android::content::ContextError>;

    /**
     * Register a new system service fetcher.
     * @param name The name of the service.
     * @param fetcher The fetcher implementation.
     */
    static void register_service(std::string_view name, std::unique_ptr<ServiceFetcher> fetcher);

private:
    static std::unordered_map<std::string, std::unique_ptr<ServiceFetcher>> fetchers_;
};

} // namespace android::app
