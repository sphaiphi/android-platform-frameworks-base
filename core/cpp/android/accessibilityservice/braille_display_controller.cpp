// braille_display_controller.cpp
import braille_display_interfaces;
import ndk_executor; // Assumes the provided executor module

import <memory>;
import <mutex>;
import <stdexcept>;
import <variant>;
import <iostream>; // For mock implementation logging

// MOCK: In a real implementation, this would interact with OS-level APIs.
namespace mock_hid_driver {
    using namespace accessibility;

    auto open_connection(const Device& device) -> std::expected<HidData, ConnectError> {
        // Simulate a connection delay and potential failure.
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
            // Return a dummy HID descriptor
            return HidData{0x05, 0x01, 0x09, 0x06, 0xA1, 0x01, 0x05, 0x07};
        }, device);
    }
} // namespace mock_hid_driver


export class BrailleDisplayControllerImpl final : public accessibility::BrailleDisplayController {
private:
    // FSM states for type-safe state management
    struct StateDisconnected {};
    struct StateConnecting { accessibility::Device pending_device; };
    struct StateConnected { accessibility::Device connected_device; };

    using State = std::variant<StateDisconnected, StateConnecting, StateConnected>;

public:
    explicit BrailleDisplayControllerImpl(std::shared_ptr<ndk::IThreadExecutor> executor)
        : executor_{std::move(executor)} {
        if (!executor_) {
            throw std::invalid_argument("Executor cannot be null.");
        }
    }

    ~BrailleDisplayControllerImpl() final {
        // Ensure disconnection on destruction (RAII)
        disconnect();
    }

    // Rule of 5: Disable copy/move, as this class manages a unique connection.
    BrailleDisplayControllerImpl(const BrailleDisplayControllerImpl&) = delete;
    auto operator=(const BrailleDisplayControllerImpl&) -> BrailleDisplayControllerImpl& = delete;
    BrailleDisplayControllerImpl(BrailleDisplayControllerImpl&&) = delete;
    auto operator=(BrailleDisplayControllerImpl&&) -> BrailleDisplayControllerImpl& = delete;

    [[nodiscard]] auto connect(accessibility::Device device, accessibility::BrailleDisplayCallback* callback)
        -> std::expected<void, accessibility::ConnectError> final {
        
        std::lock_guard lock(state_mutex_);
        if (!std::holds_alternative<StateDisconnected>(state_)) {
            return std::unexpected(accessibility::ConnectError::already_connected);
        }

        // Transition to connecting state
        state_ = StateConnecting{device};
        callback_ = callback; // Store non-owning pointer

        // Post the blocking connection logic to the background thread.
        executor_->post([this, device]() {
            // This lambda runs on the executor's thread.
            auto result = mock_hid_driver::open_connection(device);

            // Post the result handling back to the executor to ensure sequential state changes.
            executor_->post([this, result = std::move(result)]() {
                handle_connection_result(result);
            });
        });

        return {}; // Success
    }

    void write(const accessibility::HidData& buffer) final {
        std::shared_lock lock(state_mutex_);
        if (!std::holds_alternative<StateConnected>(state_)) {
            throw std::logic_error("Cannot write: Not connected.");
        }
        
        // "Fire and forget" write operation on the background thread.
        executor_->post([buffer, dev = std::get<StateConnected>(state_).connected_device]() {
            // This runs on the executor's thread
            std::cout << "Mock driver: Writing " << buffer.size() << " bytes.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate write
        });
    }

    void disconnect() final {
        executor_->post([this]() {
            std::lock_guard lock(state_mutex_);
            if (std::holds_alternative<StateDisconnected>(state_)) {
                return; // Already disconnected
            }
            
            // Immediately transition state and notify.
            state_ = StateDisconnected{};
            if(callback_) {
                callback_->on_disconnected();
                callback_ = nullptr; // Clear pointer after final use
            }
            std::cout << "Controller: Disconnected.\n";
        });
    }

    [[nodiscard]] auto is_connected() const -> bool final {
        std::shared_lock lock(state_mutex_);
        return std::holds_alternative<StateConnected>(state_);
    }

private:
    void handle_connection_result(const std::expected<accessibility::HidData, accessibility::ConnectError>& result) {
        std::lock_guard lock(state_mutex_);
        
        // Only proceed if we are still in the 'Connecting' state.
        if (!std::holds_alternative<StateConnecting>(state_)) {
             return; // State changed (e.g., disconnected before connection completed)
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

    // SAFETY ✓ Lifetime: RAII/smart pointers manage resource lifetime.
    std::shared_ptr<ndk::IThreadExecutor> executor_;

    // SAFETY ✓ Lifetime: Raw pointer assumes callback outlives this object.
    // This is documented in the interface header.
    accessibility::BrailleDisplayCallback* callback_{nullptr};
    
    // SAFETY ✓ Init: All members are initialized in the constructor.
    mutable std::shared_mutex state_mutex_{};
    State state_{StateDisconnected{}};
};