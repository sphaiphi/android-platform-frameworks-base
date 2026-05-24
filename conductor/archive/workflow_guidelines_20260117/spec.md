# Specification: Update Workflow with Guideline References

## 1. Overview
Update `conductor/workflow.md` to explicitly link to project-specific guidelines for C++ implementation (`core/cpp/CPP.md`) and Unit Testing (`cts/xUNIT.md`) within the "Standard Task Workflow" section.

## 2. Context
The current workflow describes *what* to do (write tests, implement code) but doesn't point to the specific *how-to* guides available in the repository. Adding these references will ensure developers adhere to the project's C++ safety standards and xUnit testing patterns during the development cycle.

## 3. Goals
1.  **Improve Discoverability:** Ensure developers find the C++ style/safety guidelines (`core/cpp/CPP.md`) right when they need them (during implementation).
2.  **Standardize Testing:** Ensure developers find the xUnit testing patterns (`cts/xUNIT.md`) right when they need them (during test creation).

## 4. Scope
*   **Target File:** `conductor/workflow.md`
*   **Modifications:**
    *   **Step 3 (Write Failing Tests):** Add a sub-bullet or note referencing `cts/xUNIT.md` for guidelines on creating unit tests.
    *   **Step 4 (Implement to Pass Tests):** Add a sub-bullet or note referencing `core/cpp/CPP.md` for guidelines on C++ implementation.

## 5. Out of Scope
*   Modifying the content of `core/cpp/CPP.md` or `cts/xUNIT.md`.
*   Changing the logical flow of the Standard Task Workflow.
