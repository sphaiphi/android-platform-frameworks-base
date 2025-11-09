// braille_impl.cpp
module braille;

import std.core;
import std.threading; // For mutex, jthread, atomic, condition_variable
import <iostream>;
import <variant>;
import <chrono>;
import <memory>;

// The implementation is within the module's namespace.
namespace braille::hid {

// This class is a PRIVATE implementation detail of the 'braille' module.
// It is not exported and cannot be named directly by client code.
class MockBrailleDisplayController final : public BrailleDisplayController {
    static constexpr std::size_t MAX_IPC_BUFFER_SIZE = 8192;
    const std::vector<std::uint8_t> mock_hid_descriptor_ = {0x05, 0x28, 0x09, 0x01};

    std::mutex mutex_;
    std::atomic<bool> is_connected_{false};
    BrailleDisplayCallback* callback_ = nullptr;
    Executor executor_;
    std::optional<std::jthread> io_thread_;
    std::variant<std::monostate, BluetoothDeviceHandle, UsbDeviceHandle> connecting_device_;

    template<typename F>
    void post_callback(F&& func) {
        if (executor_) {
            executor_(std::forward<F>(func));
        } else {
            func();
        }
    }

    void connect_impl(auto /*device_handle*/, BrailleDisplayCallback& cb, Executor exec) {
        std::scoped_lock lock{mutex_};
        if (is_connected_ || io_thread_.has_value()) {
            throw std::logic_error("Connection already in progress or established.");
        }
        callback_ = &cb;
        executor_ = std::move(exec);

        io_thread_.emplace([this](std::stop_token st) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if (st.stop_requested()) return;

            if (auto* bt_dev = std::get_if<BluetoothDeviceHandle>(&connecting_device_)) {
                 if (bt_dev->id == "bad-device") {
                    post_callback([this]{ callback_->on_connection_failed(ErrorCode::display_not_found); });
                    std::scoped_lock cleanup_lock{mutex_};
                    io_thread_.reset();
                    callback_ = nullptr;
                    return;
                 }
            }

            is_connected_ = true;
            post_callback([this]{ callback_->on_connected(mock_hid_descriptor_); });

            while (!st.stop_requested()) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                 if (st.stop_requested()) break;
                const std::vector<uint8_t> input_data = {0x01, 0x02};
                post_callback([this, input_data]{ callback_->on_input(input_data); });
            }
        });
    }

public:
    ~MockBrailleDisplayController() override {
        disconnect();
    }

    void connect(const BluetoothDeviceHandle& device, BrailleDisplayCallback& callback, Executor executor) override {
        connecting_device_ = device;
        connect_impl(device, callback, std::move(executor));
    }

    void connect(const UsbDeviceHandle& device, BrailleDisplayCallback& callback, Executor executor) override {
        connecting_device_ = device;
        connect_impl(device, callback, std::move(executor));
    }

    [[nodiscard]] auto is_connected() const noexcept -> bool override {
        return is_connected_;
    }

    void write(std::span<const std::uint8_t> buffer) override {
        if (!is_connected_) {
            throw IOError("Not connected to a Braille display.");
        }
        if (buffer.size() > MAX_IPC_BUFFER_SIZE) {
            throw std::length_error("Buffer size exceeds maximum IPC limit.");
        }
        std::scoped_lock lock{mutex_};
        std::cout << "[Controller] Writing " << buffer.size() << " bytes." << std::endl;
    }

    void disconnect() noexcept override {
        if (io_thread_.has_value() && io_thread_->joinable()) {
             io_thread_->request_stop();
             io_thread_.reset();
        }
        if (is_connected_.exchange(false)) {
            post_callback([this] {
                 if(callback_) callback_->on_disconnected();
            });
        }
        std::scoped_lock lock{mutex_};
        callback_ = nullptr;
    }
};

// Implementation of the exported factory function.
auto create_mock_controller() -> std::unique_ptr<BrailleDisplayController> {
    return std::make_unique<MockBrailleDisplayController>();
}

} // namespace braille::hid