---
name: android-docs
description: Use when building, debugging, or refactoring Android system libraries, platform components, or applications. Instructs the agent to consult the local Android CLI Knowledge Base via doc_tool.py as the absolute source of truth to eliminate API hallucination.
license: Apache-2.0
metadata:
  author: "Android System Programming Expert"
  version: "1.0.0"
allowed-tools:
  - run_skill_script
  - execute_bash
---

# Android CLI Docs Source of Truth Skill

You are an expert Android application and system framework engineer. When modifying, implementing, or troubleshooting code within this repository, you must treat the local Android CLI Docs Knowledge Base as your absolute source of truth. Do not rely on pre-trained parametric knowledge for API signatures, deprecation policies, or architecture constraints.

## 1. Concrete Workflow

Follow these steps in absolute order when requested to implement a feature or fix a bug:

1. **Isolate Terms:** Identify the core API classes, Gradle components, or error strings needing resolution.
2. **Search the Docs:** Execute the local Python tool helper to scan the local index for matching `kb://` URIs.
3. **Fetch & Ingest:** Fetch the full content of the relevant `kb://` address. Read its contents to parse exact method signatures, required blocks, and hidden platform constraints (`@hide`, `@SystemApi`).
4. **Implement:** Write or modify the codebase to match the retrieved documentation exactly.

## 2. Command Reference

### Step 1: Search the Index
```bash
python3 scripts/doc_tool.py search "<api_class_or_error_string>"

```

### Step 2: Fetch Document Payload

```bash
python3 scripts/doc_tool.py fetch "kb://<resolved_path>"

```

## 3. Edge Cases & Error Troubleshooting

* **Error: Command Failed / No Output:** If `android cli` or the local python script crashes, invoke `python3 scripts/doc_tool.py status` to check environment configurations.
* **Error: Missing Documentation Path:** If no `kb://` path returns a match for your target feature, fallback gracefully to inspecting the local framework files directly and explicitly alert the user that you are proceeding using structural codebase patterns rather than an index lookup.



