#pragma once

#include <android/view/InputChannel.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <memory>
#include <string>

namespace android {
namespace view {
namespace test {

/**
 * Mock InputChannel backed by a real Unix domain socket for testing.
 */
class MockInputChannel {
public:
    static auto create(std::string name = "mock_channel")
        -> std::shared_ptr<InputChannel> {
        // Use AF_UNIX SOCK_STREAM for byte-stream semantics (multiple writes = one read)
        int fds[2];
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) != 0) {
            return nullptr;
        }

        for (int fd : fds) {
            int flags = fcntl(fd, F_GETFL, 0);
            fcntl(fd, F_SETFL, flags | O_NONBLOCK);
        }

        auto* pair = new int[2]{fds[0], fds[1]};
        return std::make_shared<InputChannel>(std::move(name), pair);
    }

    static auto get_write_fd(const std::shared_ptr<InputChannel>& channel) -> int {
        return channel->write_fd();
    }

    static auto send(const std::shared_ptr<InputChannel>& channel,
                     const void* data, size_t len) -> ssize_t {
        int fd = channel->write_fd();
        if (fd < 0) return -1;
        return ::write(fd, data, len);
    }

    static auto send_motion_event(const std::shared_ptr<InputChannel>& channel,
                                  uint32_t sequence,
                                  float x, float y,
                                  int32_t key_code = 0) -> ssize_t {
        // Wire format: 19-byte header + 48-byte payload = 67 bytes
        uint8_t buf[67];
        size_t offset = 0;

        // Header (19 bytes)
        std::memcpy(buf + offset, &sequence, sizeof(uint32_t)); offset += 4;
        buf[offset] = 1; offset++; // WIRE_EVENT_TYPE_MOTION
        buf[offset] = 0; offset++; // ACTION_DOWN
        std::memcpy(buf + offset, &key_code, sizeof(int32_t)); offset += 4; // device_id
        uint32_t source = 0x00000002; // SOURCE_TOUCHSCREEN
        std::memcpy(buf + offset, &source, sizeof(uint32_t)); offset += 4;
        buf[offset] = 0; offset++; // history_size
        uint32_t pointer_count = 1;
        std::memcpy(buf + offset, &pointer_count, sizeof(uint32_t)); offset += 4; // 19 bytes

        // Payload (48 bytes) - matches parser's WIRE_MOTION_BASE_SIZE
        // Parser reads: event_time@payload[20], x@payload[24], y@payload[28]
        uint32_t meta = 0, btn = 0, edge = 0, mode = 1;
        std::memcpy(buf + offset, &meta, 4); offset += 4; // 20: meta_state
        std::memcpy(buf + offset, &btn, 4); offset += 4; // 24: button_state
        std::memcpy(buf + offset, &edge, 4); offset += 4; // 28: edge_flags
        std::memcpy(buf + offset, &mode, 4); offset += 4; // 32: mode
        int64_t event_time = 0;
        std::memcpy(buf + offset, &event_time, 8); offset += 8; // 36: event_time (payload[20])
        float fx = x, fy = y;
        std::memcpy(buf + offset, &fx, 4); offset += 4; // 44: x (payload[24])
        std::memcpy(buf + offset, &fy, 4); offset += 4; // 48: y (payload[28])
        // Padding to reach 48-byte payload (bytes 52-66)
        memset(buf + offset, 0, 67 - offset);

        return send(channel, buf, 67);
    }

    static auto send_key_event(const std::shared_ptr<InputChannel>& channel,
                               uint32_t sequence,
                               int32_t key_code) -> ssize_t {
        // Wire format: 19-byte header + 24-byte payload = 43 bytes
        uint8_t buf[43];
        memset(buf, 0, sizeof(buf));
        size_t offset = 0;

        // Header (19 bytes)
        std::memcpy(buf + offset, &sequence, sizeof(uint32_t)); offset += 4;
        buf[offset] = 2; offset++; // WIRE_EVENT_TYPE_KEY
        buf[offset] = 0; offset++; // ACTION_DOWN
        int32_t device_id = 0;
        std::memcpy(buf + offset, &device_id, sizeof(int32_t)); offset += 4;
        uint32_t source = 0x00000100; // SOURCE_KEYBOARD
        std::memcpy(buf + offset, &source, sizeof(uint32_t)); offset += 4;
        buf[offset] = 0; offset++; // history_size
        uint32_t _pc = 0;
        std::memcpy(buf + offset, &_pc, sizeof(uint32_t)); offset += 4; // 19 bytes

        // Payload (24 bytes) - matches parser's WIRE_KEY_BASE_SIZE
        uint32_t meta = 0, repeat = 0;
        std::memcpy(buf + offset, &meta, 4); offset += 4; // 20: meta_state
        std::memcpy(buf + offset, &repeat, 4); offset += 4; // 24: repeat_count
        std::memcpy(buf + offset, &device_id, 4); offset += 4; // 28: device_id
        int64_t event_time = 0;
        std::memcpy(buf + offset, &event_time, 8); offset += 8; // 36: event_time
        std::memcpy(buf + offset, &key_code, sizeof(int32_t)); offset += 4; // 44: key_code

        return send(channel, buf, 43);
    }

    static void destroy(std::shared_ptr<InputChannel>& channel) {
        channel->close();
    }
};

} // namespace test
} // namespace view
} // namespace android
