#pragma once

#include <cstdint>

namespace android {
namespace view {

class KeyEvent {
public:
    enum Action {
        ACTION_DOWN = 0,
        ACTION_UP = 1,
        ACTION_REPEAT = 2,
    };

    KeyEvent(Action action, int32_t key_code)
        : action_(action), key_code_(key_code),
          device_id_(0), source_(0x00000002), event_time_(0),
          repeat_count_(0), meta_state_(0) {}

    KeyEvent(Action action, int32_t key_code,
             int32_t device_id, uint32_t source,
             int64_t event_time,
             uint32_t repeat_count = 0, uint32_t meta_state = 0)
        : action_(action), key_code_(key_code),
          device_id_(device_id), source_(source),
          event_time_(event_time), repeat_count_(repeat_count), meta_state_(meta_state) {}

    auto get_action() const -> Action { return action_; }
    auto get_key_code() const -> int32_t { return key_code_; }
    auto get_device_id() const -> int32_t { return device_id_; }
    auto get_source() const -> uint32_t { return source_; }
    auto get_event_time() const -> int64_t { return event_time_; }
    auto get_repeat_count() const -> uint32_t { return repeat_count_; }
    auto get_meta_state() const -> uint32_t { return meta_state_; }

private:
    Action action_;
    int32_t key_code_;
    int32_t device_id_;
    uint32_t source_;
    int64_t event_time_;
    uint32_t repeat_count_;
    uint32_t meta_state_;
};

} // namespace view
} // namespace android
