---
pattern: observer
category: behavioral
cpp_standard: c++23
complexity: medium
zero_cost: false
tags: [weak-ptr, function, event, publish-subscribe, lifetime-safe]
---

## Intent

Define a one-to-many dependency so that when one object changes state, all dependents are notified automatically. In modern C++23, use **std::function** for lightweight callbacks and **weak_ptr** to prevent dangling observer lifetimes.

## When to Use

- One object's state change requires updating unknown number of others
- Objects should be able to notify without assumptions about who is listening
- Decoupled event propagation needed across components

## When NOT to Use

- Single known observer → call directly
- Synchronous notification only → consider callbacks
- Observers outlive subject always → raw function is safe

## Structure

```
Subject
    ├── attach(weak_ptr<IObserver> | function) → Token
    ├── detach(Token)
    └── notify(Event) → dispatches to all live observers

Observer (weak_ptr — auto-cleanup on destruction)
    └── on_event(Event) → void
```

## Implementation

```cpp
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cstdint>
#include <ranges>
#include <print>
#include <optional>

// Strong token type for unsubscription [P.1]
struct SubscriptionToken {
    std::uint64_t id{};
    auto operator<=>(const SubscriptionToken&) const = default;  // Spaceship [C++20]
};

// Strong event types [I.4, Enum.3]
struct TemperatureChanged { double celsius{}; };
struct HumidityChanged    { double percent{}; };
struct SensorOffline      { std::string_view sensor_id; };

using SensorEvent = std::variant<TemperatureChanged, HumidityChanged, SensorOffline>;

// Observer interface — default no-ops [C.2]
class ISensorObserver {
public:
    virtual auto on_event(const SensorEvent&) -> void {}
    virtual ~ISensorObserver() = default;
    ISensorObserver() = default;
    ISensorObserver(const ISensorObserver&) = delete;
    ISensorObserver(ISensorObserver&&) = delete;
    auto operator=(const ISensorObserver&) -> ISensorObserver& = delete;
    auto operator=(ISensorObserver&&) -> ISensorObserver& = delete;
};

// Type-safe subject with weak_ptr lifetime management [R.21]
class SensorSubject {
    using ObserverFn = std::function<void(const SensorEvent&)>;

    struct Entry {
        std::weak_ptr<ISensorObserver> weak;   // Lifetime-safe [R.21]
        std::optional<ObserverFn> fn;          // Function-based alternative
    };

    std::unordered_map<std::uint64_t, Entry> observers_;  // [ES.20]
    std::uint64_t next_id_{1};

public:
    // Register shared_ptr observer — auto-cleanup on expiry [R.20]
    [[nodiscard]] auto attach(std::shared_ptr<ISensorObserver> obs)
        -> SubscriptionToken {
        const auto id = next_id_++;
        observers_[id] = Entry{.weak = obs};
        return SubscriptionToken{id};
    }

    // Register lightweight function observer
    [[nodiscard]] auto attach(ObserverFn fn)
        -> SubscriptionToken {
        const auto id = next_id_++;
        observers_[id] = Entry{.fn = std::move(fn)};
        return SubscriptionToken{id};
    }

    auto detach(SubscriptionToken token) -> void {
        observers_.erase(token.id);
    }

    auto notify(const SensorEvent& event) -> void {
        // Collect expired entries for cleanup
        std::vector<std::uint64_t> expired;

        for (auto& [id, entry] : observers_) {
            if (entry.fn) {
                (*entry.fn)(event);
            } else if (auto obs = entry.weak.lock()) {
                obs->on_event(event);
            } else {
                expired.push_back(id);  // Observer destroyed — cleanup
            }
        }

        // Remove expired observers [ES.71: range-for]
        for (auto id : expired) {
            observers_.erase(id);
        }
    }
};

// Concrete observers
class Dashboard : public ISensorObserver {
public:
    auto on_event(const SensorEvent& event) -> void override {
        std::visit([](auto const& e) {
            using T = std::decay_t<decltype(e)>;
            if constexpr (std::is_same_v<T, TemperatureChanged>) {
                std::println("[Dashboard] Temperature: {:.1f}°C", e.celsius);
            } else if constexpr (std::is_same_v<T, HumidityChanged>) {
                std::println("[Dashboard] Humidity: {:.1f}%", e.percent);
            } else if constexpr (std::is_same_v<T, SensorOffline>) {
                std::println("[Dashboard] Sensor offline: {}", e.sensor_id);
            }
        }, event);
    }
};

class Alarm : public ISensorObserver {
    double threshold_{40.0};  // [C.48]
public:
    explicit Alarm(double threshold) : threshold_(threshold) {}

    auto on_event(const SensorEvent& event) -> void override {
        if (auto* t = std::get_if<TemperatureChanged>(&event)) {
            if (t->celsius > threshold_) {
                std::println("[Alarm] ALERT: Temperature {:.1f}°C exceeds {:.1f}°C",
                    t->celsius, threshold_);
            }
        }
    }
};
```

## Usage

```cpp
auto main() -> int {
    SensorSubject subject{};

    // Shared ownership observers — auto-cleanup on destruction
    auto dashboard = std::make_shared<Dashboard>();
    auto alarm     = std::make_shared<Alarm>(35.0);

    auto t1 = subject.attach(dashboard);
    auto t2 = subject.attach(alarm);

    // Lightweight lambda observer
    auto t3 = subject.attach([](const SensorEvent& e) {
        if (std::holds_alternative<SensorOffline>(e)) {
            std::println("[Logger] Sensor offline event logged");
        }
    });

    subject.notify(TemperatureChanged{.celsius = 22.5});
    subject.notify(HumidityChanged{.percent = 65.0});
    subject.notify(TemperatureChanged{.celsius = 38.0});  // Triggers alarm

    // Detach specific observer
    subject.detach(t2);

    // Lifetime safety: dashboard destroyed → auto-removed on next notify
    dashboard.reset();
    subject.notify(SensorOffline{.sensor_id = "sensor-01"});
    // dashboard entry silently cleaned up — no dangling call
}
```

## Safety Checklist

```
✓ Type Safety    — SensorEvent as variant; strong token type
✓ Bounds Safety  — unordered_map; range-for for cleanup; no C arrays
✓ Lifetime Safety — weak_ptr prevents dangling; expired auto-cleaned
✓ Init Safety    — All members initialized; next_id_ in-class
✓ Error Safety   — No exceptions; detach is idempotent
Guidelines: R.21, R.20, ES.20, C.48, P.1, Enum.3
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect         | Benefit                                    | Cost                              |
|----------------|--------------------------------------------|-----------------------------------|
| Lifetime       | weak_ptr auto-cleans destroyed observers   | Lock cost per notify              |
| Flexibility    | Both interface and function observers      | Two dispatch paths                |
| Decoupling     | Subject knows nothing about observers      | Notification order undefined      |
| Performance    | Lazy cleanup on notify                     | Dead entries linger until notify  |

## Related Patterns

- **Mediator** — Centralizes complex observer interactions
- **Event Bus** — Global observer registry
- **Command** — Encapsulates change notifications as commands
