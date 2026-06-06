#pragma once

#include <memory>

namespace android::view {

/**
 * Interpolator — defines the rate-of-change curve for animations.
 *
 * The interpolation input is normalized to [0, 1] representing the
 * fraction of elapsed animation time. The output must also be in [0, 1].
 *
 * Subclasses implement different curves (linear, accelerate, decelerate, etc.).
 * The interface clamps output to [0, 1] regardless of the subclass implementation.
 */
class Interpolator {
public:
    virtual ~Interpolator() = default;

    /**
     * Compute the interpolated value for the given input fraction.
     *
     * @param input  Normalized time fraction in [0, 1].
     * @return       Interpolated value clamped to [0, 1].
     */
    virtual float getInterpolation(float input) = 0;
};

/**
 * LinearInterpolator — constant rate of change (identity curve).
 */
class LinearInterpolator : public Interpolator {
public:
    float getInterpolation(float input) override;
};

/**
 * AccelerateDecelerateInterpolator — accelerates before decelerating (double-alpha curve).
 */
class AccelerateDecelerateInterpolator : public Interpolator {
public:
    float getInterpolation(float input) override;
};

/**
 * DecelerateInterpolator — decelerates from the start (single-alpha curve).
 */
class DecelerateInterpolator : public Interpolator {
public:
    float getInterpolation(float input) override;
};

} // namespace android::view
