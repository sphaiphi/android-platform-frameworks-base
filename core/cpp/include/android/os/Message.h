#pragma once

#include <functional>
#include <memory>

namespace android::os {

struct Message {
    int what;
    void* obj{nullptr};
    std::function<void()> callback;
};

} // namespace android::os
