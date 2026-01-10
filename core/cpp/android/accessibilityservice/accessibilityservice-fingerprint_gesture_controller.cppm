// accessibilityservice-fingerprint_gesture_controller.cppm
export module accessibilityservice:fingerprint_gesture_controller;

import :internal;
import ndk_executor;
import <memory>;
import <mutex>;
import <map>;
import <expected>;

export namespace accessibility {

// Callback interface for fingerprint gestures
class IFingerprintGestureCallback {
public:
    virtual ~IFingerprintGestureCallback() = default;
    
    virtual void on_gesture_detection_availability_changed(bool available) = 0;
    virtual void on_gesture_detected(int gesture_id) = 0;
};

// Interface for the FingerprintGestureController
class IFingerprintGestureController {
public:
    virtual ~IFingerprintGestureController() = default;

    static constexpr int FINGERPRINT_GESTURE_SWIPE_UP = 0x00000001;
    static constexpr int FINGERPRINT_GESTURE_SWIPE_DOWN = 0x00000002;
    static constexpr int FINGERPRINT_GESTURE_SWIPE_LEFT = 0x00000004;
    static constexpr int FINGERPRINT_GESTURE_SWIPE_RIGHT = 0x00000008;

    [[nodiscard]] virtual auto is_gesture_detection_available() const -> bool = 0;

    virtual void register_callback(
        std::shared_ptr<IFingerprintGestureCallback> callback,
        std::shared_ptr<ndk::IThreadExecutor> executor) = 0;

    virtual void unregister_callback(std::shared_ptr<IFingerprintGestureCallback> callback) = 0;
};

// Implementation of the controller
class FingerprintGestureControllerImpl final : public IFingerprintGestureController {
public:
    explicit FingerprintGestureControllerImpl(
        std::shared_ptr<internal::IAccessibilityServiceConnection> connection)
        : connection_(std::move(connection)) {}

    [[nodiscard]] auto is_gesture_detection_available() const -> bool override {
        auto result = connection_->is_fingerprint_gesture_detection_available();
        return result.value_or(false);
    }

    void register_callback(
        std::shared_ptr<IFingerprintGestureCallback> callback,
        std::shared_ptr<ndk::IThreadExecutor> executor) override {
        if (!callback || !executor) return;
        std::lock_guard lock(mutex_);
        callbacks_[callback] = executor;
    }

    void unregister_callback(std::shared_ptr<IFingerprintGestureCallback> callback) override {
        std::lock_guard lock(mutex_);
        callbacks_.erase(callback);
    }

    // Internal methods called when events arrive from system
    void dispatch_availability_changed(bool available) {
        std::lock_guard lock(mutex_);
        for (auto const& [callback, executor] : callbacks_) {
            executor->post([cb = callback, available]() {
                cb->on_gesture_detection_availability_changed(available);
            });
        }
    }

    void dispatch_gesture(int gesture_id) {
        std::lock_guard lock(mutex_);
        for (auto const& [callback, executor] : callbacks_) {
            executor->post([cb = callback, gesture_id]() {
                cb->on_gesture_detected(gesture_id);
            });
        }
    }

private:
    std::shared_ptr<internal::IAccessibilityServiceConnection> connection_;
    std::mutex mutex_;
    std::map<std::shared_ptr<IFingerprintGestureCallback>, std::shared_ptr<ndk::IThreadExecutor>> callbacks_;
};

} // namespace accessibility