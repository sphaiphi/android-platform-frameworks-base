#pragma once

#include <cstdint>
#include <string>
#include <memory>

namespace android::view {

/**
 * Wrapper around a native input channel (socket pair for delivering input events).
 * For host builds this is a handle wrapper only.
 */
class InputChannel {
public:
    InputChannel() = default;
    InputChannel(std::string name, void* native_handle);

    [[nodiscard]] bool is_valid() const;
    [[nodiscard]] const std::string& name() const { return name_; }
    [[nodiscard]] void* get_native_handle() const { return native_handle_; }

    [[nodiscard]] auto read_fd() const -> int;
    [[nodiscard]] auto write_fd() const -> int;
    void close();
    auto send_handled(bool handled) const -> int;

private:
    std::string name_;
    void* native_handle_{nullptr};
};

} // namespace android::view
