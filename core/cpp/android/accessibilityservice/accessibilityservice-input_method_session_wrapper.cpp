// accessibilityservice-input_method_session_wrapper.cpp
module;

#include <binder/Binder.h>
#include <binder/Status.h>
// #include "android/view/inputmethod/BnAccessibilityInputMethodSession.h" // Assumed generated header

module accessibilityservice:input_method_session_wrapper;

import :input_method_session;
import :types;
import ndk_executor;
import <memory>;
import <atomic>;
import <utility>;
import <functional>;

// Mocking BnAccessibilityInputMethodSession for compilation in this context
namespace android::view::inputmethod {
    class BnAccessibilityInputMethodSession : public android::BBinder {
    public:
        virtual android::binder::Status finishInput() = 0;
        virtual android::binder::Status updateSelection(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t) = 0;
        // virtual android::binder::Status invalidateInput(...) = 0;
    };
}

namespace android::accessibilityservice {

using ::android::view::inputmethod::BnAccessibilityInputMethodSession;
using ::android::binder::Status;

class AccessibilityInputMethodSessionWrapperImpl final : public BnAccessibilityInputMethodSession {
public:
    explicit AccessibilityInputMethodSessionWrapperImpl(
        std::shared_ptr<IAccessibilityInputMethodSession> session,
        std::shared_ptr<ndk::IThreadExecutor> executor)
        : session_ref_(std::move(session)), executor_(std::move(executor)) {}

    void finish_session() {
        auto old_session = session_ref_.exchange(nullptr);
        if (old_session && executor_) {
            executor_->post([s = std::move(old_session)]() {});
        }
    }

private:
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
    
    // Status invalidateInput(...) override { ... }

    void post_to_executor(std::function<void(const std::shared_ptr<IAccessibilityInputMethodSession>&)> task) {
        if (!executor_) return;
        std::shared_ptr<IAccessibilityInputMethodSession> session = session_ref_.load();
        if (session) {
            executor_->post([s = std::move(session), t = std::move(task)]() {
                t(s);
            });
        }
    }

    std::atomic<std::shared_ptr<IAccessibilityInputMethodSession>> session_ref_;
    std::shared_ptr<ndk::IThreadExecutor> executor_;
};

AccessibilityInputMethodSessionWrapper::AccessibilityInputMethodSessionWrapper(
    std::shared_ptr<IAccessibilityInputMethodSession> session,
    std::shared_ptr<ndk::IThreadExecutor> executor)
    : impl_(std::make_unique<AccessibilityInputMethodSessionWrapperImpl>(std::move(session), std::move(executor))) {}

AccessibilityInputMethodSessionWrapper::~AccessibilityInputMethodSessionWrapper() {
    if (impl_) {
        impl_->finish_session();
    }
}

AccessibilityInputMethodSessionWrapper::AccessibilityInputMethodSessionWrapper(AccessibilityInputMethodSessionWrapper&&) noexcept = default;
AccessibilityInputMethodSessionWrapper& AccessibilityInputMethodSessionWrapper::operator=(AccessibilityInputMethodSessionWrapper&&) noexcept = default;

} // namespace android::accessibilityservice