# Platform & Tooling Reference

## Android NDK

- Binder IPC mechanisms — the transport underneath most cross-process Android calls.
- JNI integration patterns — reference management, exception propagation across the JNI boundary, thread attachment.
- Android Looper/Handler system for message-loop-driven concurrency.
- `RefBase`-family smart pointers (Android's own reference-counting scheme, distinct from `std::shared_ptr`) — don't assume STL smart pointer semantics apply.
- Hardware abstraction layers and system service communication patterns.

## AOSP-specific

- AOSP codebase conventions and idioms — these often predate or diverge from modern C++23 style; know when to follow local convention vs. when to modernize.
- `libutils`, `libbase` — Android's own foundational libraries, used in place of some STL facilities in older code.
- Binder framework internals, HAL interfaces, HIDL/AIDL for interface definition across process boundaries.

## Linux systems programming

- POSIX APIs as the baseline for portability across Linux/Unix-like systems.
- File descriptors managed via RAII wrappers — never a bare `int` fd without a destructor closing it.
- `epoll`/`select`/`poll` patterns for I/O multiplexing — know the tradeoffs (scalability, portability, ease of use) before picking one.
- Signal handling — async-signal-safety constraints are stricter than normal thread-safety.
- Process/thread management and inter-process communication (pipes, shared memory, sockets).

## Cross-platform concerns

- Compiler differences across GCC, Clang, and MSVC — don't assume a feature or extension is portable without checking.
- Platform abstraction layers to isolate OS-specific code behind a common interface.
- Conditional compilation strategies (`#if`/feature-test macros) kept minimal and centralized rather than scattered.
- CMake as the modern, target-based build system of choice; know Conan/vcpkg for dependency management when the project needs it.

## Common frameworks

- Qt — signals/slots and the meta-object system, when the project is Qt-based.
- Boost, especially ASIO and Beast for networking.
- Abseil for Google-style utility types.
- Google Test / Catch2 for unit testing.
- gRPC / Protocol Buffers for RPC and serialization.

## Build & tooling proficiency

**Must have:** a modern compiler (GCC 13+, Clang 16+, or MSVC 19.36+), CMake 3.25+, a debugger (GDB/LLDB), Git, and one capable IDE.

**Should have:** static analyzers (clang-tidy, cppcheck), sanitizers (ASan, TSan, UBSan), a profiler (perf, Instruments, vtune), a benchmark framework (Google Benchmark), and a test framework (Google Test/Catch2).

**Nice to have:** Compiler Explorer (godbolt.org) for checking generated assembly, Quick Bench for microbenchmark comparisons, C++ Insights for seeing what the compiler actually does with a construct, and Doxygen for generated documentation.

## Version control practice

- Clear Git workflows and branching strategy appropriate to the project's size and release cadence.
- Code review as a first-class step, not a formality.
- Commit message conventions that make history genuinely useful for later archaeology (this project already uses a `spec-kit: <stage>: <summary>` convention for pipeline commits — follow whatever local convention exists).
