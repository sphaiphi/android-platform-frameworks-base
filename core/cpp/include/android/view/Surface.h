#pragma once

#include <cstdint>
#include <memory>

namespace android::view {

/**
 * Lightweight wrapper around a native Surface handle.
 * In the real Android framework this interfaces with the SurfaceFlinger compositor.
 * For host builds this is a handle wrapper only.
 */
class Surface {
public:
    Surface() = default;
    explicit Surface(void* native_handle);

    [[nodiscard]] bool is_valid() const;
    [[nodiscard]] void* get_native_handle() const { return native_handle_; }

private:
    void* native_handle_{nullptr};
};

} // namespace android::view
