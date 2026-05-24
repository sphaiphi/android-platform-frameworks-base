#include <android/app/ContextImpl.h>
#include <android/app/SystemServiceRegistry.h>

namespace android::app {

ContextImpl::ContextImpl() = default;

auto ContextImpl::get_system_service(std::string_view name) -> std::expected<void*, android::content::ContextError> {
    return SystemServiceRegistry::get_system_service(this, name);
}

auto ContextImpl::get_package_name() const -> std::string {
    return package_name_;
}

auto ContextImpl::get_files_dir() const -> std::string {
    return files_dir_;
}

auto ContextImpl::get_cache_dir() const -> std::string {
    return cache_dir_;
}

void ContextImpl::set_package_name(std::string_view name) {
    package_name_ = name;
}

void ContextImpl::set_files_dir(std::string_view path) {
    files_dir_ = path;
}

void ContextImpl::set_cache_dir(std::string_view path) {
    cache_dir_ = path;
}

} // namespace android::app
