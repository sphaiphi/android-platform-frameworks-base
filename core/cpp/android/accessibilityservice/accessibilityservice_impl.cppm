// accessibilityservice_impl.cppm
module accessibilityservice;

import :types;
import :internal;
import <stdexcept>;

// Assume necessary Binder and NDK headers are available
// #include <binder/IServiceManager.h>
// #include <binder/ProcessState.h>

namespace accessibility {

// The PIMPL class definition
class AccessibilityServiceImpl : public internal::BnAccessibilityServiceClient {
public:
    // Constructor: Takes a reference to the public AccessibilityService interface
    // to call back into its virtual methods.
    explicit AccessibilityServiceImpl(AccessibilityService& public_api)
        : public_api_ref_{public_api},
          executor_{ndk::NdkThreadExecutor::create()} {
        if (!executor_) {
            throw std::runtime_error("Failed to create NdkThreadExecutor");
        }
        // In a real scenario, this would register itself with the system's
        // AccessibilityManagerService via the Binder service manager.
        // android::defaultServiceManager()->addService(...);
    }

    // Callback from system (via Binder), executed on a Binder thread.
    void onAccessibilityEvent(const AccessibilityEvent& event) override {
        // Post the event to the dedicated executor thread to avoid blocking the
        // Binder thread and to ensure events are processed sequentially.
        executor_->post([this, event] {
            public_api_ref_.on_accessibility_event(event);
        });
    }

    // Callback from system (via Binder).
    void onInterrupt() override {
        executor_->post([this] {
            public_api_ref_.on_interrupt();
        });
    }

    // Callback from system (via Binder).
    void onServiceConnected() override {
        executor_->post([this] {
            public_api_ref_.on_service_connected();
        });
    }

    auto get_executor() const -> std::shared_ptr<ndk::IThreadExecutor> {
        return executor_;
    }
    
    auto get_service_info() const -> const AccessibilityServiceInfo& {
        return service_info_;
    }

    void set_service_info(AccessibilityServiceInfo info) {
        service_info_ = std::move(info);
        // This would then make an IPC call to the system to update the service info.
    }

private:
    AccessibilityService& public_api_ref_; // Non-owning reference to the public object
    std::shared_ptr<ndk::IThreadExecutor> executor_;
    AccessibilityServiceInfo service_info_{};
};

//======== Implementation of AccessibilityService public methods ========

AccessibilityService::AccessibilityService()
    : impl_{std::make_unique<AccessibilityServiceImpl>(*this)} {}

AccessibilityService::~AccessibilityService() = default; // std::unique_ptr handles cleanup

auto AccessibilityService::get_executor() const -> std::shared_ptr<ndk::IThreadExecutor> {
    return impl_->get_executor();
}

auto AccessibilityService::get_service_info() const -> const AccessibilityServiceInfo& {
    return impl_->get_service_info();
}

void AccessibilityService::set_service_info(AccessibilityServiceInfo info) {
    impl_->set_service_info(std::move(info));
}

} // namespace accessibility