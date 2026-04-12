#pragma once

#include <memory>

namespace android::view {

class IWindowSession {
public:
    virtual ~IWindowSession() = default;
};

} // namespace android::view
