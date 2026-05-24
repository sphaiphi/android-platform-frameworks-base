#include <android/graphics/Paint.h>

namespace android::graphics {

void Paint::set_style(Style style) { style_ = style; }
Paint::Style Paint::get_style() const { return style_; }

void Paint::set_color(uint32_t color) { color_ = color; }
uint32_t Paint::get_color() const { return color_; }

void Paint::set_alpha(uint8_t alpha) { alpha_ = alpha; }
uint8_t Paint::get_alpha() const { return alpha_; }

void Paint::set_stroke_width(float width) { stroke_width_ = width; }
float Paint::get_stroke_width() const { return stroke_width_; }

void Paint::set_stroke_cap(StrokeCap cap) { stroke_cap_ = cap; }
Paint::StrokeCap Paint::get_stroke_cap() const { return stroke_cap_; }

void Paint::set_stroke_join(StrokeJoin join) { stroke_join_ = join; }
Paint::StrokeJoin Paint::get_stroke_join() const { return stroke_join_; }

void Paint::set_stroke_miter(float miter) { stroke_miter_ = miter; }
float Paint::get_stroke_miter() const { return stroke_miter_; }

void Paint::set_text_size(float size) { text_size_ = size; }
float Paint::get_text_size() const { return text_size_; }

void Paint::set_text_align(TextAlign align) { text_align_ = align; }
Paint::TextAlign Paint::get_text_align() const { return text_align_; }

float Paint::measureText(std::string_view text) const {
    if (text.empty()) return 0.0f;
    // Approximation: monospace ~0.6em per character
    return static_cast<float>(text.size()) * text_size_ * 0.6f;
}

void Paint::set_anti_alias(bool enable) { anti_alias_ = enable; }
bool Paint::is_anti_alias() const { return anti_alias_; }

void Paint::set_dither(bool enable) { dither_ = enable; }
bool Paint::is_dither() const { return dither_; }

void Paint::set_filter_bitmap(bool enable) { filter_bitmap_ = enable; }
bool Paint::is_filter_bitmap() const { return filter_bitmap_; }

} // namespace android::graphics
