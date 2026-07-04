---
name: spec-kit
description: >
  Guide users through Spec-Driven Development (SDD) using the github/spec-kit toolkit. Use this skill
  whenever a user mentions spec-kit, spec-driven development, specifying features before coding, the
  `specify` CLI, `/speckit-*` slash commands, or wants to structure AI-assisted software development
  with upfront specifications. Also trigger when a user says things like "I want to plan my feature
  before implementing", "help me write a spec for my project", "set up a new project with an AI
  coding agent", or "how do I use spec-kit". This skill covers the full SDD workflow: project
  initialization, constitution, specification, clarification, planning, task breakdown, and
  implementation.
---

# Spec-Kit: Spec-Driven Development Skill

Spec-Kit is an open-source toolkit from GitHub that enables **Spec-Driven Development (SDD)** — a
methodology where specifications become the primary artifact, directly driving implementation through
an AI coding agent rather than being discarded after the "real" coding begins.

## Core Workflow (7 Steps)

Walk the user through these phases in order. Each step has a corresponding slash command in their
AI coding agent after `specify init` is run.

```
Constitution → Specify → Clarify → Plan → Analyze → Tasks → Implement
```

---

## Pipeline Orchestration

The pipeline is orchestrated by a **calling agent** — an AI agent that spawns each skill as a subagent in sequence, checks gate conditions between phases, and passes context forward. No external workflow engine is required.

### Orchestrator responsibilities

The calling agent:
1. Spawns each skill subagent from `agents/` in pipeline order
2. Passes the output path of each phase as an input to the next
3. Enforces three gate conditions before advancing:
   - **post-clarify** — pauses for human review of `clarifications.md` and updated `spec.md`
   - **post-analyze** — reads `analysis.md`; advances on APPROVED or APPROVED WITH CONDITIONS, halts on BLOCKED
   - **post-implement** — pauses for human to verify the running app before marking done
4. Logs progress so the pipeline can resume after interruption

### Pipeline sequence

```
speckit.constitution   →  .specify/memory/constitution.md
speckit.specify        →  spec.md
speckit.clarify        →  clarifications.md  [GATE: human review]
speckit.plan           →  plan.md, data-model.md, contracts/, research.md, quickstart.md
speckit.checklist      →  checklist.md
speckit.analyze        →  analysis.md        [GATE: agent-evaluated — BLOCKED halts]
speckit.tasks          →  tasks.md
speckit.design       →  design.md        [GATE: human review]
speckit.implement      →  codebase           [GATE: human review of running app]
speckit.evolve         →  evolve/candidates.md (scan), then per-task
```

### Subagent inputs

Each agent's `## Inputs` section defines what the orchestrator must pass. Core paths follow a consistent pattern:

```
constitution_path  =  .specify/memory/constitution.md
spec_path          =  .specify/specs/<feature-id>/spec.md
plan_path          =  .specify/specs/<feature-id>/plan.md
data_model_path    =  .specify/specs/<feature-id>/data-model.md
contracts_dir      =  .specify/specs/<feature-id>/contracts/
tasks_path         =  .specify/specs/<feature-id>/tasks.md
thinking_path      =  .specify/specs/<feature-id>/thinking.md
output_path        =  .specify/specs/<feature-id>/<artifact>.md
```

`feature-id` is auto-assigned by spec-kit when `speckit-specify` runs (e.g. `001-task-management`).

---

## Step 1: Constitution 

**Purpose:** Define the project's non-negotiable principles and governance rules that all future
decisions must align with.

**Key guidance:**
- Run this *first*, before any spec or plan
- Results in `.specify/memory/constitution.md`
- Focus on: code quality standards, testing requirements, UX consistency, performance budgets,
  tech stack constraints, architectural patterns

**Subagent:** spawn the `@agents-speckit-constitution.md` subagent with these parameters:
- `output_path`: `.specify/memory/constitution.md`
- `project_description` *(optional)*: brief description of the project, domain, team, and users
- `existing_codebase` *(optional)*: path or description of existing code to extract conventions from
- `interview_mode` *(optional)*: `true` to have the agent ask structured questions before writing
- `draft_path` *(optional)*: path to an existing draft to refine rather than start from scratch

The agent identifies which of 11 risk areas (code quality, testing, security, performance, accessibility, data integrity, dependency management, API stability, error handling, observability, AI agent guidance) apply to the project, then writes 1–3 numbered, citable principles per area — each with scope, rule, rationale, a concrete violation example, and exceptions. It closes with a Governance section that tells AI agents how to use the constitution in downstream phases. After writing, run `/speckit-checklist target:constitution` to validate principle quality.

**Example prompt:**
```
/speckit-constitution Create principles focused on code quality, test coverage requirements,
user experience consistency, and performance targets. Include guidance on how principles
should govern technical decisions.
```

---

## Step 2: Specify 

**Purpose:** Capture *what* you want to build and *why*, expressed as user stories and
functional requirements.

**Key guidance:**
- Focus on the **what and why**, NOT the tech stack
- Be explicit about behavior, user roles, edge cases, constraints
- This creates `specs/<feature-id>/spec.md` on a new git branch (e.g. `001-feature-name`)
- Don't worry about perfection — clarification comes next

**Subagent:** spawn the `@agents-speckit-specify.md` subagent with these parameters:
- `feature_description`: the user's raw idea
- `constitution_path`: `.specify/memory/constitution.md` (if it exists)
- `output_path`: `.specify/specs/<feature-id>/spec.md`
- `feature_id`: auto-assigned slug, e.g. `001-feature-name`

**Example prompt:**
```
/speckit-specify Build a task management app where teams can create projects, assign tasks,
move cards in Kanban-style boards (To Do, In Progress, In Review, Done), leave comments,
and see their own cards highlighted differently.
```

---

## Step 3: Clarify 

**Purpose:** Identify and fill gaps in the spec before committing to a technical plan.

**Key guidance:**
- Run this *before* `/speckit-plan` to reduce rework
- Generates structured questions based on the spec; answers are recorded in a Clarifications section
- Can skip if doing a quick spike or exploratory prototype (tell the agent explicitly)
- After clarification, ask the agent to validate the **Review & Acceptance Checklist** in the spec

**Subagent:** spawn the `@agents-speckit-clarify.md` subagent with these parameters:
- `spec_path`: `.specify/specs/<feature-id>/spec.md`
- `constitution_path`: `.specify/memory/constitution.md` (if it exists)
- `output_path`: `.specify/specs/<feature-id>/clarifications.md`
- `answers` *(optional)*: pass when re-running after the user has answered questions, to apply answers back into the spec

The agent produces a prioritized `clarifications.md` (🔴 Blocking / 🟡 Important / 🟢 Nice-to-know). When called a second time with answers, it edits `spec.md` in place and logs all changes.

**Validation prompt:**
```
Read the review and acceptance checklist, and check off each item if the feature spec meets
the criteria. Leave unchecked items that don't pass.
```

---

## Step 4: Plan 

**Purpose:** Define the technical implementation — stack, architecture, APIs, data models.

**Key guidance:**
- Now is the time to specify the tech stack
- Output includes: `plan.md`, `data-model.md`, `research.md`, API contracts, quickstart guides
- Review `research.md` to confirm the right tech stack and versions are used
- Ask the agent to research rapidly-changing dependencies (e.g. .NET Aspire, JS frameworks)
- Push back on over-engineering — cross-check the constitution

**Example prompt:**
```
/speckit.plan Use Next.js 14 with a PostgreSQL database, Prisma ORM, REST API for tasks
and projects, and deploy to Vercel. Prioritize minimal external dependencies.
```

**Subagent:** spawn the `@agents-speckit-plan.md` subagent with these parameters:
- `spec_path`: `.specify/specs/<feature-id>/spec.md`
- `constitution_path`: `.specify/memory/constitution.md` (if it exists)
- `output_dir`: `.specify/specs/<feature-id>/`
- `tech_preferences` *(optional)*: user-specified stack (e.g. "Next.js 14, PostgreSQL, Prisma, Vercel")
- `existing_codebase` *(optional)*: description or path of existing code the feature must integrate with

The agent produces: `plan.md`, `data-model.md`, `research.md`, `quickstart.md`, and `contracts/` — then traces every functional requirement from the spec to a layer in the plan to confirm nothing was missed.

**After planning**, ask the agent to audit the plan for gaps and missing sequences.

---

## Step 5: Analyze (optional but recommended)

**Purpose:** Cross-artifact consistency check — confirms spec, plan, data model, contracts, and tasks are all mutually consistent before a single line of code is written.

**When to use:** After `/speckit-tasks` and before `/speckit-implement`.

**Subagent:** spawn the `@agents-speckit-analyze.md` subagent with these parameters:
- `spec_path`: `.specify/specs/<feature-id>/spec.md`
- `plan_path`: `.specify/specs/<feature-id>/plan.md`
- `data_model_path`: `.specify/specs/<feature-id>/data-model.md`
- `contracts_dir`: `.specify/specs/<feature-id>/contracts/`
- `tasks_path`: `.specify/specs/<feature-id>/tasks.md`
- `constitution_path`: `.specify/memory/constitution.md` (if it exists)
- `output_path`: `.specify/specs/<feature-id>/analysis.md`
- `research_path` *(optional)*: `.specify/specs/<feature-id>/research.md`

The agent runs eight check categories across every artifact pair (spec↔plan, spec↔data model, plan↔contracts, contracts↔data model, tasks↔everything), then issues a three-level verdict: **APPROVED**, **APPROVED WITH CONDITIONS**, or **BLOCKED**. Only an APPROVED or APPROVED WITH CONDITIONS report should proceed to `/speckit-implement`.

---

## Step 6: Tasks 

**Purpose:** Generate an actionable, ordered task list from the implementation plan.

```
/speckit-tasks
```

Output (`tasks.md`) includes:
- Tasks grouped by user story / implementation phase
- Dependency ordering (models → services → endpoints → UI)
- `[P]` markers for tasks that can run in parallel
- Exact file paths for each task
- TDD structure (tests before implementation)
- Checkpoint validations per phase

**Subagent:** spawn the `@agents-speckit-tasks.md` subagent with these parameters:
- `plan_path`: `.specify/specs/<feature-id>/plan.md`
- `spec_path`: `.specify/specs/<feature-id>/spec.md`
- `data_model_path`: `.specify/specs/<feature-id>/data-model.md`
- `contracts_dir`: `.specify/specs/<feature-id>/contracts/`
- `constitution_path`: `.specify/memory/constitution.md` (if it exists)
- `output_path`: `.specify/specs/<feature-id>/tasks.md`
- `existing_codebase` *(optional)*: description of existing patterns to conform to

The agent sweeps all plan artifacts, sequences tasks by dependency, marks parallelisable work with `[P]`, inserts checkpoint gates between phases, then runs a coverage check to confirm every spec acceptance criterion and every plan layer has at least one task.

---

## Step 6.5: Implementation Design 

**Purpose:** Design the implementation — the detailed structural design that bridges `plan.md` (architecture by name) and `tasks.md` (decomposed work) with the actual code. Produces `design.md`: a design document the implement agent reads as a blueprint.

**When to use:** After `tasks` and before `implement`. The orchestrating agent spawns this between tasks and implement.

**What it is not:** Re-architecture (`plan.md`'s job). Task decomposition (`tasks.md`'s job). Execution planning (ordering, risk mitigation). It is design: *what the implementation looks like* — component shapes, typed interfaces, data flows, behavioural contracts, structural organisation.

**Subagent:** `@agents-speckit-design.md`

**Parameters:**
- `tasks_path`, `plan_path`, `spec_path`, `data_model_path`, `contracts_dir`, `constitution_path`
- `output_path`: `.specify/specs/<feature-id>/design.md`
- `existing_codebase` *(optional)*

**Nine design lenses:**

1. **Component design** — typed public interfaces for every component (service, repository, controller, hook); responsibility boundary; lifecycle; what each component explicitly never does
2. **Data flow design** — typed pipeline for each user action from entry to response; every transformation point; null/missing value handling at each boundary
3. **Interface design** — contracts between components: preconditions, postconditions, error types; who owns each interface (consumer defines, producer implements); full error type hierarchy
4. **Structural design** — annotated file/module tree; import direction rules per component; what each file exports and must never import
5. **State & behaviour design** — complete state machine with guards and side effects; behavioural scenarios (Given/When/Then) for every spec acceptance criterion
6. **Dependency design** — dependency table with direction rules; any cycles or layer violations redesigned before reaching the implement agent
7. **Design pattern application** — concrete instantiation of each plan-named pattern (not textbook definition); test doubles; deviation notices if the application differs from the plan's implication
8. **Design trade-offs** — for 3–5 consequential decisions: options considered, chosen design, rationale derived from constitution and plan
9. **Extension design** — anticipated future changes (from spec non-goals), how the current design accommodates them, what design choice would make them expensive

**Output:** `design.md` — a design document the implement agent treats as a blueprint. Every section answers "what does it look like?" not "what do you do first?".

---

## Step 7: Implement 

**Purpose:** Execute the task list to build the feature.

```
/speckit-implement
```

The agent will:
1. Validate all prerequisites (constitution, spec, plan, tasks)
2. Parse `tasks.md` and execute in dependency order
3. Apply TDD as defined in the task plan
4. Report progress and handle errors

**Subagent:** spawn the `@agents-speckit-implement.md` subagent with these parameters:
- `tasks_path`: `.specify/specs/<feature-id>/tasks.md`
- `plan_path`: `.specify/specs/<feature-id>/plan.md`
- `spec_path`: `.specify/specs/<feature-id>/spec.md`
- `data_model_path`: `.specify/specs/<feature-id>/data-model.md`
- `contracts_dir`: `.specify/specs/<feature-id>/contracts/`
- `quickstart_path`: `.specify/specs/<feature-id>/quickstart.md`
- `constitution_path`: `.specify/memory/constitution.md` (if it exists)
- `codebase_root`: root of the codebase (usually `.`)
- `resume_from` *(optional)*: task ID to resume from after an interruption (e.g. `T-07`)

The agent maintains a `tasks.md.progress` log throughout execution — checkpoints, per-task acceptance criteria results, and blocker reports — enabling safe resumption if interrupted. It halts and surfaces a structured blocker report rather than silently working around plan-level gaps.

**After implementation:** Test the running app; paste any browser console errors back to the agent.

---

## Optional Commands

| Command | Purpose |
|---|---|
| `/speckit-checklist` | Run "unit tests for English" — structured pass/fail quality checks against any single artifact |
| `/speckit-clarify` | Can be run at any time to re-examine underspecified areas |
| `/speckit-analyze` | Run after tasks, before implement, for cross-artifact consistency audit |
| `/speckit-evolve` | Bridge spec-kit with OpenEvolve for evolutionary optimization of algorithmic tasks |

**Subagent for `/speckit-checklist`:** Spawn `@agents-speckit-checklist.md` with:
- `target`: which artifact to check — `spec`, `plan`, `data-model`, `tasks`, `constitution`, or `all`
- `feature_dir`: `.specify/specs/<feature-id>/`
- `constitution_path`: `.specify/memory/constitution.md` (if it exists)
- `output_path`: `.specify/specs/<feature-id>/checklist.md`
- `strict` *(optional)*: `true` to treat warnings as failures (recommended before handing off to a reviewer or next phase)

The agent runs every check in its library for the target artifact and produces a `checklist.md` with per-check pass/fail results, exact citation of any failure, and a recommended fix for each. Overall verdict: **PASS**, **PASS WITH WARNINGS**, or **FAIL**. Unlike `/speckit-analyze` (cross-artifact consistency), checklist checks the *intrinsic quality* of a single artifact — vague verbs, untestable criteria, missing justifications, orphaned components.

---

## Directory Structure After Full Workflow

```
.specify/
├── memory/
│   └── constitution.md
├── scripts/          # Setup scripts
│   └── bash
│       ├── check-prerequisites.sh
│       ├── common.sh
│       ├── create-new-feature.sh
│       ├── setup-plan.sh
│       └── setup-tasks.sh
├── specs/
│   └── 001-feature-name/
│       ├── spec.md
│       ├── plan.md
│       ├── data-model.md
│       ├── research.md
│       ├── tasks.md
│       ├── quickstart.md
│       ├── design.md
│       └── contracts/
│           ├── api-spec.json
│           └── signalr-spec.md   # if applicable
└── templates/
    ├── spec-template.md
    ├── plan-template.md
    └── tasks-template.md
```

---

## Common Pitfalls & Tips

- **Don't describe the tech stack in `/speckit-specify`** — save that for `/speckit-plan`
- **AI agents can be over-eager** — they may add components you didn't ask for. Always ask for rationale.
- **Research rapidly-changing libraries explicitly** — prompt the agent to look up current versions
- **Multiple research tasks in parallel** — nudge the agent with targeted research prompts, not broad ones
- **Cross-check the constitution** — before implementation, verify the plan adheres to the governing principles
- **Git integration** — the CLI creates branches automatically; use GitHub CLI to open PRs for tracking

---

## Development Phases Supported

| Phase | Use Case |
|---|---|
| 0-to-1 (Greenfield) | Brand new projects built from scratch |
| Creative Exploration | Parallel implementations of the same spec |
| Iterative (Brownfield) | Adding features to existing codebases |

---

## Subagents

The `agents/` directory contains specialized subagents for individual SDD phases. Spawn these
when executing a phase yourself (e.g. in Claude.ai) rather than delegating to the user's
Claude Code agent.

| File | Phase | When to use |
|------|-------|-------------|
| `agents/speckit-constitution.md` | Constitution | Elicit project principles and write a numbered, citable governing constitution |
| `agents/speckit-specify.md` | Specify | Turn a user's raw idea into a structured `spec.md` |
| `agents/speckit-clarify.md` | Clarify | Audit a draft `spec.md` for gaps; apply answers back into the spec |
| `agents/speckit-plan.md` | Plan | Translate the spec into architecture, data model, API contracts, and a developer quickstart |
| `agents/speckit-tasks.md` | Tasks | Decompose the plan into a sequenced, dependency-ordered, checkpoint-gated task list |
| `agents/speckit-design.md` | Design | Implementation design: typed component interfaces, data flow pipelines, interface contracts, file structure, behavioural scenarios, dependency graph, trade-offs |
| `agents/speckit-analyze.md` | Analyze | Cross-artifact consistency audit across all pipeline artifacts; issues APPROVED / BLOCKED verdict before implementation |
| `agents/speckit-checklist.md` | Checklist | Intrinsic quality audit of any single artifact; issues per-check PASS / WARN / FAIL results with exact citations |
| `agents/speckit-evolve.md` | Evolve | Bridge spec-kit with OpenEvolve: scan candidates, generate evaluator + config, integrate evolved output |
| `agents/speckit-implement.md` | Implement | Execute `tasks.md` task-by-task, verify acceptance criteria, maintain a progress log, and surface blockers |

Read the relevant agent file before spawning it to understand required parameters.

## Agents

The orchestrating agent reads each file from `agents/` and spawns it as a subagent.
Each agent file is self-contained: `## Inputs` defines required parameters, `## Skill Invocation`
shows the slash command, and `## Next Step Delegation` shows what to call next.

---

## OpenEvolve Integration 

spec-kit and OpenEvolve are complementary tools for different layers of the stack:

- **spec-kit** handles the full software engineering process: constitution, requirements, architecture, task decomposition, and implementation of structured code (migrations, routing, auth, UI scaffolding). These have no meaningful optimization score — they are correct-by-construction from contracts.
- **OpenEvolve** handles algorithmic components where a measurable score function exists and multiple valid implementations have meaningfully different performance characteristics.

**Subagent:** Spawn `@agents-speckit-evolve.md` in one of four modes:

| Mode | When | What it does |
|------|------|-------------|
| `scan` | After `speckit-tasks` | Scores every task on the Evolution Fitness Test; produces `evolve/candidates.md` |
| `prepare` | Before running OpenEvolve | Generates `initial_program.py`, `evaluator.py`, `config.yaml` from SDD artifacts |
| `integrate` | After OpenEvolve finishes | Wires the best evolved program back into the codebase; writes integration report |
| `full` | For a single known candidate | Runs scan → prepare → integrate in sequence |

**Parameters:**
- `mode`: `scan` / `prepare` / `integrate` / `full`
- `tasks_path`, `spec_path`, `plan_path`, `constitution_path`, `codebase_root`
- `output_dir`: `.specify/specs/<feature-id>/evolve/`
- `task_id` *(prepare / integrate / full)*: the task to evolve
- `evolve_output_dir` *(integrate)*: OpenEvolve's output directory with `checkpoints/`
- `llm_model` : default `inherit`
- `llm_api_base` : default `http://localhost:8000/v1`
- `iterations` *(optional)*: default `200`

**How spec-kit artifacts map to OpenEvolve inputs:**

| spec-kit artifact | OpenEvolve input |
|---|---|
| `constitution.md` principles | `system_message` constraints (MUST NOT / ALLOWED) |
| Task acceptance criteria | `evaluator.py` test cases and metrics |
| Plan performance targets | `feature_dimensions` and evaluator score weights |
| Task function signature | Protected code outside `EVOLVE-BLOCK` markers |
| Plan stack decisions | Import constraints in `initial_program.py` |


---

## Environment Variables

| Variable | Description |
|---|---|
| `SPECIFY_FEATURE` | Override feature detection for non-Git repos. Set to feature directory name (e.g. `001-photo-albums`). Must be set in agent context before `/speckit-plan`. |
| `GH_TOKEN` or `GITHUB_TOKEN` | GitHub token for API requests in corporate environments |

---

## Further Reading

- [github/spec-kit on GitHub](https://github.com/github/spec-kit)
- [Spec-Driven Development methodology](https://github.com/github/spec-kit/blob/main/spec-driven.md)
- [Community walkthroughs](https://github.com/github/spec-kit#-community-walkthroughs)
