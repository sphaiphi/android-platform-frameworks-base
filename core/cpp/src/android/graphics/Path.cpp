#include <android/graphics/Path.h>
#include <limits>

namespace android::graphics {

void Path::moveTo(float x, float y) {
    mElements.emplace_back(MoveTo{x, y});
}

void Path::lineTo(float x, float y) {
    mElements.emplace_back(LineTo{x, y});
}

void Path::close() {
    mElements.emplace_back(ClosePath{});
}

void Path::reset() {
    mElements.clear();
}

void Path::rewind() {
    mElements.clear();
}

void Path::addRect(float left, float top, float right, float bottom) {
    mElements.emplace_back(AddRect{left, top, right, bottom});
}

void Path::addCircle(float cx, float cy, float radius) {
    mElements.emplace_back(AddCircle{cx, cy, radius});
}

void Path::addOval(float left, float top, float right, float bottom) {
    mElements.emplace_back(AddOval{left, top, right, bottom});
}

void Path::addArc(float left, float top, float right, float bottom, float startAngle, float sweepAngle) {
    mElements.emplace_back(ArcTo{left, top, right, bottom, startAngle, sweepAngle, true});
}

void Path::arcTo(float left, float top, float right, float bottom, float startAngle, float sweepAngle, bool forceMoveTo) {
    mElements.emplace_back(ArcTo{left, top, right, bottom, startAngle, sweepAngle, forceMoveTo});
}

void Path::set_fill_type(FillType ft) {
    mFillType = ft;
}

Path::FillType Path::get_fill_type() const {
    return mFillType;
}

bool Path::is_empty() const {
    return mElements.empty();
}

Rect Path::computeBounds() const {
    if (mElements.empty()) {
        return Rect{0, 0, 0, 0};
    }

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();

    auto update = [&minX, &minY, &maxX, &maxY](float x, float y) {
        if (x < minX) minX = x;
        if (y < minY) minY = y;
        if (x > maxX) maxX = x;
        if (y > maxY) maxY = y;
    };

    for (const auto& elem : mElements) {
        std::visit([&](auto& e) {
            using T = std::decay_t<decltype(e)>;
            if constexpr (std::is_same_v<T, MoveTo> || std::is_same_v<T, LineTo>) {
                update(e.x, e.y);
            } else if constexpr (std::is_same_v<T, AddRect> || std::is_same_v<T, AddOval> || std::is_same_v<T, ArcTo>) {
                update(e.left, e.top);
                update(e.right, e.bottom);
            } else if constexpr (std::is_same_v<T, AddCircle>) {
                update(e.cx - e.radius, e.cy - e.radius);
                update(e.cx + e.radius, e.cy + e.radius);
            }
            // ClosePath has no coordinates
        }, elem);
    }

    return Rect{
        static_cast<int32_t>(minX),
        static_cast<int32_t>(minY),
        static_cast<int32_t>(maxX),
        static_cast<int32_t>(maxY)
    };
}

} // namespace android::graphics
