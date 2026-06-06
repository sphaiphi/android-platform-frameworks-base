#include <android/view/ViewPropertyAnimator.h>
#include <android/view/Choreographer.h>
#include <android/view/Interpolator.h>

#include <algorithm>
#include <stdexcept>

namespace android::view {

// Default interpolator type
using DefaultInterpolator = LinearInterpolator;

// ============================================================================
// Constructor
// ============================================================================

ViewPropertyAnimator::ViewPropertyAnimator(std::weak_ptr<View> view)
    : m_view_(std::move(view))
    , m_interpolator_(std::make_shared<DefaultInterpolator>()) {
}

// ============================================================================
// Fluent property methods — animate to absolute value
// ============================================================================

auto ViewPropertyAnimator::alpha(float value) -> ViewPropertyAnimator& {
    m_pending_.push_back({ALPHA, value, false});
    return *this;
}

auto ViewPropertyAnimator::alpha_by(float delta) -> ViewPropertyAnimator& {
    m_pending_.push_back({ALPHA, delta, true});
    return *this;
}

auto ViewPropertyAnimator::translation_x(float value) -> ViewPropertyAnimator& {
    m_pending_.push_back({TRANSLATION_X, value, false});
    return *this;
}

auto ViewPropertyAnimator::translation_x_by(float delta) -> ViewPropertyAnimator& {
    m_pending_.push_back({TRANSLATION_X, delta, true});
    return *this;
}

auto ViewPropertyAnimator::translation_y(float value) -> ViewPropertyAnimator& {
    m_pending_.push_back({TRANSLATION_Y, value, false});
    return *this;
}

auto ViewPropertyAnimator::translation_y_by(float delta) -> ViewPropertyAnimator& {
    m_pending_.push_back({TRANSLATION_Y, delta, true});
    return *this;
}

auto ViewPropertyAnimator::rotation(float value) -> ViewPropertyAnimator& {
    m_pending_.push_back({ROTATION, value, false});
    return *this;
}

auto ViewPropertyAnimator::rotation_by(float delta) -> ViewPropertyAnimator& {
    m_pending_.push_back({ROTATION, delta, true});
    return *this;
}

auto ViewPropertyAnimator::scale_x(float value) -> ViewPropertyAnimator& {
    m_pending_.push_back({SCALE_X, value, false});
    return *this;
}

auto ViewPropertyAnimator::scale_x_by(float delta) -> ViewPropertyAnimator& {
    m_pending_.push_back({SCALE_X, delta, true});
    return *this;
}

auto ViewPropertyAnimator::scale_y(float value) -> ViewPropertyAnimator& {
    m_pending_.push_back({SCALE_Y, value, false});
    return *this;
}

auto ViewPropertyAnimator::scale_y_by(float delta) -> ViewPropertyAnimator& {
    m_pending_.push_back({SCALE_Y, delta, true});
    return *this;
}

auto ViewPropertyAnimator::x(float value) -> ViewPropertyAnimator& {
    // x = left + translationX, so delta = value - current_x
    if (auto view = m_view_.lock()) {
        translation_x_by(value - view->get_x());
    } else {
        // Fallback: queue as translation_x_by(0) — will be resolved on first frame
        translation_x_by(value);
    }
    return *this;
}

auto ViewPropertyAnimator::x_by(float delta) -> ViewPropertyAnimator& {
    translation_x_by(delta);
    return *this;
}

auto ViewPropertyAnimator::y(float value) -> ViewPropertyAnimator& {
    // y = top + translationY, so delta = value - current_y
    if (auto view = m_view_.lock()) {
        translation_y_by(value - view->get_y());
    } else {
        translation_y_by(value);
    }
    return *this;
}

auto ViewPropertyAnimator::y_by(float delta) -> ViewPropertyAnimator& {
    translation_y_by(delta);
    return *this;
}

// ============================================================================
// Configuration methods
// ============================================================================

auto ViewPropertyAnimator::set_duration(int64_t ms) -> ViewPropertyAnimator& {
    if (ms < 0) {
        throw std::invalid_argument("Animators cannot have negative duration: " + std::to_string(ms));
    }
    m_duration_ms_ = ms;
    return *this;
}

auto ViewPropertyAnimator::set_start_delay(int64_t ms) -> ViewPropertyAnimator& {
    m_start_delay_ms_ = ms;
    return *this;
}

auto ViewPropertyAnimator::set_interpolator(std::shared_ptr<Interpolator> interpolator) -> ViewPropertyAnimator& {
    m_interpolator_ = std::move(interpolator);
    return *this;
}

auto ViewPropertyAnimator::with_start_action(std::function<void()> action) -> ViewPropertyAnimator& {
    m_start_action_ = std::move(action);
    return *this;
}

auto ViewPropertyAnimator::with_end_action(std::function<void()> action) -> ViewPropertyAnimator& {
    m_end_action_ = std::move(action);
    return *this;
}

// ============================================================================
// Lifecycle methods
// ============================================================================

void ViewPropertyAnimator::start() {
    if (m_state_ == State::CANCELED) {
        // Reset from canceled state
        m_state_ = State::PENDING;
        m_pending_.clear();
    }

    if (m_pending_.empty()) {
        return;
    }

    // Fire start action
    if (m_start_action_) {
        m_start_action_();
    }

    m_state_ = State::RUNNING;
    m_start_time_nanos_ = Choreographer::system_time_nanos();

    // Capture shared_ptr to keep VPA alive during animation
    auto self = shared_from_this();

    // Post Choreographer callback with start delay
    auto choreo = Choreographer::get_main_instance();
    if (choreo) {
        auto cb = [self](int64_t /*frameTimeNanos*/) {
            self->on_frame(Choreographer::system_time_nanos());
        };
        choreo->post_frame_callback_delayed(std::move(cb), m_start_delay_ms_);
    } else {
        // Fallback: no Choreographer available, execute immediately
        on_frame(Choreographer::system_time_nanos());
    }
}

void ViewPropertyAnimator::cancel() {
    m_pending_.clear();
    m_state_ = State::CANCELED;
    m_start_action_ = nullptr;
    m_end_action_ = nullptr;
}

// ============================================================================
// Query methods
// ============================================================================

auto ViewPropertyAnimator::is_running() const -> bool {
    return m_state_ == State::RUNNING;
}

auto ViewPropertyAnimator::is_pending() const -> bool {
    return m_state_ == State::PENDING && !m_pending_.empty();
}

auto ViewPropertyAnimator::get_duration() const -> int64_t {
    return m_duration_ms_;
}

auto ViewPropertyAnimator::get_view() const -> std::shared_ptr<View> {
    return m_view_.lock();
}

// ============================================================================
// Internal animation engine
// ============================================================================

void ViewPropertyAnimator::on_frame(int64_t /*frame_time_nanos*/) {
    auto view = m_view_.lock();
    if (!view || m_state_ != State::RUNNING) {
        return;
    }

    // Compute interpolation fraction from elapsed time
    float fraction;
    if (m_duration_ms_ == 0) {
        fraction = 1.0f;
    } else {
        int64_t elapsed_ms = static_cast<int64_t>(
            (Choreographer::system_time_nanos() - m_start_time_nanos_) / 1000000LL
        );
        fraction = std::min(1.0f, static_cast<float>(elapsed_ms) / static_cast<float>(m_duration_ms_));
    }

    // Apply interpolator
    fraction = m_interpolator_->getInterpolation(fraction);

    // Apply interpolated values to the View
    apply_pending_values();

    // Animation complete
    if (fraction >= 1.0f) {
        m_state_ = State::CANCELED;
        if (m_end_action_) {
            m_end_action_();
        }
    }
}

#ifdef HOST_BUILD
void ViewPropertyAnimator::test_advance_time(int64_t ms) {
    // Advance the perceived start time by ms, making on_frame think time has passed
    m_start_time_nanos_ -= ms * 1000000LL;
}
#endif

void ViewPropertyAnimator::apply_pending_values() {
    auto view = m_view_.lock();
    if (!view) return;

    for (auto& nv : m_pending_) {
        float target;
        if (nv.is_delta) {
            // Compute start value from current View state
            float current = 0.0f;
            switch (nv.property) {
            case TRANSLATION_X: current = view->get_translation_x(); break;
            case TRANSLATION_Y: current = view->get_translation_y(); break;
            case ALPHA:         current = view->get_alpha(); break;
            case ROTATION:      current = view->get_rotation(); break;
            case SCALE_X:       current = view->get_scale_x(); break;
            case SCALE_Y:       current = view->get_scale_y(); break;
            }
            target = current + nv.value;
        } else {
            target = nv.value;
        }

        // Apply to View
        switch (nv.property) {
        case TRANSLATION_X: view->set_translation_x(target); break;
        case TRANSLATION_Y: view->set_translation_y(target); break;
        case ALPHA:         view->set_alpha(target); break;
        case ROTATION:      view->set_rotation(target); break;
        case SCALE_X:       view->set_scale_x(target); break;
        case SCALE_Y:       view->set_scale_y(target); break;
        }
    }

    // Invalidate the view to trigger redraw
    view->invalidate();
}

// ============================================================================
// View::animate() implementation
// ============================================================================

auto View::animate() -> std::shared_ptr<ViewPropertyAnimator> {
    return std::make_shared<ViewPropertyAnimator>(shared_from_this());
}

} // namespace android::view
