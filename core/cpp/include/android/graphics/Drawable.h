#pragma once

#include <android/graphics/Rect.h>
#include <vector>
#include <cstdint>
#include <memory>

namespace android::graphics {

class Canvas;

/**
 * Drawable is an abstract base class for objects that can draw themselves on a Canvas.
 */
class Drawable {
public:
    Drawable() = default;
    virtual ~Drawable() = default;

    // Drawing
    virtual void draw(Canvas* canvas) = 0;

    // Bounds
    virtual void setBounds(int32_t left, int32_t top, int32_t right, int32_t bottom);
    [[nodiscard]] virtual Rect getBounds() const;
    virtual void setBoundsInPlace(const Rect& bounds);

    // Intrinsic size
    [[nodiscard]] virtual int32_t getIntrinsicWidth() const;
    [[nodiscard]] virtual int32_t getIntrinsicHeight() const;

    // Alpha
    virtual void setAlpha(uint8_t alpha);
    [[nodiscard]] virtual uint8_t getAlpha() const;

    // Color filter (opaque handle for now)
    virtual void setColorFilter(std::shared_ptr<void> filter);
    [[nodiscard]] virtual std::shared_ptr<void> getColorFilter() const;

    // State (set of style state ints)
    virtual void setState(const std::vector<int32_t>& state);
    [[nodiscard]] virtual std::shared_ptr<const std::vector<int32_t>> getState() const;

    // Minimum dimensions
    [[nodiscard]] virtual int32_t getMinimumHeight() const;
    [[nodiscard]] virtual int32_t getMinimumWidth() const;

    // Level
    virtual void setLevel(int32_t level);
    [[nodiscard]] virtual int32_t getLevel() const;

private:
    Rect mBounds;
    uint8_t mAlpha{255};
    std::shared_ptr<void> mColorFilter;
    std::shared_ptr<const std::vector<int32_t>> mState{std::make_shared<std::vector<int32_t>>()};
    int32_t mLevel{0};
};

} // namespace android::graphics
