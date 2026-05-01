#pragma once

#include <android/graphics/Rect.h>
#include <vector>
#include <array>
#include <variant>
#include <cmath>

namespace android::graphics {

/**
 * Path holds a collection of geometric shapes and drawing commands.
 */
class Path {
public:
    enum class FillType {
        WINDING = 0,
        EVEN_ODD = 1,
        INVERSE_WINDING = 2,
        INVERSE_EVEN_ODD = 3
    };

    struct MoveTo { float x; float y; };
    struct LineTo { float x; float y; };
    struct ClosePath {};
    struct AddRect { float left; float top; float right; float bottom; };
    struct AddCircle { float cx; float cy; float radius; };
    struct AddOval { float left; float top; float right; float bottom; };
    struct ArcTo { float left; float top; float right; float bottom; float startAngle; float sweepAngle; bool forceMoveTo; };

    using Element = std::variant<MoveTo, LineTo, ClosePath, AddRect, AddCircle, AddOval, ArcTo>;

    Path() = default;
    Path(const Path&) = default;
    Path& operator=(const Path&) = default;

    // Point operations
    void moveTo(float x, float y);
    void lineTo(float x, float y);
    void close();
    void reset();
    void rewind();

    // Shape operations
    void addRect(float left, float top, float right, float bottom);
    void addCircle(float cx, float cy, float radius);
    void addOval(float left, float top, float right, float bottom);
    void addArc(float left, float top, float right, float bottom, float startAngle, float sweepAngle);
    void arcTo(float left, float top, float right, float bottom, float startAngle, float sweepAngle, bool forceMoveTo);

    // Fill type
    void set_fill_type(FillType ft);
    [[nodiscard]] FillType get_fill_type() const;

    // Query
    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] Rect computeBounds() const;

private:
    std::vector<Element> mElements;
    FillType mFillType{FillType::WINDING};
};

} // namespace android::graphics
