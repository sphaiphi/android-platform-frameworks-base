#pragma once

#include <memory>

namespace android::hardware::input {

class IInputManager {
public:
    virtual ~IInputManager() = default;
};

} // namespace android::hardware::input
