// accessibilityservice-magnification_controller.cppm
export module accessibilityservice:magnification_controller;

import :internal;
import :types;
import ndk_executor;

import <memory>;
import <mutex>;
import <vector>;
import <expected>;

export namespace accessibility {

class IMagnificationController {
public:
    virtual ~IMagnificationController() = default;

    virtual auto get_magnification_config(int display_id) 
        -> std::expected<MagnificationConfig, internal::IpcError> = 0;

    virtual auto set_magnification_config(int display_id, const MagnificationConfig& config, bool animate)
        -> std::expected<bool, internal::IpcError> = 0;

    virtual auto reset(int display_id, bool animate) -> std::expected<bool, internal::IpcError> = 0;

    virtual auto set_center(int display_id, float center_x, float center_y, bool animate) 
        -> std::expected<bool, internal::IpcError> = 0;

    virtual auto set_scale(int display_id, float scale, bool animate) 
        -> std::expected<bool, internal::IpcError> = 0;
};

class MagnificationControllerImpl final : public IMagnificationController {
public:
    explicit MagnificationControllerImpl(
        std::shared_ptr<internal::IAccessibilityServiceConnection> connection)
        : connection_(std::move(connection)) {}

    auto get_magnification_config(int display_id) 
        -> std::expected<MagnificationConfig, internal::IpcError> override {
        // Delegate to connection (mocked/internal)
        return std::unexpected(internal::IpcError::transaction_failed); 
    }

    auto set_magnification_config(int display_id, const MagnificationConfig& config, bool animate)
        -> std::expected<bool, internal::IpcError> override {
         return std::unexpected(internal::IpcError::transaction_failed); 
    }

    auto reset(int display_id, bool animate) -> std::expected<bool, internal::IpcError> override {
         return std::unexpected(internal::IpcError::transaction_failed);
    }

    auto set_center(int display_id, float center_x, float center_y, bool animate) 
        -> std::expected<bool, internal::IpcError> override {
        MagnificationConfig config;
        config.center_x = center_x;
        config.center_y = center_y;
        return set_magnification_config(display_id, config, animate);
    }

    auto set_scale(int display_id, float scale, bool animate) 
        -> std::expected<bool, internal::IpcError> override {
        MagnificationConfig config;
        config.scale = scale;
        return set_magnification_config(display_id, config, animate);
    }

private:
    std::shared_ptr<internal::IAccessibilityServiceConnection> connection_;
};

} // namespace accessibility