#pragma once

#include <android/content/ContextWrapper.h>

namespace android::view {

class ContextThemeWrapper : public android::content::ContextWrapper {
public:
    using android::content::ContextWrapper::ContextWrapper;
    virtual ~ContextThemeWrapper() = default;

    auto set_theme(int res_id) -> void {
        theme_resource_ = res_id;
    }

    [[nodiscard]] auto get_theme_res_id() const noexcept -> int {
        return theme_resource_;
    }

private:
    int theme_resource_{0};
};

} // namespace android::view
