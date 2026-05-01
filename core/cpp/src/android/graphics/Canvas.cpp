#include <android/graphics/Canvas.h>
#include <android/graphics/Paint.h>
#include <android/graphics/Path.h>

namespace android::graphics {

Canvas::Canvas(int32_t width, int32_t height)
    : mWidth(width), mHeight(height), mSaveCount(1) {}

int32_t Canvas::width() const { return mWidth; }
int32_t Canvas::height() const { return mHeight; }

const std::vector<Canvas::Command>& Canvas::get_commands() const { return mCommands; }

void Canvas::drawRect(float left, float top, float right, float bottom, const Paint&) {
    mCommands.emplace_back(CmdDrawRect{left, top, right, bottom});
}

void Canvas::drawCircle(float cx, float cy, float radius, const Paint&) {
    mCommands.emplace_back(CmdDrawCircle{cx, cy, radius});
}

void Canvas::drawLine(float x0, float y0, float x1, float y1, const Paint&) {
    mCommands.emplace_back(CmdDrawLine{x0, y0, x1, y1});
}

void Canvas::drawPath(const Path& path, const Paint&) {
    mCommands.emplace_back(CmdDrawPath{path});
}

void Canvas::drawText(std::string_view text, float x, float y, const Paint&) {
    mCommands.emplace_back(CmdDrawText{std::string(text), x, y});
}

void Canvas::drawColor(uint32_t color) {
    mCommands.emplace_back(CmdDrawColor{color});
}

void Canvas::drawDrawable(Drawable*) {
    mCommands.emplace_back(CmdDrawDrawable{});
}

void Canvas::draw_rect(int32_t l, int32_t t, int32_t r, int32_t b) {
    mCommands.emplace_back(CmdDrawRect{static_cast<float>(l), static_cast<float>(t),
                                       static_cast<float>(r), static_cast<float>(b)});
}

int Canvas::save() {
    mSaveCount++;
    return mSaveCount;
}

void Canvas::restore() {
    if (mSaveCount > 1) {
        mSaveCount--;
    }
}

int Canvas::saveLayer(float, float, float, float, const Paint*) {
    mSaveCount++;
    return mSaveCount;
}

int Canvas::getSaveCount() const { return mSaveCount; }

void Canvas::translate(float dx, float dy) {
    mCommands.emplace_back(CmdTranslate{dx, dy});
}

void Canvas::scale(float sx, float sy) {
    mCommands.emplace_back(CmdScale{sx, sy});
}

void Canvas::rotate(float degrees) {
    mCommands.emplace_back(CmdRotate{degrees});
}

void Canvas::clipRect(float left, float top, float right, float bottom) {
    mCommands.emplace_back(CmdClipRect{left, top, right, bottom});
}

void Canvas::clipPath(const Path& path) {
    mCommands.emplace_back(CmdClipPath{path});
}

} // namespace android::graphics
