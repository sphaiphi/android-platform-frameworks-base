---
pattern: state
category: behavioral
cpp_standard: c++23
complexity: medium
zero_cost: true
tags: [variant, visit, type-states, illegal-state-prevention]
---

## Intent

Allow an object to alter its behavior when its internal state changes. In modern C++23, use **std::variant** for type-safe states where **illegal state transitions are impossible at compile time**.

## When to Use

- Object behavior depends on state and changes at runtime
- Large conditionals based on object state exist
- State transitions need to be explicit and auditable
- Invalid states must be unrepresentable

## When NOT to Use

- Only one or two states → use bool/optional
- States don't affect behavior → plain data member
- Transitions need no enforcement → use enum class + switch

## Structure

```
State = std::variant<StateA, StateB, StateC>

StateMachine
    ├── state_ : State
    ├── handle(Event) → void
    │       └── std::visit → dispatch to current state
    └── Each state returns next State (encoding valid transitions)
```

## Implementation

```cpp
#include <variant>
#include <expected>
#include <string_view>
#include <print>
#include <concepts>

// Strong event types [P.1, I.4]
struct StartEvent  { std::string_view reason; };
struct StopEvent   { std::string_view reason; };
struct PauseEvent  {};
struct ResumeEvent {};

using Event = std::variant<StartEvent, StopEvent, PauseEvent, ResumeEvent>;

// Strong error type [Enum.3]
enum class TransitionError {
    invalid_transition,
    already_in_state
};

// Forward declarations
struct Idle;
struct Running;
struct Paused;
struct Stopped;

// Legal transition encoding in return types — illegal states unrepresentable [P.4]
struct Idle {
    static constexpr std::string_view name = "Idle";

    // Only valid from Idle: start → Running
    [[nodiscard]] auto on(StartEvent e) const
        -> std::expected<Running, TransitionError>;

    // All other events: invalid
    [[nodiscard]] auto on(StopEvent) const
        -> std::expected<Stopped, TransitionError> {
        return std::unexpected(TransitionError::invalid_transition);
    }
    [[nodiscard]] auto on(PauseEvent) const
        -> std::expected<Paused, TransitionError> {
        return std::unexpected(TransitionError::invalid_transition);
    }
    [[nodiscard]] auto on(ResumeEvent) const
        -> std::expected<Running, TransitionError> {
        return std::unexpected(TransitionError::invalid_transition);
    }

    auto on_enter() const -> void { std::println("[Idle] entered"); }
    auto on_exit()  const -> void { std::println("[Idle] exited"); }
};

struct Running {
    static constexpr std::string_view name = "Running";
    std::string_view started_by;

    // Valid transitions from Running: pause, stop
    [[nodiscard]] auto on(PauseEvent) const
        -> std::expected<Paused, TransitionError>;
    [[nodiscard]] auto on(StopEvent e) const
        -> std::expected<Stopped, TransitionError>;

    [[nodiscard]] auto on(StartEvent) const
        -> std::expected<Running, TransitionError> {
        return std::unexpected(TransitionError::already_in_state);
    }
    [[nodiscard]] auto on(ResumeEvent) const
        -> std::expected<Running, TransitionError> {
        return std::unexpected(TransitionError::already_in_state);
    }

    auto on_enter() const -> void { std::println("[Running] entered, started by: {}", started_by); }
    auto on_exit()  const -> void { std::println("[Running] exited"); }
};

struct Paused {
    static constexpr std::string_view name = "Paused";

    // Valid from Paused: resume → Running, stop → Stopped
    [[nodiscard]] auto on(ResumeEvent) const
        -> std::expected<Running, TransitionError>;
    [[nodiscard]] auto on(StopEvent e) const
        -> std::expected<Stopped, TransitionError>;

    [[nodiscard]] auto on(StartEvent) const
        -> std::expected<Running, TransitionError> {
        return std::unexpected(TransitionError::invalid_transition);
    }
    [[nodiscard]] auto on(PauseEvent) const
        -> std::expected<Paused, TransitionError> {
        return std::unexpected(TransitionError::already_in_state);
    }

    auto on_enter() const -> void { std::println("[Paused] entered"); }
    auto on_exit()  const -> void { std::println("[Paused] exited"); }
};

struct Stopped {
    static constexpr std::string_view name = "Stopped";
    std::string_view stopped_by;

    // Terminal state — no valid transitions
    auto on(auto) const -> std::expected<Stopped, TransitionError> {
        return std::unexpected(TransitionError::invalid_transition);
    }

    auto on_enter() const -> void { std::println("[Stopped] entered, by: {}", stopped_by); }
    auto on_exit()  const -> void {}
};

// Deferred definitions
inline auto Idle::on(StartEvent e) const -> std::expected<Running, TransitionError> {
    return Running{.started_by = e.reason};
}
inline auto Running::on(PauseEvent) const -> std::expected<Paused, TransitionError> {
    return Paused{};
}
inline auto Running::on(StopEvent e) const -> std::expected<Stopped, TransitionError> {
    return Stopped{.stopped_by = e.reason};
}
inline auto Paused::on(ResumeEvent) const -> std::expected<Running, TransitionError> {
    return Running{.started_by = "resumed"};
}
inline auto Paused::on(StopEvent e) const -> std::expected<Stopped, TransitionError> {
    return Stopped{.stopped_by = e.reason};
}

// Type-safe state variant — only legal states exist [P.4]
using State = std::variant<Idle, Running, Paused, Stopped>;

// State machine — std::visit for exhaustive dispatch
class StateMachine {
    State state_{Idle{}};   // [C.48: in-class init]

public:
    [[nodiscard]] auto current_name(this auto const& self) -> std::string_view {
        return std::visit([](auto const& s) { return s.name; }, self.state_);
    }

    [[nodiscard]] auto handle(Event event)
        -> std::expected<void, TransitionError> {

        return std::visit(
            [this](auto const& state, auto const& evt)
                -> std::expected<void, TransitionError> {

                return state.on(evt)
                    .transform([this, &state](auto&& next_state) {
                        // Exit current, enter next
                        std::visit([](auto const& s) { s.on_exit(); }, state_);
                        state_ = std::move(next_state);
                        std::visit([](auto const& s) { s.on_enter(); }, state_);
                    });
            },
            state_, event
        );
    }
};
```

## Usage

```cpp
auto main() -> int {
    StateMachine sm{};
    std::println("State: {}", sm.current_name());  // Idle

    // Valid transitions
    sm.handle(StartEvent{"user request"});  // Idle → Running
    sm.handle(PauseEvent{});               // Running → Paused
    sm.handle(ResumeEvent{});              // Paused → Running
    sm.handle(StopEvent{"shutdown"});      // Running → Stopped

    // Invalid transition caught via std::expected
    auto result = sm.handle(StartEvent{"retry"});
    if (!result) {
        std::println("Invalid: cannot start from Stopped");
    }

    // Compile-time: cannot construct invalid state
    // State s = 42;  // ✗ not a valid state type
}
```

## Safety Checklist

```
✓ Type Safety    — variant<> only holds legal state types; no raw enum
✓ Bounds Safety  — std::visit exhaustive; no unchecked indexing
✓ Lifetime Safety — States are value types; no pointer ownership issues
✓ Init Safety    — state_ initialized to Idle{}; no uninit state
✓ Error Safety   — std::expected for invalid transitions; no silent failure
Guidelines: P.4, Enum.3, ES.20, C.48, E.2, T.10
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect           | Benefit                                  | Cost                              |
|------------------|------------------------------------------|-----------------------------------|
| Safety           | Illegal states unrepresentable           | More types to define              |
| Exhaustiveness   | std::visit forces all states handled     | Verbose visit lambdas             |
| Performance      | No vtable; variant is stack-allocated    | Variant size = largest state      |
| Extensibility    | Add state = add variant member           | All visit sites need updating     |

## Related Patterns

- **Strategy** — Algorithm changes, not full behavior
- **Command** — Encapsulates state transitions as commands
- **Observer** — Notify others of state changes
