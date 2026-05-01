#pragma once

#include <android/graphics/Drawable.h>
#include <android/graphics/Color.h>

namespace android::graphics {

class Canvas;
class Paint;

/**
 * ColorDrawable draws a solid color rectangle within its bounds.
 */
class ColorDrawable : public Drawable {
public:
    explicit ColorDrawable(uint32_t color = Color::BLACK);

    void draw(Canvas* canvas) override;
    [[nodiscard]] uint32_t getColor() const;
    [[nodiscard]] int32_t getIntrinsicWidth() const override { return 0; }
    [[nodiscard]] int32_t getIntrinsicHeight() const override { return 0; }

private:
    uint32_t mColor;
};

} // namespace android::graphics
