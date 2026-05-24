#include <android/app/Exceptions.h>

namespace android::app {

auto ServiceStartNotAllowedException::newInstance(bool foreground, const std::string& message) -> std::unique_ptr<ServiceStartNotAllowedException> {
    if (foreground) {
        return std::make_unique<ForegroundServiceStartNotAllowedException>(message);
    } else {
        return std::make_unique<BackgroundServiceStartNotAllowedException>(message);
    }
}

} // namespace android::app
