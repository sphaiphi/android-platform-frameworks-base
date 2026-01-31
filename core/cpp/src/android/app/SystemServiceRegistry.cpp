#include <android/app/SystemServiceRegistry.h>
#include <android/app/ContextImpl.h>

namespace android::app {

std::unordered_map<std::string, std::unique_ptr<ServiceFetcher>> SystemServiceRegistry::fetchers_;

auto SystemServiceRegistry::get_system_service(ContextImpl* ctx, std::string_view name) -> std::expected<void*, android::content::ContextError> {
    auto it = fetchers_.find(std::string(name));
    if (it == fetchers_.end()) {
        return std::unexpected(android::content::ContextError::service_not_found);
    }
    return it->second->get_service(ctx);
}

void SystemServiceRegistry::register_service(std::string_view name, std::unique_ptr<ServiceFetcher> fetcher) {
    fetchers_[std::string(name)] = std::move(fetcher);
}

} // namespace android::app
