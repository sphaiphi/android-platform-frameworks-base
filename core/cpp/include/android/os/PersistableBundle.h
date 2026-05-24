#pragma once

#include <android/os/Bundle.h>

namespace android::os {

/**
 * A mapping from String keys to values of various types.
 * Skeleton implementation for ActivityClient parity.
 */
class PersistableBundle : public Bundle {
public:
    using Bundle::Bundle;
};

} // namespace android::os
