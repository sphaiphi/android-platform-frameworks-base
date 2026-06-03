#pragma once

/**
 * Mock DisplayEventReceiver for host builds.
 *
 * Simulates VSync events from SurfaceFlinger using an AF_UNIX socket pair.
 * Tests write raw VSync event data to the write-end FD; the DisplayEventReceiver
 * reads from the read-end FD via its Looper-registered FD.
 *
 * Wire format matches android::DisplayEventReceiver::Event union from libui.
 */

#include <cstdint>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <memory>
#include <string>

namespace android::ui {

/**
 * Event type constants matching android::DisplayEventReceiver::Event::type.
 */
enum class DisplayEventType : int32_t {
    VSYNC = 0,
    HOTPLUG = 1,
    REFRESH = 2,
    CONTENT_ORIENTATION = 3,
};

/**
 * VSync event data payload.
 */
struct VsyncEventData {
    int64_t timestamp;  // nanoseconds (monotonic clock)
    uint32_t count;     // VSync pulse count
    uint32_t vsync_id;  // reserved for future use
};

/**
 * Hotplug event data payload.
 */
struct HotplugEventData {
    int32_t display;
    int32_t connected;
    int64_t timestamp;
};

/**
 * Unified event union matching libui layout.
 */
struct DisplayEvent {
    DisplayEventType type;
    union {
        VsyncEventData vsync;
        HotplugEventData hotplug;
    };
};

/**
 * Mock native DisplayEventReceiver using a pipe (AF_UNIX SOCK_DGRAM) for
 * event delivery. SOCK_DGRAM preserves message boundaries so each write()
 * is read as a single event (matching the real libui pipe semantics).
 */
class MockDisplayEventReceiver {
public:
    MockDisplayEventReceiver() : m_read_fd_(-1), m_write_fd_(-1) {
        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, m_fds_) != 0) {
            m_read_fd_ = -1;
            m_write_fd_ = -1;
            return;
        }
        m_read_fd_ = m_fds_[0];
        m_write_fd_ = m_fds_[1];

        for (int fd : m_fds_) {
            int flags = fcntl(fd, F_GETFL, 0);
            fcntl(fd, F_SETFL, flags | O_NONBLOCK);
        }
    }

    ~MockDisplayEventReceiver() {
        close();
    }

    // Non-copyable
    MockDisplayEventReceiver(const MockDisplayEventReceiver&) = delete;
    MockDisplayEventReceiver& operator=(const MockDisplayEventReceiver&) = delete;

    // Movable
    MockDisplayEventReceiver(MockDisplayEventReceiver&& other) noexcept
        : m_read_fd_(other.m_read_fd_), m_write_fd_(other.m_write_fd_) {
        other.m_read_fd_ = -1;
        other.m_write_fd_ = -1;
        other.m_fds_[0] = -1;
        other.m_fds_[1] = -1;
    }

    /**
     * Get the read-end FD for Looper registration.
     */
    [[nodiscard]] auto getFd() const -> int {
        return m_read_fd_;
    }

    /**
     * Check if the receiver is valid (socket pair created successfully).
     */
    [[nodiscard]] auto isValid() const -> bool {
        return m_read_fd_ >= 0 && m_write_fd_ >= 0;
    }

    /**
     * Write a VSync event to the mock receiver.
     * Called by tests to simulate a VSync pulse from SurfaceFlinger.
     */
    static auto write_vsync_event(int write_fd, int64_t timestamp, uint32_t count) -> bool {
        DisplayEvent event;
        event.type = DisplayEventType::VSYNC;
        event.vsync.timestamp = timestamp;
        event.vsync.count = count;
        event.vsync.vsync_id = 0;

        ssize_t n = ::write(write_fd, &event, sizeof(event));
        return n == static_cast<ssize_t>(sizeof(event));
    }

    /**
     * Write a hotplug event to the mock receiver.
     */
    static auto write_hotplug_event(int write_fd, int32_t display, bool connected, int64_t timestamp) -> bool {
        DisplayEvent event;
        event.type = DisplayEventType::HOTPLUG;
        event.hotplug.display = display;
        event.hotplug.connected = connected ? 1 : 0;
        event.hotplug.timestamp = timestamp;

        ssize_t n = ::write(write_fd, &event, sizeof(event));
        return n == static_cast<ssize_t>(sizeof(event));
    }

    /**
     * Dispose of the receiver and close FDs.
     */
    void close() {
        if (m_read_fd_ >= 0) {
            ::close(m_read_fd_);
            m_read_fd_ = -1;
        }
        if (m_write_fd_ >= 0) {
            ::close(m_write_fd_);
            m_write_fd_ = -1;
        }
        m_fds_[0] = -1;
        m_fds_[1] = -1;
    }

    /**
     * Drain any pending events from the read FD (for test cleanup).
     */
    void drain_events() {
        char buf[256];
        while (m_read_fd_ >= 0) {
            ssize_t n = ::read(m_read_fd_, buf, sizeof(buf));
            if (n <= 0) break;
        }
    }

private:
    int m_fds_[2] = {-1, -1};
    int m_read_fd_ = -1;
    int m_write_fd_ = -1;
};

} // namespace android::ui
