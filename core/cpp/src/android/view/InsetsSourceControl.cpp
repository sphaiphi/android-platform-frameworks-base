#include <android/view/InsetsSourceControl.h>

namespace android::view {

InsetsSourceControl::Builder::Builder(int32_t id, int32_t type)
    : id_(id), type_(type) {}

InsetsSourceControl::Builder& InsetsSourceControl::Builder::set_leash(std::shared_ptr<Surface> leash) {
    leash_ = std::move(leash);
    return *this;
}

InsetsSourceControl::Builder& InsetsSourceControl::Builder::set_surface_position(android::graphics::Point position) {
    surface_position_ = position;
    return *this;
}

InsetsSourceControl::Builder& InsetsSourceControl::Builder::set_insets_hint(android::graphics::Insets hint) {
    insets_hint_ = hint;
    return *this;
}

InsetsSourceControl::Builder& InsetsSourceControl::Builder::set_initially_visible(bool visible) {
    initially_visible_ = visible;
    return *this;
}

InsetsSourceControl::Builder& InsetsSourceControl::Builder::set_skip_animation_once(bool skip) {
    skip_animation_once_ = skip;
    return *this;
}

std::shared_ptr<InsetsSourceControl> InsetsSourceControl::Builder::build() && {
    auto control = std::make_shared<InsetsSourceControl>();
    control->id = id_;
    control->type = type_;
    control->leash = std::move(leash_);
    control->surface_position = surface_position_;
    control->insets_hint = std::move(insets_hint_);
    control->initially_visible = initially_visible_;
    control->skip_animation_once = skip_animation_once_;
    return control;
}

InsetsSourceControl::Builder InsetsSourceControl::builder(int32_t id, int32_t type) {
    return Builder{id, type};
}

} // namespace android::view
