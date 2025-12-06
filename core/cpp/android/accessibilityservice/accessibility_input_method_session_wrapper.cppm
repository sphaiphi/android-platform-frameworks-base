// accessibility_input_method_session_wrapper.cppm
export module accessibilityservice:accessibility_input_method_session_wrapper;

import :accessibility_input_method_session;
import <common/ndk_executor.cppm>; // Assumed executor interface
import <memory>;

export namespace android::accessibilityservice {

// Forward-declare the implementation class
class AccessibilityInputMethodSessionWrapperImpl;

/**
 * @brief A thread-safe Binder wrapper for an IAccessibilityInputMethodSession.
 *
 * This class receives IPC calls from the system on Binder threads and safely
 * posts them to the service's main thread via an executor.
 */
class AccessibilityInputMethodSessionWrapper final {
public:
    explicit AccessibilityInputMethodSessionWrapper(
        std::shared_ptr<IAccessibilityInputMethodSession> session,
        std::shared_ptr<ndk::IThreadExecutor> executor);

    ~AccessibilityInputMethodSessionWrapper();

    // Rule of Five: This class manages a unique resource (the PIMPL pointer)
    // and should have a single, clear ownership model.
    AccessibilityInputMethodSessionWrapper(const AccessibilityInputMethodSessionWrapper&) = delete;
    AccessibilityInputMethodSessionWrapper& operator=(const AccessibilityInputMethodSessionWrapper&) = delete;
    AccessibilityInputMethodSessionWrapper(AccessibilityInputMethodSessionWrapper&&) noexcept;
    AccessibilityInputMethodSessionWrapper& operator=(AccessibilityInputMethodSessionWrapper&&) noexcept;

private:
    std::unique_ptr<AccessibilityInputMethodSessionWrapperImpl> impl_;
};

} // namespace android::accessibilityservice