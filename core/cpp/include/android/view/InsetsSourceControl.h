#pragma once

#include <android/graphics/Insets.h>
#include <android/graphics/Point.h>
#include <cstdint>
#include <memory>
#include <optional>

namespace android::view {

class Surface;

/**
 * Controls how the window manager handles a particular insets source.
 * Built via the builder pattern to match Android API ergonomics.
 */
class InsetsSourceControl {
public:
    class Builder {
    public:
        Builder(int32_t id, int32_t type);

        Builder& set_leash(std::shared_ptr<Surface> leash);
        Builder& set_surface_position(android::graphics::Point position);
        Builder& set_insets_hint(android::graphics::Insets hint);
        Builder& set_initially_visible(bool visible);
        Builder& set_skip_animation_once(bool skip);
        [[nodiscard]] std::shared_ptr<InsetsSourceControl> build() &&;

    private:
        int32_t id_;
        int32_t type_;
        std::shared_ptr<Surface> leash_;
        android::graphics::Point surface_position_;
        std::optional<android::graphics::Insets> insets_hint_;
        bool initially_visible_{false};
        bool skip_animation_once_{false};
    };

    static Builder builder(int32_t id, int32_t type);

    int32_t id{0};
    int32_t type{0};
    std::shared_ptr<Surface> leash;
    bool initially_visible{false};
    android::graphics::Point surface_position;
    std::optional<android::graphics::Insets> insets_hint;
    bool skip_animation_once{false};

public:
    InsetsSourceControl() = default;
};

} // namespace android::view
