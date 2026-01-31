#pragma once

#include <android/content/Context.h>

namespace android::content {

class ContextWrapper : public Context {
public:
    explicit ContextWrapper(std::shared_ptr<Context> base) : base_(std::move(base)) {}
    virtual ~ContextWrapper() = default;

    auto attach_base_context(std::shared_ptr<Context> base) -> void {
        if (base_ != nullptr) {
            // In Android, this throws IllegalStateException if already set
            return;
        }
        base_ = std::move(base);
    }

    [[nodiscard]] auto get_base_context() const noexcept -> std::shared_ptr<Context> {
        return base_;
    }

    [[nodiscard]] auto get_system_service(std::string_view name) -> std::expected<void*, ContextError> override {
        if (base_ == nullptr) {
            return std::unexpected(ContextError::service_not_found);
        }
        return base_->get_system_service(name);
    }

    [[nodiscard]] auto get_package_name() const -> std::string override {
        if (base_ == nullptr) {
            return "";
        }
        return base_->get_package_name();
    }

    [[nodiscard]] auto get_files_dir() const -> std::string override {
        if (base_ == nullptr) {
            return "";
        }
        return base_->get_files_dir();
    }

    [[nodiscard]] auto get_cache_dir() const -> std::string override {
        if (base_ == nullptr) {
            return "";
        }
        return base_->get_cache_dir();
    }

private:
    std::shared_ptr<Context> base_{nullptr};
};

} // namespace android::content
