---
pattern: command
category: behavioral
cpp_standard: c++23
complexity: medium
zero_cost: false
tags: [expected, unique-ptr, undo-redo, encapsulation, invoker]
---

## Intent

Encapsulate a request as an object, allowing parameterization, queuing, logging, and undo/redo operations. In modern C++23, commands return **std::expected** for type-safe error propagation and use **unique_ptr** for ownership.

## When to Use

- Operations need undo/redo capability
- Requests need to be queued, logged, or scheduled
- Operations should be composable into macros
- Decouple sender from receiver

## When NOT to Use

- Simple one-shot operation with no undo → call directly
- No queue or history needed → use std::function
- Operations always succeed → use void return

## Structure

```
Invoker (CommandHistory)
    └── execute(unique_ptr<ICommand>) → expected<void, E>
    └── undo() → expected<void, E>

ICommand (abstract)
    ├── execute() → expected<void, CommandError>
    └── undo()    → expected<void, CommandError>

ConcreteCommand
    ├── Receiver& receiver_
    └── captured state for undo
```

## Implementation

```cpp
#include <expected>
#include <memory>
#include <vector>
#include <string>
#include <print>
#include <concepts>
#include <ranges>

// Strong error type [Enum.3]
enum class CommandError {
    execution_failed,
    undo_failed,
    nothing_to_undo,
    receiver_invalid
};

// Command interface [C.2]
class ICommand {
public:
    [[nodiscard]] virtual auto execute()
        -> std::expected<void, CommandError> = 0;
    [[nodiscard]] virtual auto undo()
        -> std::expected<void, CommandError> = 0;
    [[nodiscard]] virtual auto description() const
        -> std::string_view = 0;

    virtual ~ICommand() = default;
    ICommand() = default;
    ICommand(const ICommand&) = delete;
    ICommand(ICommand&&) = delete;
    auto operator=(const ICommand&) -> ICommand& = delete;
    auto operator=(ICommand&&) -> ICommand& = delete;
};

// Concept: type is a command [T.10]
template<typename T>
concept Command = std::derived_from<T, ICommand>;

// Receiver — business logic lives here [P.1]
class TextDocument {
    std::string content_{};    // [C.48]
public:
    auto insert(std::size_t pos, std::string_view text)
        -> std::expected<void, CommandError> {
        if (pos > content_.size()) {
            return std::unexpected(CommandError::execution_failed);
        }
        content_.insert(pos, text);
        return {};
    }

    auto erase(std::size_t pos, std::size_t len)
        -> std::expected<void, CommandError> {
        if (pos + len > content_.size()) {
            return std::unexpected(CommandError::execution_failed);
        }
        content_.erase(pos, len);
        return {};
    }

    [[nodiscard]] auto content(this auto const& self)
        -> std::string_view { return self.content_; }
};

// Concrete command: InsertText
class InsertTextCommand final : public ICommand {
    TextDocument& doc_;        // Non-owning ref [R.3]
    std::size_t   pos_{};
    std::string   text_{};

public:
    explicit InsertTextCommand(
        TextDocument& doc,
        std::size_t pos,
        std::string text)
        : doc_(doc)
        , pos_(pos)
        , text_(std::move(text)) {}

    [[nodiscard]] auto execute()
        -> std::expected<void, CommandError> override {
        return doc_.insert(pos_, text_);
    }

    [[nodiscard]] auto undo()
        -> std::expected<void, CommandError> override {
        return doc_.erase(pos_, text_.size());
    }

    [[nodiscard]] auto description() const
        -> std::string_view override { return "InsertText"; }
};

// Concrete command: EraseText
class EraseTextCommand final : public ICommand {
    TextDocument& doc_;
    std::size_t   pos_{};
    std::size_t   len_{};
    std::string   erased_{};   // Captured for undo

public:
    explicit EraseTextCommand(
        TextDocument& doc,
        std::size_t pos,
        std::size_t len)
        : doc_(doc)
        , pos_(pos)
        , len_(len) {}

    [[nodiscard]] auto execute()
        -> std::expected<void, CommandError> override {
        erased_ = std::string(doc_.content().substr(pos_, len_));
        return doc_.erase(pos_, len_);
    }

    [[nodiscard]] auto undo()
        -> std::expected<void, CommandError> override {
        if (erased_.empty()) {
            return std::unexpected(CommandError::undo_failed);
        }
        return doc_.insert(pos_, erased_);
    }

    [[nodiscard]] auto description() const
        -> std::string_view override { return "EraseText"; }
};

// Macro command: compose multiple commands [Composite]
class MacroCommand final : public ICommand {
    std::vector<std::unique_ptr<ICommand>> commands_;  // [R.20]
    std::string name_;

public:
    explicit MacroCommand(std::string name)
        : name_(std::move(name)) {}

    auto add(std::unique_ptr<ICommand> cmd) -> void {
        commands_.push_back(std::move(cmd));
    }

    [[nodiscard]] auto execute()
        -> std::expected<void, CommandError> override {
        for (auto& cmd : commands_) {
            if (auto r = cmd->execute(); !r) return r;
        }
        return {};
    }

    [[nodiscard]] auto undo()
        -> std::expected<void, CommandError> override {
        for (auto& cmd : commands_ | std::views::reverse) {
            if (auto r = cmd->undo(); !r) return r;
        }
        return {};
    }

    [[nodiscard]] auto description() const
        -> std::string_view override { return name_; }
};

// Invoker: command history with undo stack [R.1]
class CommandHistory {
    std::vector<std::unique_ptr<ICommand>> history_;  // [R.20]
    std::size_t undo_index_{0};

public:
    [[nodiscard]] auto execute(std::unique_ptr<ICommand> cmd)
        -> std::expected<void, CommandError> {

        auto result = cmd->execute();
        if (!result) return result;

        // Truncate redo stack on new command
        history_.erase(
            history_.begin() +
                static_cast<std::ptrdiff_t>(undo_index_),
            history_.end()
        );
        history_.push_back(std::move(cmd));
        ++undo_index_;
        return {};
    }

    [[nodiscard]] auto undo()
        -> std::expected<void, CommandError> {
        if (undo_index_ == 0) {
            return std::unexpected(CommandError::nothing_to_undo);
        }
        --undo_index_;
        std::println("[History] Undoing: {}",
            history_[undo_index_]->description());
        return history_[undo_index_]->undo();
    }

    [[nodiscard]] auto redo()
        -> std::expected<void, CommandError> {
        if (undo_index_ >= history_.size()) {
            return std::unexpected(CommandError::nothing_to_undo);
        }
        std::println("[History] Redoing: {}",
            history_[undo_index_]->description());
        auto result = history_[undo_index_]->execute();
        if (result) ++undo_index_;
        return result;
    }

    [[nodiscard]] auto history_size() const -> std::size_t {
        return history_.size();
    }
};
```

## Usage

```cpp
auto main() -> int {
    TextDocument doc{};
    CommandHistory history{};

    // Execute commands
    history.execute(std::make_unique<InsertTextCommand>(doc, 0, "Hello"));
    history.execute(std::make_unique<InsertTextCommand>(doc, 5, ", World"));
    std::println("Doc: {}", doc.content());  // Hello, World

    // Undo
    history.undo();
    std::println("After undo: {}", doc.content());  // Hello

    // Redo
    history.redo();
    std::println("After redo: {}", doc.content());  // Hello, World

    // Macro command
    auto macro = std::make_unique<MacroCommand>("Bold");
    macro->add(std::make_unique<InsertTextCommand>(doc, 0, "<b>"));
    macro->add(std::make_unique<InsertTextCommand>(doc, doc.content().size() + 3, "</b>"));
    history.execute(std::move(macro));

    // Error path
    auto result = history.undo();
    if (!result) {
        std::println("Undo failed: {}",
            static_cast<int>(result.error()));
    }
}
```

## Safety Checklist

```
✓ Type Safety    — CommandError enum class; ICommand interface
✓ Bounds Safety  — std::vector; range-for with views::reverse
✓ Lifetime Safety — unique_ptr owns commands; non-owning ref to receiver
✓ Init Safety    — All members initialized; erased_ lazily in execute()
✓ Error Safety   — std::expected on all operations; [[nodiscard]]
Guidelines: R.20, R.3, Enum.3, ES.20, C.48, E.2, T.10
```

## Compile

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -Werror -O3
```

## Trade-offs

| Aspect        | Benefit                              | Cost                           |
|---------------|--------------------------------------|--------------------------------|
| Undo/Redo     | Full history with redo support       | Memory for captured state      |
| Composition   | MacroCommand composites freely       | Nested undo complexity         |
| Decoupling    | Invoker knows nothing of receiver    | Extra command class per op     |
| Error Safety  | std::expected propagates cleanly     | Callers must handle results    |

## Related Patterns

- **Strategy** — Encapsulates algorithm; Command encapsulates request
- **Memento** — Captures state for undo without Command overhead
- **Chain of Responsibility** — Commands can form a processing chain
