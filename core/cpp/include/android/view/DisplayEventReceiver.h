#pragma once

/**
 * DisplayEventReceiver — VSync and display event consumer.
 *
 * Wraps the native android::DisplayEventReceiver (from libui on-device,
 * or MockDisplayEventReceiver on host builds) and registers its FD with
 * a Looper for async event delivery.
 *
 * Thread safety: NOT thread-safe. All public methods must be called from
 * the associated Looper thread.
 *
 * RAII: FD is closed in destructor. Looper registration cleaned up in dispose().
 */

#include <android/os/Looper.h>
#include <functional>
#include <memory>
#include <cstdint>

// Forward declarations for event types
namespace android {
namespace ui {
    enum class DisplayEventType : int32_t;
    struct VsyncEventData;
}
}

namespace android::view {

/**
 * VSync event data passed to callbacks.
 */
struct VsyncEventData {
    int64_t timestamp;  // nanoseconds (monotonic clock)
    uint32_t count;     // VSync pulse count
    uint32_t vsync_id;  // reserved for future use
};

/**
 * DisplayEventReceiver public interface.
 *
 * On-device: wraps android::DisplayEventReceiver from libui.
 * On host (HOST_BUILD): wraps MockDisplayEventReceiver from android_mock/ui/.
 */
class DisplayEventReceiver {
public:
    /**
     * Callback type for VSync events.
     */
    using VsyncCallback = std::function<void(const VsyncEventData&)>;

    /**
     * Create a DisplayEventReceiver associated with the given Looper.
     *
     * @param looper  The Looper thread this receiver belongs to. Must not be null.
     * @param callback  VSync callback (may be null; set later via set_vsync_callback).
     * @throws std::runtime_error if looper is null or socket pair creation fails.
     */
    explicit DisplayEventReceiver(std::shared_ptr<os::Looper> looper,
                                  VsyncCallback callback);

    /**
     * Destructor: disposes and closes the native receiver.
     */
    ~DisplayEventReceiver();

    // Non-copyable, movable
    DisplayEventReceiver(const DisplayEventReceiver&) = delete;
    DisplayEventReceiver& operator=(const DisplayEventReceiver&) = delete;
    DisplayEventReceiver(DisplayEventReceiver&&) noexcept;
    DisplayEventReceiver& operator=(DisplayEventReceiver&&) noexcept;

    /**
     * Request a single VSync pulse from SurfaceFlinger.
     * Must be called from the Looper thread.
     * No-op if already disposed.
     */
    void schedule_vsync();

    /**
     * Dispose of the receiver: unregisters from Looper and closes the FD.
     * Safe to call multiple times. No-op if already disposed.
     */
    void dispose();

    /**
     * Check if the receiver has been disposed.
     */
    [[nodiscard]] auto is_disposed() const -> bool;

    /**
     * Register the receiver's FD with the Looper for async polling.
     * Must be called from the Looper thread.
     * No-op if already registered or disposed.
     */
    void register_with_looper();

    /**
     * Unregister the FD watcher from the Looper.
     * Must be called from the Looper thread.
     * No-op if not registered.
     */
    void unregister_from_looper();

    /**
     * Get the associated Looper.
     */
    [[nodiscard]] auto get_looper() const -> std::shared_ptr<os::Looper>;

    /**
     * Get the current frame interval in nanoseconds.
     * Default is 60Hz (16666667 ns).
     */
    [[nodiscard]] auto get_frame_interval_nanos() const -> int64_t;

    /**
     * Set the VSync callback. Called internally by Choreographer factory.
     * Must be called from the Looper thread.
     */
    void set_vsync_callback(VsyncCallback callback);

    /**
     * Internal: called by the Looper FD callback when data is available.
     * Must be called from the Looper thread.
     */
    void on_data_available();

private:
    /**
     * Parse and dispatch VSync events from the native receiver.
     * Must be called from the Looper thread.
     */
    void dispatch_events();

    // -- State --
    std::shared_ptr<os::Looper> m_looper_;
    VsyncCallback m_vsync_callback_;

    // Native receiver handle (RAII -- closed in destructor)
    // Wrapped in unique_ptr because native type may not be available on host
    struct NativeReceiver;
    std::unique_ptr<NativeReceiver> m_native_;

    // FD watcher registration
    bool m_disposed_ = false;
    bool m_fd_watcher_registered_ = false;
    int m_fd_watcher_cookie_ = 0;
    int m_fd_ = -1;

    // Frame interval (computed from display refresh rate)
    int64_t m_frame_interval_nanos_ = 16666667; // 60Hz default
};

} // namespace view
