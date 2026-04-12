#pragma once

#include <android/graphics/Canvas.h>
#include <string>
#include <memory>

namespace android::graphics {

/**
 * RenderNode is used to build hardware-accelerated rendering hierarchies.
 * It stores a list of drawing commands (a "display list") that can be replayed.
 */
class RenderNode {
public:
    explicit RenderNode(const std::string& name) : name_(name) {}
    virtual ~RenderNode() = default;

    const std::string& get_name() const { return name_; }

    /**
     * Starts recording drawing commands into this RenderNode.
     * Returns a Canvas that can be used for recording.
     */
    virtual Canvas* begin_recording(int32_t width, int32_t height) = 0;

    /**
     * Ends recording and saves the drawing commands.
     */
    virtual void end_recording() = 0;

    /**
     * Returns true if the RenderNode has a display list (recorded commands).
     */
    virtual bool has_display_list() const = 0;

    // Transformation properties (simplified for now)
    void set_translation_x(float translation_x) { translation_x_ = translation_x; }
    void set_translation_y(float translation_y) { translation_y_ = translation_y; }
    float get_translation_x() const { return translation_x_; }
    float get_translation_y() const { return translation_y_; }

private:
    std::string name_;
    float translation_x_{0.0f};
    float translation_y_{0.0f};
};

} // namespace android::graphics
