#include <android/view/Interpolator.h>
#include <cmath>

namespace android::view {

// Clamp value to [0, 1]
static inline float clamp01(float v) {
    return v < 0.0f ? 0.0f : (v > 1.0f ? 1.0f : v);
}

// ---------------------------------------------------------------------------
// LinearInterpolator — identity curve.
// ---------------------------------------------------------------------------

float LinearInterpolator::getInterpolation(float input) {
    return clamp01(input);
}

// ---------------------------------------------------------------------------
// AccelerateDecelerateInterpolator — double-alpha curve.
// cos((input + 1) * PI) / 2 + 0.5
// ---------------------------------------------------------------------------

float AccelerateDecelerateInterpolator::getInterpolation(float input) {
    return clamp01(
        static_cast<float>(std::cos((input + 1.0f) * M_PI) * -0.5f + 0.5f)
    );
}

// ---------------------------------------------------------------------------
// DecelerateInterpolator — single-alpha curve.
// 1 - (1 - input)^2
// ---------------------------------------------------------------------------

float DecelerateInterpolator::getInterpolation(float input) {
    float u = 1.0f - input;
    return clamp01(1.0f - u * u);
}

} // namespace android::view
