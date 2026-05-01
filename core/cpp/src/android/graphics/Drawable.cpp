#include <android/graphics/Drawable.h>

namespace android::graphics {

void Drawable::setBounds(int32_t left, int32_t top, int32_t right, int32_t bottom) {
    mBounds = {left, top, right, bottom};
}

Rect Drawable::getBounds() const {
    return mBounds;
}

void Drawable::setBoundsInPlace(const Rect& bounds) {
    mBounds = bounds;
}

int32_t Drawable::getIntrinsicWidth() const { return -1; }
int32_t Drawable::getIntrinsicHeight() const { return -1; }

void Drawable::setAlpha(uint8_t alpha) { mAlpha = alpha; }
uint8_t Drawable::getAlpha() const { return mAlpha; }

void Drawable::setColorFilter(std::shared_ptr<void> filter) { mColorFilter = std::move(filter); }
std::shared_ptr<void> Drawable::getColorFilter() const { return mColorFilter; }

void Drawable::setState(const std::vector<int32_t>& state) {
    mState = std::make_shared<std::vector<int32_t>>(state);
}

std::shared_ptr<const std::vector<int32_t>> Drawable::getState() const {
    return mState;
}

int32_t Drawable::getMinimumHeight() const { return 0; }
int32_t Drawable::getMinimumWidth() const { return 0; }

void Drawable::setLevel(int32_t level) { mLevel = level; }
int32_t Drawable::getLevel() const { return mLevel; }

} // namespace android::graphics
