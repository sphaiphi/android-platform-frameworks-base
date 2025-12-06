// accessibility_input_method_session_wrapper_impl.cpp
module;

#include <binder/Binder.h>
#include <binder/Status.h>
#include "android/view/inputmethod/BnAccessibilityInputMethodSession.h" // Assumed generated header

module accessibilityservice:accessibility_input_method_session_wrapper;

import :accessibility_input_method_session;
import <common/ndk_executor.cppm>;
import <memory>;
import <atomic>;
import <utility>;
import <functional>;

namespace android::accessibilityservice {

using ::android::view::inputmethod::BnAccessibilityInputMethodSession;
using ::android::binder::Status;

/**
 * @brief Private implementation of the session wrapper.
 *
 * This class is the actual Binder service object. It receives calls on
 * Binder threads and uses the executor to forward them to the correct thread.
 */
class AccessibilityInputMethodSessionWrapperImpl final : public BnAccessibilityInputMethodSession {
public:
    explicit AccessibilityInputMethodSessionWrapperImpl(
        std::shared_ptr<IAccessibilityInputMethodSession> session,
        std::shared_ptr<ndk::IThreadExecutor> executor)
        : session_ref_(std::move(session)), executor_(std::move(executor)) {}

    // Atomically clears the session reference to prevent further calls.
    void finish_session() {
        // Use exchange to atomically replace the pointer with nullptr
        auto old_session = session_ref_.exchange(nullptr);
        if (old_session && executor_) {
            executor_->post([s = std::move(old_session)]() {
                // The actual destruction happens here on the correct thread,
                // if this was the last shared_ptr.
            });
        }
    }

private:
    //======================================================================
    // Binder interface implementation
    //======================================================================

    Status finishInput() override {
        post_to_executor([this](const auto& session) {
            session->finish_input();
        });
        return Status::ok();
    }

    Status updateSelection(
        int32_t old_sel_start, int32_t old_sel_end,
        int32_t new_sel_start, int32_t new_sel_end,
        int32_t candidates_start, int32_t candidates_end) override {
        post_to_executor([=](const auto& session) {
            session->update_selection(old_sel_start, old_sel_end, new_sel_start, new_sel_end, candidates_start, candidates_end);
        });
        return Status::ok();
    }
    
    Status invalidateInput(const EditorInfo& editor_info,
                           const sp<IRemoteAccessibilityInputConnection>& connection,
                           int32_t session_id) override {
        // Note: For Binder objects (IRemote...), they must be handled carefully.
        // For this example, we assume `connection` can be converted to a shared_ptr.
        // In a real scenario, you'd manage the strong pointer `sp` correctly.
        auto shared_connection = std::shared_ptr<IRemoteAccessibilityInputConnection>(
            connection.get(), [connection](...){ /* Keep sp alive */ });

        post_to_executor([=, info = editor_info, conn = shared_connection](const auto& session) {
            session->invalidate_input(info, conn, session_id);
        });
        return Status::ok();
    }
    
    //======================================================================
    // Helper for thread marshalling
    //======================================================================

    // Generic helper to post a task to the executor.
    void post_to_executor(std::function<void(const std::shared_ptr<IAccessibilityInputMethodSession>&)> task) {
        if (!executor_) return;

        // Load the atomic shared_ptr safely.
        std::shared_ptr<IAccessibilityInputMethodSession> session = session_ref_.load();

        if (session) {
            executor_->post([s = std::move(session), t = std::move(task)]() {
                t(s);
            });
        }
    }

    // Thread-safe reference to the actual session implementation.
    std::atomic<std::shared_ptr<IAccessibilityInputMethodSession>> session_ref_;

    // Executor to post tasks to the service's main thread.
    std::shared_ptr<ndk::IThreadExecutor> executor_;
};

//======================================================================
// Public PIMPL class implementation
//======================================================================

AccessibilityInputMethodSessionWrapper::AccessibilityInputMethodSessionWrapper(
    std::shared_ptr<IAccessibilityInputMethodSession> session,
    std::shared_ptr<ndk::IThreadExecutor> executor)
    : impl_(std::make_unique<AccessibilityInputMethodSessionWrapperImpl>(std::move(session), std::move(executor))) {}

AccessibilityInputMethodSessionWrapper::~AccessibilityInputMethodSessionWrapper() {
    if (impl_) {
        impl_->finish_session();
    }
}

// Move constructor and assignment operator for proper resource transfer
AccessibilityInputMethodSessionWrapper::AccessibilityInputMethodSessionWrapper(AccessibilityInputMethodSessionWrapper&&) noexcept = default;
AccessibilityInputMethodSessionWrapper& AccessibilityInputMethodSessionWrapper::operator=(AccessibilityInputMethodSessionWrapper&&) noexcept = default;


} // namespace android::accessibilityservice