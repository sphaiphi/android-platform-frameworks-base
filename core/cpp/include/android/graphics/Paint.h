#pragma once

#include <android/graphics/Color.h>
#include <string_view>
#include <cstdint>

namespace android::graphics {

/**
 * Paint holds the style and color information about how to draw shapes, text, and bitmaps.
 */
class Paint {
public:
    enum class Style {
        FILL = 0,
        STROKE = 1,
        FILL_AND_STROKE = 2
    };

    enum class StrokeCap {
        BUTT = 0,
        ROUND = 1,
        SQUARE = 2
    };

    enum class StrokeJoin {
        MITER = 0,
        ROUND = 1,
        BEVEL = 2
    };

    enum class TextAlign {
        LEFT = 0,
        CENTER = 1,
        RIGHT = 2
    };

    Paint() = default;
    Paint(const Paint&) = default;
    Paint& operator=(const Paint&) = default;

    // Style
    void set_style(Style style);
    [[nodiscard]] Style get_style() const;

    // Color
    void set_color(uint32_t color);
    [[nodiscard]] uint32_t get_color() const;

    // Alpha
    void set_alpha(uint8_t alpha);
    [[nodiscard]] uint8_t get_alpha() const;

    // Stroke
    void set_stroke_width(float width);
    [[nodiscard]] float get_stroke_width() const;

    void set_stroke_cap(StrokeCap cap);
    [[nodiscard]] StrokeCap get_stroke_cap() const;

    void set_stroke_join(StrokeJoin join);
    [[nodiscard]] StrokeJoin get_stroke_join() const;

    void set_stroke_miter(float miter);
    [[nodiscard]] float get_stroke_miter() const;

    // Text
    void set_text_size(float size);
    [[nodiscard]] float get_text_size() const;

    void set_text_align(TextAlign align);
    [[nodiscard]] TextAlign get_text_align() const;

    [[nodiscard]] float measureText(std::string_view text) const;

    // Flags
    void set_anti_alias(bool enable);
    [[nodiscard]] bool is_anti_alias() const;

    void set_dither(bool enable);
    [[nodiscard]] bool is_dither() const;

    void set_filter_bitmap(bool enable);
    [[nodiscard]] bool is_filter_bitmap() const;

private:
    Style style_{Style::FILL};
    uint32_t color_{0xFF000000};
    uint8_t alpha_{255};
    float stroke_width_{0.0f};
    StrokeCap stroke_cap_{StrokeCap::BUTT};
    StrokeJoin stroke_join_{StrokeJoin::MITER};
    float stroke_miter_{4.0f};
    float text_size_{0.0f};
    TextAlign text_align_{TextAlign::LEFT};
    bool anti_alias_{false};
    bool dither_{false};
    bool filter_bitmap_{false};
};

} // namespace android::graphics
