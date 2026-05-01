#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <expected_shim.h>

namespace android::graphics {

/**
 * Static utility functions for manipulating color integers.
 * Colors are packed as 0xAARRGGBB.
 */
class Color {
public:
    // --- Constants ---
    static constexpr uint32_t BLACK         = 0xFF000000;
    static constexpr uint32_t WHITE         = 0xFFFFFFFF;
    static constexpr uint32_t RED           = 0xFFFF0000;
    static constexpr uint32_t GREEN         = 0xFF00FF00;
    static constexpr uint32_t BLUE          = 0xFF0000FF;
    static constexpr uint32_t CYAN          = 0xFF00FFFF;
    static constexpr uint32_t MAGENTA       = 0xFFFF00FF;
    static constexpr uint32_t YELLOW        = 0xFFFFFF00;
    static constexpr uint32_t TRANSPARENT   = 0x00000000;
    static constexpr uint32_t LEGACY_BLACK  = 0xFF000000;

    // --- Factory ---
    static uint32_t argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
    static uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);

    // --- Accessors ---
    static uint8_t getRed(uint32_t color);
    static uint8_t getGreen(uint32_t color);
    static uint8_t getBlue(uint32_t color);
    static uint8_t getAlpha(uint32_t color);

    // --- Manipulation ---
    static uint32_t setColorAlpha(uint32_t color, uint8_t alpha);
    static uint32_t setAlphaColor(uint8_t alpha, uint32_t color);

    // --- Parsing ---
    [[nodiscard]] static std::expected<uint32_t, std::string> parseColor(std::string_view str);

    // --- Formatting ---
    static std::string toArgbString(uint32_t color);
};

} // namespace android::graphics
