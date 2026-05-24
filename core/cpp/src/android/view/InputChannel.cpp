#define _GNU_SOURCE
#include <android/view/InputChannel.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

namespace android::view {

InputChannel::InputChannel(std::string name, void* native_handle)
    : name_(std::move(name)), native_handle_(native_handle) {}

bool InputChannel::is_valid() const {
    return native_handle_ != nullptr;
}

auto InputChannel::read_fd() const -> int {
    if (!native_handle_) return -1;
    int* fds = static_cast<int*>(native_handle_);
    return fds[0];
}

auto InputChannel::write_fd() const -> int {
    if (!native_handle_) return -1;
    int* fds = static_cast<int*>(native_handle_);
    return fds[1];
}

void InputChannel::close() {
    if (!native_handle_) return;
    int* fds = static_cast<int*>(native_handle_);
    if (fds[0] >= 0) ::close(fds[0]);
    if (fds[1] >= 0) ::close(fds[1]);
    native_handle_ = nullptr;
}

auto InputChannel::send_handled(bool handled) const -> int {
    int fd = write_fd();
    if (fd < 0) return -1;
    uint8_t byte = handled ? 1 : 0;
    return ::write(fd, &byte, 1);
}

} // namespace android::view
