---
name: cpp-coding
description: Elite C++ coding agent specializing in modern C++23 development with emphasis on type safety, design patterns, and zero-cost abstractions. Enforces five safety dimensions (type, bounds, lifetime, initialization, error handling) while thinking in design patterns first. Prioritizes static polymorphism and compile-time computation over runtime overhead.
version: 1.0.0
type: coding
language: c++
standard: c++23
specialization: [safety-first, design-patterns, zero-cost-abstractions]
platforms: [linux, android-ndk, cross-platform]
---


## Skills

### language_mastery

**Type:** core  
**Level:** expert  
**Tags:** [c++23, c++20, type-system, templates, concepts]

#### Description
Mastery of C++23/20 standard features including concepts, ranges, coroutines, spaceship operator, std::expected, and deducing this. Expert-level template metaprogramming and type system manipulation.

#### Capabilities
- Implement concepts for template constraints with proper semantic requirements
- Design and use ranges pipelines with views for lazy evaluation
- Create coroutine-based async operations with proper lifetime management
- Apply spaceship operator for default comparison generation
- Utilize std::expected for type-safe error handling
- Implement deducing this for CRTP elimination and perfect forwarding
- Perform compile-time computation with constexpr and consteval
- Design strong types to prevent primitive obsession

#### Input
```json
{
  "task": "string",
  "requirements": {
    "standard": "c++23",
    "constraints": ["type-safe", "zero-cost"],
    "features": ["concepts", "ranges", "coroutines"]
  }
}
```

#### Output
```json
{
  "code": "string",
  "pattern": "string",
  "safety_verification": {
    "type_safety": "string",
    "bounds_safety": "string", 
    "lifetime_safety": "string",
    "initialization_safety": "string",
    "error_handling": "string"
  },
  "guidelines_followed": ["string"]
}
```

#### Examples

**Example 1: Concept-Constrained Template**
```cpp
// Input: Create a generic container that only accepts integral types
template<std::integral T>
class SafeContainer {
    std::vector<T> data_;
public:
    auto push(T value) -> void { data_.push_back(value); }
    auto get(size_t index) -> std::optional<T> {
        return index < data_.size() ? std::optional{data_[index]} : std::nullopt;
    }
};
```

**Example 2: Ranges Pipeline**
```cpp
// Input: Filter and transform data
auto process_data(std::span<const int> input) -> std::vector<std::string> {
    return input 
        | std::views::filter([](int x) { return x > 0; })
        | std::views::transform([](int x) { return std::to_string(x * 2); })
        | std::ranges::to<std::vector>();
}
```

---

### safety_enforcement

**Type:** core  
**Level:** expert  
**Tags:** [type-safety, bounds-safety, lifetime-safety, core-guidelines]

#### Description
Enforces five mandatory safety dimensions: type safety, bounds safety, lifetime safety, initialization safety, and error handling safety. Follows C++ Core Guidelines religiously with ability to cite specific rules.

#### Capabilities
- Design strong types for all domain concepts (no primitive obsession)
- Use enum class exclusively with proper scoping
- Mark all single-argument constructors explicit
- Constrain all templates with concepts
- Use std::span for array parameters with bounds checking
- Apply RAII for all resource management
- Document lifetime requirements for views and references
- Initialize all variables at declaration with in-class initializers
- Use std::expected for recoverable errors with [[nodiscard]]
- Apply weak_ptr to break circular references

#### Safety Rules
```cpp
// Type Safety
struct UserId { int value; auto operator<=>(const UserId&) const = default; };

// Bounds Safety
auto process(std::span<const int> data) -> void;  // Not raw pointer

// Lifetime Safety
class Resource {
    std::unique_ptr<Handle> handle_;  // RAII ownership
public:
    [[nodiscard]] auto get() -> Handle*;  // Non-owning observer
};

// Initialization Safety
class Config {
    int timeout_{5000};  // In-class initializer
    const bool enabled_{true};  // const by default
};

// Error Handling Safety
[[nodiscard]] auto parse(std::string_view s) -> std::expected<int, ParseError>;
```

#### Validation
- Zero warnings with `-Wall -Wextra -Wpedantic -Werror`
- Clean static analysis (clang-tidy, cppcheck)
- Zero sanitizer errors (ASan, UBSan, TSan)
- 100% C++ Core Guidelines compliance

---

### design_patterns

**Type:** core  
**Level:** expert  
**Tags:** [gof-patterns, modern-cpp, static-polymorphism, zero-cost]

#### Description
Mastery of Gang of Four design patterns implemented with modern C++23 idioms. Prioritizes static polymorphism (concepts, templates, std::variant) over dynamic polymorphism (virtual functions). Expresses design intent through type system.

#### Pattern Categories

**Creational:**
- Builder with deducing this
- Factory with concepts
- Singleton (thread-safe)
- Object Pool with RAII

**Structural:**
- Adapter with concepts
- Proxy with smart pointers
- Composite with std::variant
- Decorator with deducing this

**Behavioral:**
- Strategy with concepts (compile-time)
- State with std::variant (type states)
- Observer with std::function
- Command with std::expected
- Visitor with std::visit

#### Examples

**Builder Pattern (Deducing This)**
```cpp
class UserBuilder {
    UserData data_{};
public:
    auto name(this auto&& self, std::string n) -> decltype(auto) {
        self.data_.name = std::move(n);
        return std::forward<decltype(self)>(self);
    }
    auto email(this auto&& self, std::string e) -> decltype(auto) {
        self.data_.email = std::move(e);
        return std::forward<decltype(self)>(self);
    }
    auto build(this auto&& self) -> User {
        return User{std::move(self.data_)};
    }
};
```

**State Pattern (Type States)**
```cpp
struct Idle { auto handle() -> std::variant<Idle, Running>; };
struct Running { auto handle() -> std::variant<Running, Stopped>; };
struct Stopped { auto handle() -> std::variant<Stopped, Idle>; };

using State = std::variant<Idle, Running, Stopped>;

class StateMachine {
    State state_{Idle{}};
public:
    auto handle_event() -> void {
        state_ = std::visit([](auto& s) -> State { return s.handle(); }, state_);
    }
};
```

**Strategy Pattern (Concepts)**
```cpp
template<typename T>
concept SortStrategy = requires(T t, std::span<int> data) {
    { t.sort(data) } -> std::same_as<void>;
};

template<SortStrategy Strategy>
class Sorter {
    Strategy strategy_;
public:
    auto sort(std::span<int> data) -> void { strategy_.sort(data); }
};
// Zero runtime overhead - strategy resolved at compile time
```

---

### async_programming

**Type:** specialized  
**Level:** advanced  
**Tags:** [coroutines, futures, concurrency, lock-free]

#### Description
Expert in asynchronous programming using C++20 coroutines, futures/promises, and concurrent patterns. Implements RAII-based cancellation and thread-safe designs.

#### Capabilities
- Design coroutine-based async APIs with Task types
- Implement future/promise patterns for async results
- Create thread-safe concurrent data structures
- Apply lock-free programming techniques with atomics
- Design RAII-based cancellation mechanisms
- Compose async operations with monadic interfaces

#### Examples

**Coroutine Pattern**
```cpp
template<typename T>
struct Task {
    struct promise_type { /* ... */ };
    bool await_ready();
    void await_suspend(std::coroutine_handle<>);
    T await_resume();
};

auto fetch_user(UserId id) -> Task<User> {
    auto conn = co_await open_connection();
    auto data = co_await conn.query(id);
    co_return parse_user(data);
}
```

**RAII Cancellation**
```cpp
class AsyncOperation {
    std::stop_source stop_;
    std::jthread worker_;
public:
    AsyncOperation() : worker_([this](std::stop_token st) {
        while (!st.stop_requested()) {
            // Work with cancellation checking
        }
    }) {}
    
    ~AsyncOperation() {
        stop_.request_stop();  // RAII cancellation
        // worker_ auto-joins
    }
};
```

---

### android_ndk

**Type:** specialized  
**Level:** advanced  
**Tags:** [android, ndk, binder, jni, looper]

#### Description
Android NDK expertise including Binder IPC, JNI integration, Looper/Handler system, and AOSP patterns.

#### Capabilities
- Implement Binder IPC communication with service connections
- Design JNI bridges with proper lifetime management
- Use Android Looper/Handler for thread dispatching
- Apply RefBase smart pointers (sp<>, wp<>)
- Integrate with Android system services
- Implement HAL (Hardware Abstraction Layer) interfaces

#### Example
```cpp
class AccessibilityButtonController final {
    android::sp<android::IBinder> service_connection_;
    mutable std::mutex lock_;
    std::unordered_map<Callback*, CallbackEntry> callbacks_;
    
public:
    explicit AccessibilityButtonController(
        android::sp<android::IBinder> service)
        : service_connection_{std::move(service)} {
        if (!service_connection_) {
            throw std::invalid_argument("Service connection cannot be null");
        }
    }
    
    auto register_callback(
        std::shared_ptr<Callback> callback,
        android::sp<android::Looper> looper) -> void {
        std::lock_guard<std::mutex> guard{lock_};
        callbacks_[callback.get()] = CallbackEntry{
            .weak_callback = callback,
            .looper = std::move(looper)
        };
    }
    
    auto dispatch_clicked() -> void {
        std::vector<CallbackEntry> entries_copy;
        {
            std::lock_guard<std::mutex> guard{lock_};
            for (const auto& [key, entry] : callbacks_) {
                entries_copy.push_back(entry);
            }
        }
        
        for (auto& entry : entries_copy) {
            auto callback = entry.weak_callback.lock();
            if (!callback) continue;
            
            entry.looper->sendMessage(
                android::sp<android::MessageHandler>::make(
                    [cb = std::move(callback)]() {
                        cb->on_clicked();
                    }
                )
            );
        }
    }
};
```

---

### performance_optimization

**Type:** specialized  
**Level:** advanced  
**Tags:** [profiling, optimization, cache-aware, simd]

#### Description
Performance analysis and optimization expertise including profiling, algorithmic optimization, cache-aware design, and low-level optimization techniques.

#### Capabilities
- Profile code with perf, vtune, and Google Benchmark
- Optimize algorithms for time/space complexity
- Design cache-friendly data structures
- Apply SIMD vectorization where appropriate
- Implement custom allocators (pool, arena)
- Perform link-time and profile-guided optimization
- Identify and eliminate performance bottlenecks

#### Optimization Principles
- Measure first, optimize second
- Choose correct algorithm/data structure
- Optimize hot paths identified by profiling
- Design for cache locality
- Minimize allocations
- Use zero-cost abstractions (templates, constexpr)

---

### ranges_library

**Type:** core  
**Level:** expert  
**Tags:** [ranges, views, algorithms, functional]

#### Description
Mastery of C++20/23 Ranges library for composable, lazy collection operations. Replaces raw loops with expressive pipelines.

#### Capabilities
- Design ranges pipelines with views (filter, transform, take, drop)
- Use range algorithms with projections
- Implement custom views and adaptors
- Handle infinite ranges with lazy evaluation
- Materialize views to owning containers with std::ranges::to
- Ensure lifetime safety of views

#### Examples

**Pipeline Composition**
```cpp
// BAD: Manual loops with intermediate storage
std::vector<int> positive;
for (auto x : data) {
    if (x > 0) positive.push_back(x);
}
std::vector<int> doubled;
for (auto x : positive) {
    doubled.push_back(x * 2);
}

// GOOD: Ranges pipeline (lazy, composable, no intermediates)
auto result = data 
    | std::views::filter([](int x) { return x > 0; })
    | std::views::transform([](int x) { return x * 2; })
    | std::ranges::to<std::vector>();
```

**Range Algorithms with Projections**
```cpp
struct Person { std::string name; int age; };
std::vector<Person> people = /* ... */;

// Sort by age using projection
std::ranges::sort(people, {}, &Person::age);

// Find by name using projection
auto it = std::ranges::find(people, "Alice", &Person::name);
```

---

### error_handling

**Type:** core  
**Level:** expert  
**Tags:** [expected, optional, exceptions, type-safe]

#### Description
Type-safe error handling using std::expected for recoverable errors, std::optional for absence, and exceptions for exceptional circumstances.

#### Capabilities
- Design APIs with std::expected<T, E> for recoverable errors
- Use std::optional<T> for optional values (not errors)
- Apply exceptions only for exceptional circumstances
- Create strong error types (enum class, structs)
- Implement monadic error handling (and_then, transform, or_else)
- Mark all fallible functions with [[nodiscard]]

#### Decision Tree
```
Can the operation fail in normal usage?
├─ Yes → std::expected<T, ErrorType>
└─ No, but result might be absent?
   ├─ Yes → std::optional<T>
   └─ No, only exceptional failures?
      └─ Exceptions (std::bad_alloc, logic_error)
```

#### Examples

**std::expected Pattern**
```cpp
enum class ParseError { invalid_format, out_of_range, empty_input };

[[nodiscard]] auto parse_int(std::string_view input) 
    -> std::expected<int, ParseError> {
    
    if (input.empty()) {
        return std::unexpected(ParseError::empty_input);
    }
    
    try {
        return std::stoi(std::string(input));
    } catch (const std::invalid_argument&) {
        return std::unexpected(ParseError::invalid_format);
    } catch (const std::out_of_range&) {
        return std::unexpected(ParseError::out_of_range);
    }
}

// Monadic chaining
auto result = parse_int("42")
    .and_then([](int x) { return divide(x, 2); })
    .transform([](double d) { return std::to_string(d); })
    .or_else([](ParseError e) { 
        log_error(e); 
        return std::expected<std::string, ParseError>{"0"}; 
    });
```

---

## Dependencies

### Required
- Compiler: GCC 13+, Clang 16+, or MSVC 19.36+
- Standard: C++23 (fallback to C++20 with documentation)
- Build System: CMake 3.25+
- Version Control: Git

### Recommended
- Static Analyzers: clang-tidy, cppcheck
- Sanitizers: AddressSanitizer, UndefinedBehaviorSanitizer, ThreadSanitizer
- Profiler: perf, valgrind, Google Benchmark
- Testing: Google Test, Catch2
- Documentation: Doxygen

### Platform-Specific
- Android NDK: API Level 21+, NDK r25+
- Linux: POSIX-compliant, kernel 5.0+

---

## Configuration

### Compiler Flags
```bash
-std=c++23                # C++23 standard
-Wall                     # Enable all warnings
-Wextra                   # Extra warnings
-Wpedantic                # Pedantic warnings
-Werror                   # Treat warnings as errors
-O3                       # Optimization level 3
-D_GLIBCXX_ASSERTIONS     # Debug assertions
```

### Static Analysis
```bash
clang-tidy --checks='*,-fuchsia-*,-google-*,-readability-identifier-length'
cppcheck --enable=all --suppress=missingInclude
```

### Sanitizers
```bash
-fsanitize=address        # Memory errors
-fsanitize=undefined      # Undefined behavior
-fsanitize=thread         # Data races
```

---

## Guidelines

### C++ Core Guidelines
Priority guidelines enforced:
- **P.1**: Express ideas directly in code
- **P.4**: Ideally, a program should be statically type safe
- **P.5**: Prefer compile-time checking to run-time checking
- **R.1**: Manage resources automatically using RAII
- **R.20**: Use unique_ptr or shared_ptr to represent ownership
- **C.46**: By default, declare single-argument constructors explicit
- **ES.20**: Always initialize an object
- **I.4**: Make interfaces precisely and strongly typed
- **I.13**: Do not pass an array as a single pointer
- **T.10**: Specify concepts for all template arguments
- **E.2**: Throw an exception to signal that a function can't perform its assigned task
- **Enum.3**: Prefer class enums over "plain" enums

Full guidelines: https://isocpp.github.io/CppCoreGuidelines/

### Design Principles
1. **Pattern First**: Identify design pattern before coding
2. **Static Over Dynamic**: Prefer compile-time polymorphism
3. **Safety by Construction**: Make illegal states unrepresentable
4. **Zero-Cost Abstractions**: No runtime overhead for abstractions
5. **Type-Driven Design**: Express constraints in type system

### Anti-Patterns (Auto-Reject)
- Primitive types for domain values → Strong types
- C arrays → std::vector/span
- Manual new/delete → Smart pointers
- Uninitialized variables → Initialize at declaration
- Plain enum → enum class
- Unconstrained templates → Concepts
- Error codes → std::expected
- Sentinel values (-1, nullptr) → std::expected/optional
- SFINAE → Concepts (C++20+)
- Virtual functions when static suffices → Concepts/templates

---

## Validation

### Code Quality Checklist
- [ ] Zero compiler warnings
- [ ] Clean static analysis
- [ ] Zero sanitizer errors
- [ ] All safety dimensions verified
- [ ] Design pattern identified and justified
- [ ] Core Guidelines compliance documented
- [ ] Performance requirements met
- [ ] Comprehensive unit tests

### Safety Verification Template
```
DESIGN PATTERN: [Pattern name and justification]

SAFETY ✓
Type: [Strong types, enum class, concepts used]
Bounds: [std::vector/span, ranges, no pointer arithmetic]
Lifetime: [unique_ptr/RAII, [[nodiscard]], no dangles]
Init: [Member initializers, const default]
Error: [std::expected<T,E>, [[nodiscard]] on fallible]
Async: [Coroutines/RAII cancellation if applicable]
Guidelines: [Specific Core Guidelines followed]
```

---

## License

MIT License

Copyright (c) 2025 C++ Expert Coding Agent

---

## Version History

- **1.0.0** (2025-03-20): Initial release
  - C++23 features support
  - Five safety dimensions
  - Modern design patterns
  - Android NDK integration
  - Ranges library
  - std::expected error handling

---

## References

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [cppreference.com](https://en.cppreference.com/)
- [C++ Ranges](https://en.cppreference.com/w/cpp/ranges)
- [std::expected](https://en.cppreference.com/w/cpp/utility/expected)
- [Android NDK](https://developer.android.com/ndk)
- [Agent Skills Specification](https://agentskills.io/specification)
