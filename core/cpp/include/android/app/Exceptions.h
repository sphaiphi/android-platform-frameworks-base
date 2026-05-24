#pragma once

#include <stdexcept>
#include <string>
#include <memory>
#include <android/app/RemoteAction.h>

namespace android::app {

/**
 * Base class for all Android-specific exceptions in the app module.
 */
class AndroidException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

/**
 * Thrown when an application attempts to perform an operation that is not allowed.
 */
class IllegalStateException : public AndroidException {
public:
    using AndroidException::AndroidException;
};

/**
 * Thrown when a security violation is detected.
 */
class SecurityException : public AndroidException {
public:
    using AndroidException::AndroidException;
};

/**
 * Base class for exceptions thrown when a service cannot be started.
 */
class ServiceStartNotAllowedException : public IllegalStateException {
public:
    using IllegalStateException::IllegalStateException;

    static auto newInstance(bool foreground, const std::string& message) -> std::unique_ptr<ServiceStartNotAllowedException>;
};

class ForegroundServiceStartNotAllowedException : public ServiceStartNotAllowedException {
public:
    using ServiceStartNotAllowedException::ServiceStartNotAllowedException;
};

class BackgroundServiceStartNotAllowedException : public ServiceStartNotAllowedException {
public:
    using ServiceStartNotAllowedException::ServiceStartNotAllowedException;
};

/**
 * A SecurityException that provides a way for the user to recover.
 */
class RecoverableSecurityException : public SecurityException {
public:
    RecoverableSecurityException(const std::string& message, const std::string& userMessage, std::shared_ptr<RemoteAction> userAction)
        : SecurityException(message), user_message_(userMessage), user_action_(std::move(userAction)) {}

    [[nodiscard]] auto get_user_message() const -> const std::string& { return user_message_; }
    [[nodiscard]] auto get_user_action() const -> std::shared_ptr<RemoteAction> { return user_action_; }

private:
    std::string user_message_;
    std::shared_ptr<RemoteAction> user_action_;
};

} // namespace android::app
