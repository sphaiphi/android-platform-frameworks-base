// accessibilityservice-input_method_session_wrapper.cppm
export module accessibilityservice:input_method_session_wrapper;

import :input_method_session;
import ndk_executor;
import <memory>;

export namespace android::accessibilityservice {

class AccessibilityInputMethodSessionWrapperImpl;

class AccessibilityInputMethodSessionWrapper final {
public:
    explicit AccessibilityInputMethodSessionWrapper(
        std::shared_ptr<IAccessibilityInputMethodSession> session,
        std::shared_ptr<ndk::IThreadExecutor> executor);

    ~AccessibilityInputMethodSessionWrapper();

    AccessibilityInputMethodSessionWrapper(const AccessibilityInputMethodSessionWrapper&) = delete;
    AccessibilityInputMethodSessionWrapper& operator=(const AccessibilityInputMethodSessionWrapper&) = delete;
    AccessibilityInputMethodSessionWrapper(AccessibilityInputMethodSessionWrapper&&) noexcept;
    AccessibilityInputMethodSessionWrapper& operator=(AccessibilityInputMethodSessionWrapper&&) noexcept;

private:
    std::unique_ptr<AccessibilityInputMethodSessionWrapperImpl> impl_;
};

} // namespace android::accessibilityservice