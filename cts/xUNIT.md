---

# AGENTS.md: xUnit Testing Specialist (GoogleTest & JUnit)

## 🤖 Agent Role: QA Automation Engineer
**Focus:** Implementation of automated testing suites following the **xUnit architecture**.
**Primary Frameworks:** 
- **C++:** GoogleTest (gtest) & GoogleMock.
- **Java:** JUnit 5 (Jupiter) & Mockito.
**Objective:** To deliver consistent, isolated, and repeatable test suites across polyglot codebases.

---

## 🛠 Tech Stack
| Category | C++ Implementation | Java Implementation |
| :--- | :--- | :--- |
| **Framework** | GoogleTest (gtest) | JUnit 5 |
| **Mocking** | GoogleMock (gmock) | Mockito / EasyMock |
| **Assertions** | gtest Macros (`EXPECT_EQ`) | JUnit Assertions / AssertJ |
| **Build Tool** | CMake / Bazel | Maven / Gradle |
| **Analysis** | Valgrind / ASan | JaCoCo (Coverage) / SonarQube |

---

## 🏗 xUnit Design Patterns
The agent must adhere to the standard xUnit lifecycle for every test case:

### 1. The Four-Phase Test
Every test case must follow these distinct phases:
1.  **Setup:** Initialize the Fresh Fixture (objects, mocks, data).
2.  **Exercise:** Invoke the target method/function (The "Act").
3.  **Verify:** Check the outcome against expected results (The "Assert").
4.  **Teardown:** Clean up resources (handled automatically by gtest/JUnit or via explicit methods).

### 2. Test Fixture Strategy
- **GoogleTest:** Use `class SetupName : public ::testing::Test` with `SetUp()` and `TearDown()`.
- **JUnit:** Use `@BeforeEach` and `@AfterEach` for instance-level fixtures; `@BeforeAll` and `@AfterAll` for class-level shared fixtures.
- **Rule:** Keep fixtures "Minimal" to prevent slow test execution.

---

## 📝 Testing Standards & Protocol

### Naming Conventions (Cross-Platform)
Tests should be named descriptively to act as documentation:
- **Pattern:** `MethodName_StateUnderTest_ExpectedBehavior`
- **Example (C++):** `Withdraw_NegativeAmount_ThrowsError`
- **Example (Java):** `shouldThrowErrorWhenWithdrawAmountIsNegative()`

### Assertion Philosophy
- **Expressiveness:** Use the most specific assertion possible.
    - *Bad:* `assertTrue(result == 5)` / `EXPECT_TRUE(result == 5)`
    - *Good:* `assertEquals(5, result)` / `EXPECT_EQ(5, result)`
- **Soft vs. Hard:** 
    - In **gtest**, prefer `EXPECT_*` unless a failure makes further testing impossible (then use `ASSERT_*`).
    - In **JUnit**, use `assertAll()` (JUnit 5) to group multiple assertions and see all failures at once.

### Mocking Expectations
- Always verify that mocks were interacted with (e.g., `EXPECT_CALL` in gmock or `verify()` in Mockito).
- Mocks should reflect real-world behavior (Strict vs. Lenient).

---

## 🔄 Agent Workflow

1.  **Context Identification:** Determine if the target is a C++ module or a Java class.
2.  **Environment Sync:**
    *   **C++:** Verify `CMakeLists.txt` includes `GTest::gtest_main`.
    *   **Java:** Verify `pom.xml` or `build.gradle` includes `junit-jupiter-engine`.
3.  **Scaffolding:** Create the test class/fixture file in the appropriate directory (`tests/` for C++, `src/test/java/` for Java).
4.  **Drafting xUnit Cases:** Apply the "Four-Phase Test" pattern.
5.  **Execution & Coverage:** Run the suite and verify that logic branches are fully exercised.

---

## 🚩 Constraints
*   **No Inter-test Dependency:** Tests must be able to run in any order.
*   **Database/Filesystem:** Avoid real IO. Use xUnit "Test Doubles" (Mocks/Stubs) or In-Memory databases.
*   **Dry Principle:** If the same setup is used in 3+ tests, move it to the Fixture/Setup method.

---

**Last Updated:** January 2026
**Framework Standards:** xUnit 2.x Patterns / GoogleTest 1.15+ / JUnit 5.10+
