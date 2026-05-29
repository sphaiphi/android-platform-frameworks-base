---
name: android-docs
description: >
  Find, search, and retrieve Android documentation and knowledge base articles using the
  Android CLI `android docs` command. Use this skill whenever an Android developer agent
  needs to look up Android APIs, best practices, guides, architecture patterns, Jetpack
  libraries, Compose, platform framework subsystems, hidden APIs, permissions, or any other Android topic.
  Trigger this skill any time the user asks "how do I…", "what is the Android way to…",
  "find the docs for…", "look up Android…", or whenever the agent needs authoritative Android
  guidance and system library specifications before writing code or making recommendations.
  Always prefer this over guessing — official Android Knowledge Base content is the source of truth.
license: Apache-2.0
metadata:
  author: "Android System Programming Expert"
  version: "1.3.0"
requirements:
  executables:
    - android
allowed-tools:
  - execute_bash
---

# Android Docs Skill

Retrieve official Android documentation and system framework guidelines using the native `android docs` CLI commands. This is a two-step workflow: **search** to find relevant knowledge base URLs, then **fetch** to retrieve the full content.

Do not rely entirely on pre-trained parametric knowledge for API signatures, deprecation policies, or architecture constraints—especially regarding modern features or platform framework internal mechanisms.

---

## When to Use This Skill

Use `android docs` whenever you need authoritative Android information, including:

- **System & Platform Development:** Hidden/restricted platform policies (`@hide`, `@SystemApi`), AIDL/Binder IPC mechanisms, and custom system services.
- **API Usage:** Activity, Fragment, ViewModel, Flow, Coroutines, WorkManager, Room, etc.
- **Jetpack Compose:** Layout patterns, state management, and edge-to-edge configurations.
- **Architecture Guidance:** MVVM, MVI, Clean Architecture, and modular framework design.
- **Performance & Security:** Battery and memory optimization, platform permissions, and sandbox constraints.
- **Build System:** Gradle, Android Gradle Plugin (AGP), and Kotlin DSL configurations.

---

## Workflow

### Step 1 — Search the Index
Execute the search command directly via your allowed terminal execution tool. Write the query as a **natural language question or specific topic phrase**.

```bash
android docs search '<your query>'

```

* Good Queries:*

```bash
android docs search 'How do I observe LiveData in Compose?'
android docs search 'android.app.Service background execution limits'
android docs search 'Predictive back gesture navigation'
android docs search 'Room database migration strategy'
android docs search 'edge-to-edge window insets Compose'

```

* Poor Queries (Too vague — refine these):*

```bash
android docs search 'android'          # too broad
android docs search 'how to code'      # not specific

```

### Step 2 — Fetch Document Payload

Take any `kb://` URL returned from the search results and fetch its complete, explicit article payload to extract the exact implementation logic:

```bash
android docs fetch kb://android/topic/performance/overview
android docs fetch kb://android/guide/components/activities/intro-activities
android docs fetch kb://android/jetpack/compose/state

```

The fetched content is printed to stdout. Read it in full before responding or writing code — it is authoritative and may contain caveats, deprecation notices, or system-level restrictions that override your prior knowledge.

---

## Decision Tree

```
Agent needs Android guidance
        │
        ▼
Is the exact API / pattern well-established in your context?
   YES → still run docs search to confirm it's current
   NO  → run docs search immediately
        │
        ▼
Search returns kb:// URLs?
   YES → fetch the most relevant one(s);支 synthesize answer
   NO  → broaden the query (see Troubleshooting below)
        │
        ▼
Fetched article answers the question?
   YES → use it; cite the kb:// URL in your response
   NO  → search with alternate phrasing or related topic

```

---

## Multi-Step Research Pattern

For complex problems spanning multiple domains (e.g., system services combined with Jetpack components), search and fetch in sequence:

```bash
# Example: "How should I handle background sync with network constraints?"

android docs search 'WorkManager network constraints background sync'
# → finds kb://android/topic/libraries/architecture/workmanager/how-to/constraints

android docs fetch kb://android/topic/libraries/architecture/workmanager/how-to/constraints
# → read full article

android docs search 'ConnectivityManager network callback'
# → supplementary API reference

android docs fetch kb://android/reference/android/net/ConnectivityManager.NetworkCallback
# → read and combine with WorkManager guidance

```

---

## Citing Sources

Always include the explicit `kb://` URL when generating documentation-derived answers or codeblocks:

> "According to the Android Knowledge Base (`kb://android/jetpack/compose/state`), state should be hoisted to the lowest common ancestor that needs to read or write it."

This lets the user cleanly verify and explore your changes downstream.

---

## Troubleshooting

| Symptom | Fix |
| --- | --- |
| `command not found: android` | Host environment lacks the toolchain. Invoke `android init` or verify PATH before proceeding. |
| No results returned | Broaden the query; try synonyms (`"viewmodel"` → `"architecture components"`). |
| Results are off-topic | Add more context flags (`"compose"`, `"jetpack"`, `"platform"`). |
| Fetched article is outdated | Cross-check with `android docs search '<topic> latest'`. |
| `kb://` URL returns 404 | Try searching again; the URL structural layout may have changed. |
| Uncertain which result to fetch | Fetch the top 2–3 responses and synthesize. |
| Empty Index Match | If a search returns nothing, explicitly notify the user before using standard codebase templates. |

---

## Quick Reference — Common kb:// Path Patterns

These patterns appear frequently; use them to guess or refine a URL when search returns a close but not exact match:

```
kb://android/topic/performance/overview
kb://android/topic/architecture/intro
kb://android/guide/components/activities/intro-activities
kb://android/guide/topics/permissions/overview
kb://android/jetpack/compose/state
kb://android/jetpack/compose/side-effects
kb://android/training/data-storage/room
kb://android/topic/libraries/architecture/workmanager
kb://android/topic/libraries/architecture/viewmodel
kb://android/training/multiscreen/adaptui
kb://android/guide/app-bundle

```

*Note: These are directional hints—always prioritize live verification via `android docs search` first.*

---

## Notes

* Both commands (`search` and `fetch`) are completely read-only and safe to execute in any sandbox environment—they make no active mutations to the codebase filesystem.
* If the toolchain is altogether missing, guide the operator to download the tools directly via `https://developer.android.com/tools/agents`.



