// AccessibilityInputMethodSession.cppm
export module AccessibilityInputMethodSession;

import AccessibilityInterfaces;
import ndk_executor; // From the provided header
import <memory>;
import <utility>; // For std::move
import <atomic>;
import <expected>;
import <system_error>;

export class AccessibilityInputMethodSession final : public IAccessibilityInputMethodSession,
                                                     public std::enable_shared_from_this<AccessibilityInputMethodSession> {
public:
    // Deleted copy/move operations for safety.
    AccessibilityInputMethodSession(const AccessibilityInputMethodSession&) = delete;
    auto operator=(const AccessibilityInputMethodSession&) -> AccessibilityInputMethodSession& = delete;
    AccessibilityInputMethodSession(AccessibilityInputMethodSession&&) = delete;
    auto operator=(AccessibilityInputMethodSession&&) -> AccessibilityInputMethodSession& = delete;

    // Factory function to safely create and initialize the session.
    [[nodiscard]] static auto create() -> std::expected<std::shared_ptr<AccessibilityInputMethodSession>, std::runtime_error> {
        try {
            auto executor = ndk::NdkThreadExecutor::create();
            // Private constructor pattern to use with enable_shared_from_this
            struct MakeSharedEnabler : public AccessibilityInputMethodSession {
                explicit MakeSharedEnabler(std::shared_ptr<ndk::IThreadExecutor> exec)
                    : AccessibilityInputMethodSession(std::move(exec)) {}
            };
            auto session = std::make_shared<MakeSharedEnabler>(std::move(executor));
            return session;
        } catch (const std::runtime_error& e) {
            return std::unexpected(e);
        }
    }

    ~AccessibilityInputMethodSession() override = default;

    // Enqueues a task to set the enabled state.
    void set_enabled(bool enabled) override {
        executor_->post([self = shared_from_this(), enabled] {
            self->handle_set_enabled(enabled);
        });
    }

    // Enqueues a task to finish the input session.
    void finish_input() override {
        executor_->post([self = shared_from_this()] {
            self->handle_finish_input();
        });
    }

    // Enqueues a task to update text selection.
    void update_selection(
        std::int32_t old_sel_start, std::int32_t old_sel_end,
        std::int32_t new_sel_start, std::int32_t new_sel_end,
        std::int32_t candidates_start, std::int32_t candidates_end) override {
        executor_->post([self = shared_from_this(), old_sel_start, old_sel_end, new_sel_start, new_sel_end, candidates_start, candidates_end] {
            self->handle_update_selection(old_sel_start, old_sel_end, new_sel_start, new_sel_end, candidates_start, candidates_end);
        });
    }

    // Enqueues a task to invalidate and re-initialize the input state.
    void invalidate_input(
        EditorInfo editor_info,
        std::shared_ptr<IRemoteAccessibilityInputConnection> connection,
        SessionId session_id) override {
        executor_->post([self = shared_from_this(),
                           editor_info = std::move(editor_info),
                           connection = std::move(connection),
                           session_id] () mutable {
            self->handle_invalidate_input(std::move(editor_info), std::move(connection), session_id);
        });
    }

private:
    // Private constructor for factory pattern.
    explicit AccessibilityInputMethodSession(std::shared_ptr<ndk::IThreadExecutor> executor)
        : executor_{std::move(executor)} {}

    // --- Internal handlers that run on the executor thread ---

    void handle_set_enabled(bool enabled) {
        enabled_.store(enabled, std::memory_order_relaxed);
    }

    void handle_finish_input() {
        if (!is_active()) return;
        connection_.reset();
        editor_info_.reset();
        session_id_.reset();
    }

    void handle_update_selection(
        std::int32_t /*old_sel_start*/, std::int32_t /*old_sel_end*/,
        std::int32_t /*new_sel_start*/, std::int32_t /*new_sel_end*/,
        std::int32_t /*candidates_start*/, std::int32_t /*candidates_end*/) {
        if (!is_active()) return;
        // Logic to process selection change would go here.
    }

    void handle_invalidate_input(
        EditorInfo editor_info,
        std::shared_ptr<IRemoteAccessibilityInputConnection> connection,
        SessionId session_id) {
        if (!is_enabled()) return;
        editor_info_ = std::move(editor_info);
        connection_ = std::move(connection);
        session_id_ = session_id;
    }

    // Helper to check the session's active state on the executor thread.
    [[nodiscard]] auto is_active() const -> bool {
        return is_enabled() && connection_ && session_id_.has_value();
    }

    // Helper to check if the session is enabled.
    [[nodiscard]] auto is_enabled() const -> bool {
        return enabled_.load(std::memory_order_relaxed);
    }

    // Member variables - state is guarded by the executor.
    std::shared_ptr<ndk::IThreadExecutor> executor_;
    std::atomic<bool> enabled_{true};
    std::optional<EditorInfo> editor_info_{};
    std::shared_ptr<IRemoteAccessibilityInputConnection> connection_{};
    std::optional<SessionId> session_id_{};
};