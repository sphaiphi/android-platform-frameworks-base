#include <android/view/InputChannel.h>

namespace android::view {

InputChannel::InputChannel(std::string name, void* native_handle)
    : name_(std::move(name)), native_handle_(native_handle) {}

bool InputChannel::is_valid() const {
    return native_handle_ != nullptr;
}

} // namespace android::view
