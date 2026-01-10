// accessibilityservice.cpp
module accessibilityservice;

import :types;
import :internal;
import :fingerprint_gesture_controller;
import :touch_interaction_controller;
import :magnification_controller;
import ndk_executor;

import <stdexcept>;
import <mutex>;
import <map>;
import <memory>;

namespace android {
    class IBinder;
}

namespace android::accessibilityservice {

// The PIMPL class definition
class AccessibilityServiceImpl : public internal::BnAccessibilityServiceClient {
public:
    explicit AccessibilityServiceImpl(AccessibilityService& public_api)
        : public_api_ref_{public_api},
          executor_{ndk::NdkThreadExecutor::create()} {
        if (!executor_) {
            throw std::runtime_error("Failed to create NdkThreadExecutor");
        }
    }

    // --- BnAccessibilityServiceClient Implementation ---

    void init(std::shared_ptr<internal::IAccessibilityServiceConnection> connection, 
              int connectionId, 
              std::shared_ptr<android::IBinder> windowToken) override {
        std::lock_guard lock(mutex_);
        connection_ = std::move(connection);
        connection_id_ = connectionId;
        window_token_ = std::move(windowToken);
    }

    void onAccessibilityEvent(const AccessibilityEvent& event) override {
        executor_->post([this, event] {
            public_api_ref_.on_accessibility_event(event);
        });
    }

    void onInterrupt() override {
        executor_->post([this] {
            public_api_ref_.on_interrupt();
        });
    }

    void onServiceConnected() override {
        executor_->post([this] {
            public_api_ref_.on_service_connected();
        });
    }

    void onFingerprintGestureDetectionAvailabilityChanged(bool available) override {
        std::lock_guard lock(mutex_);
        if (fingerprint_controller_) {
            auto* impl = static_cast<FingerprintGestureControllerImpl*>(fingerprint_controller_.get());
            impl->dispatch_availability_changed(available);
        }
    }

    void onFingerprintGesture(int gesture) override {
        std::lock_guard lock(mutex_);
        if (fingerprint_controller_) {
            auto* impl = static_cast<FingerprintGestureControllerImpl*>(fingerprint_controller_.get());
            impl->dispatch_gesture(gesture);
        }
    }

    // --- Public API Support ---

    auto get_executor() const -> std::shared_ptr<ndk::IThreadExecutor> {
        return executor_;
    }
    
    auto get_service_info() const -> const AccessibilityServiceInfo& {
        return service_info_;
    }

    void set_service_info(AccessibilityServiceInfo info) {
        service_info_ = std::move(info);
        // if (connection_) connection_->setServiceInfo(service_info_);
    }

    auto get_fingerprint_gesture_controller() -> std::shared_ptr<IFingerprintGestureController> {
        std::lock_guard lock(mutex_);
        if (!connection_) return nullptr;

        if (!fingerprint_controller_) {
            fingerprint_controller_ = std::make_shared<FingerprintGestureControllerImpl>(connection_);
        }
        return fingerprint_controller_;
    }

    auto get_touch_interaction_controller(int display_id) -> std::shared_ptr<ITouchInteractionController> {
        std::lock_guard lock(mutex_);
        if (!connection_) return nullptr;

        if (touch_controllers_.find(display_id) == touch_controllers_.end()) {
            touch_controllers_[display_id] = std::make_shared<TouchInteractionControllerImpl>(connection_, display_id);
        }
        return touch_controllers_[display_id];
    }

    auto get_magnification_controller() -> std::shared_ptr<IMagnificationController> {
        std::lock_guard lock(mutex_);
        if (!connection_) return nullptr;

        if (!magnification_controller_) {
            magnification_controller_ = std::make_shared<MagnificationControllerImpl>(connection_);
        }
        return magnification_controller_;
    }

private:
    AccessibilityService& public_api_ref_;
    std::shared_ptr<ndk::IThreadExecutor> executor_;
    AccessibilityServiceInfo service_info_{};

    mutable std::mutex mutex_;
    std::shared_ptr<internal::IAccessibilityServiceConnection> connection_;
    int connection_id_{-1};
    std::shared_ptr<android::IBinder> window_token_;

    // Controllers
    std::shared_ptr<IFingerprintGestureController> fingerprint_controller_;
    std::map<int, std::shared_ptr<ITouchInteractionController>> touch_controllers_;
    std::shared_ptr<IMagnificationController> magnification_controller_;
};

//======== Implementation of AccessibilityService public methods ========

AccessibilityService::AccessibilityService()
    : impl_{std::make_unique<AccessibilityServiceImpl>(*this)} {}

AccessibilityService::~AccessibilityService() = default; 

auto AccessibilityService::get_executor() const -> std::shared_ptr<ndk::IThreadExecutor> {
    return impl_->get_executor();
}

auto AccessibilityService::get_service_info() const -> const AccessibilityServiceInfo& {
    return impl_->get_service_info();
}

void AccessibilityService::set_service_info(AccessibilityServiceInfo info) {
    impl_->set_service_info(std::move(info));
}

auto AccessibilityService::get_fingerprint_gesture_controller() const -> std::shared_ptr<IFingerprintGestureController> {
    return impl_->get_fingerprint_gesture_controller();
}

auto AccessibilityService::get_touch_interaction_controller(int display_id) const -> std::shared_ptr<ITouchInteractionController> {
    return impl_->get_touch_interaction_controller(display_id);
}

auto AccessibilityService::get_magnification_controller() const -> std::shared_ptr<IMagnificationController> {
    return impl_->get_magnification_controller();
}

} // namespace android::accessibilityservice