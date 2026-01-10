// accessibilityservice-braille_display.cppm
export module accessibilityservice:braille_display;

import ndk_executor;

import <vector>;
import <cstdint>;
import <string>;
import <variant>;
import <expected>;
import <memory>;
import <mutex>;
import <stdexcept>;
import <iostream>;
import <shared_mutex>;
import <thread>;

export namespace accessibility {

struct BluetoothDevice {
    std::string address;
    auto operator<=>(const BluetoothDevice&) const = default;
};

struct UsbDevice {
    int vendor_id;
    int product_id;
    auto operator<=>(const UsbDevice&) const = default;
};

using Device = std::variant<BluetoothDevice, UsbDevice>;

using HidData = std::vector<uint8_t>;

export enum class ConnectError {
    cannot_access = 1 << 0,
    display_not_found = 1 << 1,
    already_connected = 1 << 2,
    feature_disabled = 1 << 3,
};

class BrailleDisplayCallback {
public:
    virtual ~BrailleDisplayCallback() = default;
    virtual void on_connected(const HidData& hid_descriptor) = 0;
    virtual void on_connection_failed(ConnectError error) = 0;
    virtual void on_input_received(const HidData& input) = 0;
    virtual void on_disconnected() = 0;
};

class BrailleDisplayController {
public:
    virtual ~BrailleDisplayController() = default;

    [[nodiscard]] virtual auto connect(Device device, BrailleDisplayCallback* callback)
        -> std::expected<void, ConnectError> = 0;

    virtual void write(const HidData& buffer) = 0;

    virtual void disconnect() = 0;

    [[nodiscard]] virtual auto is_connected() const -> bool = 0;
};

} // namespace accessibility

// --- Implementation ---

namespace mock_hid_driver {
    using namespace accessibility;

    auto open_connection(const Device& device) -> std::expected<HidData, ConnectError> {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        return std::visit([](const auto& dev) -> std::expected<HidData, ConnectError> {
            if constexpr (std::is_same_v<decltype(dev), const BluetoothDevice&>) {
                if (dev.address == "00:DE:AD:BE:EF:00") {
                    return std::unexpected(ConnectError::display_not_found);
                }
                std::cout << "Mock driver: Connected to Bluetooth device " << dev.address << "\n";
            } else if constexpr (std::is_same_v<decltype(dev), const UsbDevice&>) {
                 std::cout << "Mock driver: Connected to USB device " << dev.vendor_id << ":" << dev.product_id << "\n";
            }
            return HidData{0x05, 0x01, 0x09, 0x06, 0xA1, 0x01, 0x05, 0x07};
        }, device);
    }
} 

namespace accessibility {

class BrailleDisplayControllerImpl final : public BrailleDisplayController {
private:
    struct StateDisconnected {};
    struct StateConnecting { Device pending_device; };
    struct StateConnected { Device connected_device; };

    using State = std::variant<StateDisconnected, StateConnecting, StateConnected>;

public:
    explicit BrailleDisplayControllerImpl(std::shared_ptr<ndk::IThreadExecutor> executor)
        : executor_{std::move(executor)} {
        if (!executor_) {
            throw std::invalid_argument("Executor cannot be null.");
        }
    }

    ~BrailleDisplayControllerImpl() final {
        disconnect();
    }

    [[nodiscard]] auto connect(Device device, BrailleDisplayCallback* callback)
        -> std::expected<void, ConnectError> final {
    
        std::lock_guard lock(state_mutex_);
        if (!std::holds_alternative<StateDisconnected>(state_)) {
            return std::unexpected(ConnectError::already_connected);
        }

        state_ = StateConnecting{device};
        callback_ = callback;

        executor_->post([this, device]() {
            auto result = mock_hid_driver::open_connection(device);
            executor_->post([this, result = std::move(result)]() {
                handle_connection_result(result);
            });
        });

        return {};
    }

    void write(const HidData& buffer) final {
        std::shared_lock lock(state_mutex_);
        if (!std::holds_alternative<StateConnected>(state_)) {
            throw std::logic_error("Cannot write: Not connected.");
        }
    
        executor_->post([buffer, dev = std::get<StateConnected>(state_).connected_device]() {
            std::cout << "Mock driver: Writing " << buffer.size() << " bytes.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        });
    }

    void disconnect() final {
        executor_->post([this]() {
            std::lock_guard lock(state_mutex_);
            if (std::holds_alternative<StateDisconnected>(state_)) {
                return;
            }
            
            state_ = StateDisconnected{};
            if(callback_) {
                callback_->on_disconnected();
                callback_ = nullptr;
            }
            std::cout << "Controller: Disconnected.\n";
        });
    }

    [[nodiscard]] auto is_connected() const -> bool final {
        std::shared_lock lock(state_mutex_);
        return std::holds_alternative<StateConnected>(state_);
    }

private:
    void handle_connection_result(const std::expected<HidData, ConnectError>& result) {
        std::lock_guard lock(state_mutex_);
        
        if (!std::holds_alternative<StateConnecting>(state_)) { 
             return; 
        }

        if (result.has_value()) {
            state_ = StateConnected{std::get<StateConnecting>(state_).pending_device};
            if (callback_) {
                callback_->on_connected(result.value());
            }
        } else {
            state_ = StateDisconnected{};
            if (callback_) {
                callback_->on_connection_failed(result.error());
            }
        }
    }

    std::shared_ptr<ndk::IThreadExecutor> executor_;
    BrailleDisplayCallback* callback_{nullptr};
    
    mutable std::shared_mutex state_mutex_{};
    State state_{StateDisconnected{}};
};

} // namespace accessibility
