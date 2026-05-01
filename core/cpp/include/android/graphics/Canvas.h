#pragma once

#include <android/graphics/Color.h>
#include <android/graphics/Path.h>
#include <vector>
#include <array>
#include <variant>
#include <memory>
#include <string>
#include <cstdint>

namespace android::graphics {

class Paint;
class Drawable;

/**
 * Canvas holds draw commands and records them for later replay.
 * Commands are stored as a list of variants for inspection and testing.
 */
class Canvas {
public:
    // --- Draw command types ---
    struct CmdDrawRect { float left; float top; float right; float bottom; };
    struct CmdDrawCircle { float cx; float cy; float radius; };
    struct CmdDrawLine { float x0; float y0; float x1; float y1; };
    struct CmdDrawPath { Path path; };
    struct CmdDrawText { std::string text; float x; float y; };
    struct CmdDrawColor { uint32_t color; };
    struct CmdDrawDrawable {};

    // --- Transform commands ---
    struct CmdTranslate { float dx; float dy; };
    struct CmdScale { float sx; float sy; };
    struct CmdRotate { float degrees; };

    // --- Clip commands ---
    struct CmdClipRect { float left; float top; float right; float bottom; };
    struct CmdClipPath { Path path; };

    using Command = std::variant<
        CmdDrawRect, CmdDrawCircle, CmdDrawLine, CmdDrawPath,
        CmdDrawText, CmdDrawColor, CmdDrawDrawable,
        CmdTranslate, CmdScale, CmdRotate,
        CmdClipRect, CmdClipPath
    >;

    explicit Canvas(int32_t width, int32_t height);
    virtual ~Canvas() = default;

    // --- Query ---
    [[nodiscard]] int32_t width() const;
    [[nodiscard]] int32_t height() const;
    [[nodiscard]] const std::vector<Command>& get_commands() const;

    // --- Drawing ---
    virtual void drawRect(float left, float top, float right, float bottom, const Paint& paint);
    virtual void drawCircle(float cx, float cy, float radius, const Paint& paint);
    virtual void drawLine(float x0, float y0, float x1, float y1, const Paint& paint);
    virtual void drawPath(const Path& path, const Paint& paint);
    virtual void drawText(std::string_view text, float x, float y, const Paint& paint);
    virtual void drawColor(uint32_t color);
    virtual void drawDrawable(Drawable* drawable);

    // Backward compat with old draw_rect signature
    virtual void draw_rect(int32_t l, int32_t t, int32_t r, int32_t b);

    // --- State management ---
    virtual int save();
    virtual void restore();
    virtual int saveLayer(float left, float top, float right, float bottom, const Paint* paint);
    [[nodiscard]] int getSaveCount() const;

    // --- Transform ---
    virtual void translate(float dx, float dy);
    virtual void scale(float sx, float sy);
    virtual void rotate(float degrees);

    // --- Clip ---
    virtual void clipRect(float left, float top, float right, float bottom);
    virtual void clipPath(const Path& path);

private:
    int32_t mWidth;
    int32_t mHeight;
    std::vector<Command> mCommands;
    int mSaveCount;
};

} // namespace android::graphics
