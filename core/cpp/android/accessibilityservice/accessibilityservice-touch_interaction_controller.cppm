// accessibilityservice-touch_interaction_controller.cppm
export module accessibilityservice:touch_interaction_controller;

import :internal;
import :types;
import ndk_executor;

import <memory>;
import <mutex>;
import <map>;
import <queue>;
import <vector>;
import <expected>;

export namespace accessibility {

class ITouchInteractionCallback {
public:
    virtual ~ITouchInteractionCallback() = default;
    virtual void on_state_changed(int state) = 0;
    virtual void on_motion_event(const MotionEvent& event) = 0;
};

class ITouchInteractionController {
public:
    virtual ~ITouchInteractionController() = default;

    static constexpr int STATE_CLEAR = 0;
    static constexpr int STATE_TOUCH_INTERACTING = 1;
    static constexpr int STATE_TOUCH_EXPLORING = 2;
    static constexpr int STATE_DRAGGING = 3;
    static constexpr int STATE_DELEGATING = 4;

    virtual auto request_touch_exploration() -> std::expected<void, internal::IpcError> = 0;
    virtual auto request_dragging(int pointer_id) -> std::expected<void, internal::IpcError> = 0;
    virtual auto request_delegating() -> std::expected<void, internal::IpcError> = 0;

    virtual void register_callback(
        std::shared_ptr<ITouchInteractionCallback> callback,
        std::shared_ptr<ndk::IThreadExecutor> executor) = 0;

    virtual void unregister_callback(std::shared_ptr<ITouchInteractionCallback> callback) = 0;

    [[nodiscard]] virtual auto get_state() const -> int = 0;
    [[nodiscard]] virtual auto get_display_id() const -> int = 0;
};

class TouchInteractionControllerImpl final : public ITouchInteractionController {
public:
    TouchInteractionControllerImpl(
        std::shared_ptr<internal::IAccessibilityServiceConnection> connection,
        int display_id)
        : connection_(std::move(connection)), display_id_(display_id) {}

    ~TouchInteractionControllerImpl() {
        unregister_all();
    }

    auto request_touch_exploration() -> std::expected<void, internal::IpcError> override {
        std::lock_guard lock(mutex_);
        state_change_requested_ = true;
        return connection_->request_touch_exploration(display_id_);
    }

    auto request_dragging(int pointer_id) -> std::expected<void, internal::IpcError> override {
        std::lock_guard lock(mutex_);
        state_change_requested_ = true;
        return connection_->request_dragging(display_id_, pointer_id);
    }

    auto request_delegating() -> std::expected<void, internal::IpcError> override {
        std::lock_guard lock(mutex_);
        state_change_requested_ = true;
        return connection_->request_delegating(display_id_);
    }

    void register_callback(
        std::shared_ptr<ITouchInteractionCallback> callback,
        std::shared_ptr<ndk::IThreadExecutor> executor) override {
        if (!callback || !executor) return;
        
        std::lock_guard lock(mutex_);
        bool first_callback = callbacks_.empty();
        callbacks_[callback] = executor;

        if (first_callback) {
            connection_->set_service_detects_gestures_enabled(display_id_, true);
        }
    }

    void unregister_callback(std::shared_ptr<ITouchInteractionCallback> callback) override {
        std::lock_guard lock(mutex_);
        callbacks_.erase(callback);
        
        if (callbacks_.empty()) {
            connection_->set_service_detects_gestures_enabled(display_id_, false);
        }
    }

    [[nodiscard]] auto get_state() const -> int override {
        std::lock_guard lock(mutex_);
        return state_;
    }

    [[nodiscard]] auto get_display_id() const -> int override {
        return display_id_;
    }

    // Internal Event Handling
    void on_motion_event(const MotionEvent& event) {
        std::lock_guard lock(mutex_);
        if (state_change_requested_) {
            queued_events_.push(event);
        } else {
            dispatch_event_locked(event);
        }
    }

    void on_state_changed(int new_state) {
        std::lock_guard lock(mutex_);
        state_ = new_state;
        state_change_requested_ = false;

        while (!queued_events_.empty()) {
            dispatch_event_locked(queued_events_.front());
            queued_events_.pop();
        }

        for (auto const& [callback, executor] : callbacks_) {
            executor->post([cb = callback, new_state]() {
                cb->on_state_changed(new_state);
            });
        }
    }

private:
    void dispatch_event_locked(const MotionEvent& event) {
        for (auto const& [callback, executor] : callbacks_) {
            executor->post([cb = callback, event]() {
                cb->on_motion_event(event);
            });
        }
    }

    void unregister_all() {
        std::lock_guard lock(mutex_);
        callbacks_.clear();
        if (connection_) {
             connection_->set_service_detects_gestures_enabled(display_id_, false);
        }
    }

    std::shared_ptr<internal::IAccessibilityServiceConnection> connection_;
    int display_id_;
    mutable std::mutex mutex_;
    std::map<std::shared_ptr<ITouchInteractionCallback>, std::shared_ptr<ndk::IThreadExecutor>> callbacks_;
    std::queue<MotionEvent> queued_events_;
    int state_{STATE_CLEAR};
    bool state_change_requested_{false};
};

} // namespace accessibility