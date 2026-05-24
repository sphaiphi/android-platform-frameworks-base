#pragma once

#include <android/view/LayoutParams.h>
#include <cstdint>

namespace android::view {

/**
 * Window-specific layout parameters extending base LayoutParams.
 * Mirrors android.view.WindowManager.LayoutParams.
 */
class WindowLayoutParams : public LayoutParams {
public:
    // Window types
    static constexpr int32_t TYPE_APPLICATION = 1;
    static constexpr int32_t TYPE_APPLICATION_STARTING = 2;
    static constexpr int32_t TYPE_APPLICATION_PANEL = 1;
    static constexpr int32_t TYPE_SYSTEM_OVERLAY = -3;
    static constexpr int32_t TYPE_SYSTEM_ALERT = -2;
    static constexpr int32_t TYPE_PHONE = -12;
    static constexpr int32_t TYPE_SYSTEM_ERROR = -1;
    static constexpr int32_t TYPE_STATUS_BAR = -11;
    static constexpr int32_t TYPE_SEARCH_BAR = -9;

    // Window flags
    static constexpr int32_t FLAG_NOT_FOCUSABLE = 0x00000008;
    static constexpr int32_t FLAG_NOT_TOUCHABLE = 0x00000020;
    static constexpr int32_t FLAG_LAYOUT_IN_SCREEN = 0x00000050;
    static constexpr int32_t FLAG_LAYOUT_NO_LIMITS = 0x00000400;
    static constexpr int32_t FLAG_FULLSCREEN = 0x00000080;
    static constexpr int32_t FLAG_HARDWARE_ACCELERATED = 0x00080000;

    // Pixel formats
    static constexpr int32_t FORMAT_TRANSLUCENT = -3;
    static constexpr int32_t FORMAT_TRANSPARENT = -2;
    static constexpr int32_t FORMAT_OPAQUE = -1;

    int32_t type{TYPE_APPLICATION};
    int32_t flags{0};
    int32_t format{FORMAT_TRANSLUCENT};
    int32_t gravity{0};
    int32_t x{0};
    int32_t y{0};
    float alpha{1.0f};
    int32_t softInputMode{0};

    WindowLayoutParams(int32_t w, int32_t h)
        : LayoutParams(w, h) {}

    virtual ~WindowLayoutParams() = default;
};

} // namespace android::view
