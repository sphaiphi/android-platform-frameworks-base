---
pattern: adapter
category: structural
cpp_standard: c++23
complexity: low
zero_cost: true
tags: [concepts, expected, interface-mismatch, legacy-wrapping, c-api]
---

## Intent

Convert the interface of a class into another interface that clients expect. In modern C++23, **concepts** define the target interface contract, and **std::expected** wraps legacy error codes into type-safe results.

## When to Use

- Existing class interface doesn't match required interface
- Wrapping a C API or third-party library
- Legacy code reuse without modification
- Multiple incompatible interfaces need unification

## When NOT to Use

- Interfaces are already compatible → use directly
- Inheritance is possible and appropriate → prefer it
- Wrapping is too deep → consider redesign

## Adapter Types

| Type           | Mechanism                   | Notes                        |
|----------------|-----------------------------|------------------------------|
| Object Adapter | Composition (preferred)     | Wraps by value or reference  |
| Class Adapter  | Inheritance                 | Only when necessary          |
| Concept Adapter| Concept-constrained template| Zero cost, compile-time      |

## Structure

```
Target Concept (IModernSensor)
    │
    └── Adapter<Legacy>  — wraps Legacy, exposes Target interface
            ├── legacy_: Legacy           — adaptee (by value or ptr)
            └── read() → expected<T, E>  — maps legacy errors
```

## Implementation

```cpp
#include <concepts>
#include <expected>
#include <string_view>
#include <memory>
#include <cstring>
#include <print>
#include <span>

// Strong types [P.1, I.4]
struct Temperature { double celsius{}; };
struct SensorId    { int value{}; auto operator<=>(const SensorId&) const = default; };

// Strong error type [Enum.3]
enum class SensorError {
    not_connected,
    read_failure,
    invalid_data,
    timeout
};

// Target concept — modern interface contract [T.10]
template<typename T>
concept ModernSensor = requires(T t, SensorId id) {
    { t.read(id) }     -> std::same_as<std::expected<Temperature, SensorError>>;
    { t.connect()  }   -> std::same_as<std::expected<void, SensorError>>;
    { t.disconnect()}  -> std::same_as<void>;
    { t.name()     }   -> std::convertible_to<std::string_view>;
};

// ---- Legacy C API (simulate third-party SDK) ----
struct CLegacySensor { int handle; };

extern "C" {
    inline auto legacy_sensor_open(int device_id) -> int {
        return device_id > 0 ? device_id : -1;  // -1 = error
    }
    inline auto legacy_sensor_read(int handle, double* out) -> int {
        if (handle <= 0 || !out) return -1;
        *out = 22.5;  // Simulated reading
        return 0;     // 0 = success
    }
    inline auto legacy_sensor_close(int handle) -> void {
        (void)handle;
    }
}
// ---- End Legacy C API ----

// Object Adapter: wraps C API — composition [C.46]
class LegacySensorAdapter {
    int  handle_{-1};    // [C.48]
    int  device_id_{};

public:
    explicit LegacySensorAdapter(int device_id)
        : device_id_(device_id) {}

    // Rule of Five: manages handle resource [C.21]
    ~LegacySensorAdapter() { disconnect(); }
    LegacySensorAdapter(const LegacySensorAdapter&) = delete;
    LegacySensorAdapter(LegacySensorAdapter&& o) noexcept
        : handle_(std::exchange(o.handle_, -1))
        , device_id_(o.device_id_) {}
    auto operator=(const LegacySensorAdapter&) -> LegacySensorAdapter& = delete;
    auto operator=(LegacySensorAdapter&& o) noexcept -> LegacySensorAdapter& {
        if (this != &o) {
            disconnect();
            handle_    = std::exchange(o.handle_, -1);
            device_id_ = o.device_id_;
        }
        return *this;
    }

    // Maps legacy int error → std::expected [E.2]
    [[nodiscard]] auto connect()
        -> std::expected<void, SensorError> {
        handle_ = legacy_sensor_open(device_id_);
        if (handle_ < 0) {
            return std::unexpected(SensorError::not_connected);
        }
        return {};
    }

    auto disconnect() -> void {
        if (handle_ >= 0) {
            legacy_sensor_close(handle_);
            handle_ = -1;
        }
    }

    [[nodiscard]] auto read(SensorId /*id*/)
        -> std::expected<Temperature, SensorError> {
        if (handle_ < 0) {
            return std::unexpected(SensorError::not_connected);
        }
        double raw{};
        if (legacy_sensor_read(handle_, &raw) != 0) {
            return std::unexpected(SensorError::read_failure);
        }
        if (raw < -273.15 || raw > 1000.0) {
            return std::unexpected(SensorError::invalid_data);
        }
        return Temperature{.celsius = raw};
    }

    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "LegacySensorAdapter";
    }
};

// Concept adapter: compile-time, zero overhead [T.10]
template<ModernSensor Sensor>
class SensorLogger {
    Sensor sensor_;   // [C.48]
public:
    explicit SensorLogger(Sensor s) : sensor_(std::move(s)) {}

    [[nodiscard]] auto read_and_log(SensorId id)
        -> std::expected<Temperature, SensorError> {
        auto result = sensor_.read(id);
        result
            .transform([&](Temperature t) {
                std::println("[LOG][{}] Temperature: {:.1f}°C",
                    sensor_.name(), t.celsius);
                return t;
            })
            .or_else([&](SensorError e) {
                std::println("[LOG][{}] Error: {}",
                    sensor_.name(), static_cast<int>(e));
                return std::expected<Temperature, SensorError>{
                    std::unexpected(e)};
            });
        return result;
    }
};

// Multi-vendor unification — different APIs, one concept [I.4]
class MockModernSensor {
public:
    [[nodiscard]] auto connect()   -> std::expected<void, SensorError> { return {}; }
    auto disconnect() -> void {}
    [[nodiscard]] auto read(SensorId) -> std::expected<Temperature, SensorError> {
        return Temperature{.celsius = 25.0};
    }
    [[nodiscard]] auto name(this auto const& self) -> std::string_view {
        return "MockModernSensor";
    }
};

// Verify both satisfy ModernSensor concept
static_assert(ModernSensor<LegacySensorAdapter>);
static_assert(ModernSensor<MockModernSensor>);
```

## Usage

```cpp
auto main() -> int {
    // Adapt legacy C API to modern interface
    auto sensor = LegacySensorAdapter{1};

    sensor.connect()
        .and_then([&](auto) { return sensor.read(SensorId{1}); })
        .transform([](Temperature t) {
            std::println("Reading: {:.1f}°C", t.celsius);
            return t;
        })
        .or_else([](SensorError e) {
            std::println("Failed: {}", static_cast<int>(e));
            return std::expected<Temperature, SensorError>{
                std::unexpected(e)};
        });

    // Concept adapter: unified interface for both legacy and modern
    auto logger1 = SensorLogger{LegacySensorAdapter{2}};
    auto logger2 = SensorLogger{MockModernSensor{}};

    auto s = LegacySensorAdapter{3};
    if (auto r = s.connect(); r) {
        logger1.read_and_log(SensorId{3});
    }
    logger2.read_and_log(SensorId{3});

    // Compile-time error: non-sensor type rejected
    // SensorLogger<int>{};  // ✗ ModernSensor concept violation
}
```

## Safety Checklist

```
✓ Type Safety    — ModernSensor concept; strong Temperature/SensorId/SensorError
✓ Bounds Safety  — No arrays; handle is scalar; no pointer arithmetic
✓ Lifetime Safety — Rule of Five for handle management; RAII disconnect
✓ Init Safety    — handle_ = -1 in-class; device_id_ in ctor list
✓ Error Safety   — Legacy int codes → std::expected; no sentinel returns
Guidelines: T.10, C.21, C.48, ES.20, R.1, Enum.3, E.2, I.4
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect        | Benefit                                  | Cost                           |
|---------------|------------------------------------------|--------------------------------|
| Reuse         | Existing legacy code unchanged           | Adapter layer maintenance      |
| Type Safety   | Concept enforces target interface        | Legacy API still unsafe inside |
| Error Safety  | Legacy int codes → std::expected         | Mapping logic required         |
| Performance   | Concept adapter: zero overhead           | Object adapter: thin wrapper   |

## Related Patterns

- **Proxy** — Same interface; Adapter changes interface
- **Facade** — Simplifies complex interface; Adapter converts interface
- **Decorator** — Adds behavior; Adapter converts interface
