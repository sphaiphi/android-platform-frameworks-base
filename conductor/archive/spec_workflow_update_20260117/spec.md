# Specification: Spec-Driven Workflow Update

## Overview
Update the `conductor/workflow.md` to formally define the workflow for implementing features based on C++ specifications located in `core/cpp/specs`. This workflow integrates strict TDD for unit tests with a post-implementation validation phase using CTS tests derived from Java references.

## Functional Requirements

### 1. Workflow Documentation Update
Modify `conductor/workflow.md` to include a specific branching or sub-process for "Spec-Driven Tasks".

### 2. Process Steps
The workflow for these tasks must be defined as follows:

1.  **Spec Analysis & Update:**
    -   Locate the relevant spec file in `core/cpp/specs`.
    -   Read and update the spec file by answering any open questions or filling in implementation details.

2.  **Unit Testing (TDD):**
    -   Write failing unit tests based on the updated specification *before* implementation (standard TDD Red phase).

3.  **Implementation:**
    -   Implement the C++ code to satisfy the spec and pass the unit tests (Green phase).

4.  **CTS Validation:**
    -   After implementation, write/port Android Compatibility Test Suite (CTS) tests.
    -   Reference `cts/java/tests` for expected behavior and test cases.
    -   Ensure these tests pass to validate compliance.

### 3. Integration
-   This workflow should be integrated into the "Standard Task Workflow" section, likely as a conditional path or specific instruction set for features with associated specs.

## Non-Functional Requirements
-   Clarity: The instructions must be unambiguous for the AI agent or developer following them.
-   Consistency: Terminology should match existing Conductor definitions.
