#pragma once

#include <cstdint>

namespace android::view {

// Visibility states matching Java View.VISIBLE/INVISIBLE/GONE
enum class Visibility : int {
    Visible = 0,
    Invisible = 4,
    Gone = 8,
};

// Layout direction
enum class LayoutDirection : int {
    Ltr = 0,
    Rtl = 1,
};

// View bit flags
enum class ViewFlags : uint32_t {
    NONE           = 0x00000000,
    FOCUSABLE      = 0x00000001,
    CLICKABLE      = 0x00000002,
    LONG_CLICKABLE = 0x00000004,
    ENABLED        = 0x00000008,
};

// ViewGroup bit flags
enum class ViewGroupFlags : uint32_t {
    CLIP_CHILDREN   = 0x00000001,
    CLIP_TO_PADDING = 0x00000002,
};

// Descendant focusability modes
enum class DescendantFocusability : int {
    FOCUS_BEFORE_DESCENDANTS    = 0,
    FOCUS_AFTER_DESCENDANTS     = 1,
    FOCUS_BLOCK_DESCENDANTS     = 2,
};

// Measure specification: packed mode + size (30-bit size, 2-bit mode)
struct MeasureSpec {
    static constexpr uint32_t MODE_SHIFT = 30;
    static constexpr uint32_t MODE_MASK  = 0xC0000000;
    static constexpr uint32_t SIZE_MASK  = 0x3FFFFFFF;

    static constexpr uint32_t UNSPECIFIED = 0x00000000;
    static constexpr uint32_t EXACTLY     = 0x40000000;
    static constexpr uint32_t AT_MOST     = 0x80000000;

    static constexpr auto make(uint32_t size, uint32_t mode) -> uint32_t {
        return (size & SIZE_MASK) | (mode & MODE_MASK);
    }

    static constexpr auto get_mode(uint32_t spec) -> uint32_t {
        return spec & MODE_MASK;
    }

    static constexpr auto get_size(uint32_t spec) -> uint32_t {
        return spec & SIZE_MASK;
    }
};

} // namespace android::view
