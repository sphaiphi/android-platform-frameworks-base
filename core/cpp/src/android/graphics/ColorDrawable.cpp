#include <android/graphics/ColorDrawable.h>
#include <android/graphics/Canvas.h>
#include <android/graphics/Paint.h>

namespace android::graphics {

ColorDrawable::ColorDrawable(uint32_t color) : mColor(color) {}

void ColorDrawable::draw(Canvas* canvas) {
    auto bounds = getBounds();
    Paint paint;
    uint32_t c = mColor;
    // Apply alpha on top of color alpha
    uint32_t combinedAlpha = static_cast<uint8_t>(Color::getAlpha(c) * getAlpha() / 255);
    paint.set_color(Color::setColorAlpha(c, combinedAlpha));
    canvas->drawRect(static_cast<float>(bounds.left),
                     static_cast<float>(bounds.top),
                     static_cast<float>(bounds.right),
                     static_cast<float>(bounds.bottom), paint);
}

uint32_t ColorDrawable::getColor() const {
    return mColor;
}

} // namespace android::graphics
