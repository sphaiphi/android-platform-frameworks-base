---
name: java-cpp-port-planner
description: >
  Figures out what to port next when migrating a Java codebase to C++ in a repository
  that has Graphify (the knowledge-graph CLI, `graphify`/`graphifyy`) installed or
  installable. Use this skill whenever the user asks what Java code is left to port,
  what to implement next in a Java-to-C++ migration, wants a porting backlog or
  priority order, mentions porting/migrating/translating Java to C++ alongside
  Graphify, or wants the leaf/foundation classes ported before classes that depend
  on them. Also trigger on phrases like "what should I port next", "dependency order
  for the C++ port", "is X already ported", or "build a porting backlog" in a mixed
  Java/C++ repo. Produces a dependency-ordered feature brief formatted as the
  `feature_description` input for spec-kit's `/speckit-specify` step, rather than a
  single freeform answer or a finished tasks.md.
---

# Java → C++ Port Planner

Analyzes a repository mid-migration from Java to C++ and produces a dependency-ordered
**feature brief** describing what to port next, using a Graphify knowledge graph of
the codebase as the source of structural truth. This skill's only job is to identify
that feature and write it up in the shape spec-kit's `/speckit-specify` expects as its
`feature_description` input — it does not write a `spec.md`, a `tasks.md`, or
anything else; that's `/speckit-specify`'s job, not this skill's.

**Core idea:** classify every Java file as ported / partially ported / not ported (by
matching against existing C++ files), build a dependency graph among the *not yet
ported* files, and topologically tier them so foundation/leaf classes surface first —
the things with no remaining unported dependencies, safe to port right now.

Don't try to do this analysis by eyeballing file names or grepping `extends` by hand —
Graphify's graph plus the bundled script handles cross-file resolution, cycles, and
partial-port detection in one pass and is significantly more reliable than ad hoc
inspection on anything past a handful of files.

## Workflow

### Step 1 — Confirm Graphify is present and the graph is current

```bash
graphify --help        # confirms the CLI is on PATH
```

If it's not installed: `pip install graphifyy --break-system-packages` (package name
has a double-y; the CLI command is just `graphify`).

Build or refresh the graph — this is AST-only, deterministic, costs no LLM tokens, and
is safe to (re)run any time, including right after the user just ported something:

```bash
graphify update <repo_root>
# add --force if files were deleted/renamed since the last graph build
```

This writes `<repo_root>/graphify-out/graph.json` and `GRAPH_REPORT.md`.

### Step 2 — Run the gap analysis script

```bash
python3 scripts/port_gap_analysis.py --graph <repo_root>/graphify-out/graph.json --repo-root <repo_root>
```

This does **not** rely on `graphify query`/`affected`/`path` for the core analysis —
those do fuzzy label matching and were verified to misbehave specifically in this
scenario, because the same class name legitimately exists in both the Java and C++
trees during a port (see `references/graphify-cli-notes.md` for the verified
failure cases). Instead the script reads `graph.json` directly, resolves everything
by unambiguous `source_file` path, and supplements it with a same-project class-name
scan over the actual source (needed because same-package Java references don't
produce a usable cross-file edge in Graphify's own extraction — also verified by
direct testing).

The script's JSON output gives you:

- `ported` — Java files matched to existing C++ files by filename stem
- `partially_ported` — matched, but only a header exists (or only an impl, no header)
- `needs_review_fuzzy_matches` — close-but-not-exact name matches (e.g.
  `FooBarUtil.java` vs `foo_bar_utils.cpp`); never auto-confirmed, always needs a
  judgment call
- `tiers` — not-yet-ported files grouped into dependency tiers; tier 0 has no
  remaining unported dependencies and is portable immediately, tier 1 depends only on
  tier 0, etc. Files in the same tier are independent of each other (parallelizable)
- `unresolved_cycle_files` / `cycles` — files that depend on each other (directly or
  transitively) and can't be linearly ordered; these need a design step (extract an
  interface, forward-declare, split a header) before either side can be finished
- `god_nodes_hint` — highest-fan-in identifiers from `GRAPH_REPORT.md`; treat these as
  their own task, never bundled with something else, since they carry the most
  behavioral surface area to get right

### Step 3 — Resolve the ambiguous cases before writing the feature brief

For every entry in `needs_review_fuzzy_matches`: look at both files (or use
`graphify explain "<ClassName>"` if the name is unique enough to be unambiguous — check
`references/graphify-cli-notes.md` if unsure) and decide: already ported under a
different naming convention (drop it), or a genuine gap (add it to the brief as a
normal not-ported file).

For every entry in `partially_ported`: decide whether finishing the stub is small
enough to fold into one line item ("implement `E.cpp` against the existing `E.h`") or
deserves the same treatment as an unported file.

### Step 4 — Write the feature brief

This is **not** a tasks.md. `/speckit-specify` takes a `feature_description` — "what
the user wants to build" in roughly plain language — and turns it into a proper
`spec.md` with user stories, functional requirements, and acceptance criteria itself.
Handing it a finished task list would do that work for it and bypass the points where
the user gets to weigh in on the result. Concrete class and file names are fine to
include — they're the actual domain content of this feature, the same way a normal
feature description names entities and screens. What to leave out: implementation
structure (build target layout, exact type signatures, header/impl split mechanics)
— describe *what* must end up true, not *how* the C++ should be structured to get
there.

Map the analysis onto the same who/what/constraints/success-conditions framing
`/speckit-specify` itself looks for, so it has to do minimal extra inference:

```markdown
# Feature Brief: Java → C++ Port

**Source graph:** <repo_root>/graphify-out/graph.json
**Generated:** <date>

## What this feature is

Port the remaining Java implementation to C++, file by file, preserving behavior.
<N> of <total> files are already ported; <N> remain.

## Suggested build order (dependency-derived, not a final plan)

Group 1 (no remaining unported dependencies — buildable in any order relative to each
other): `<JavaFile>`, `<JavaFile>` — <one line on what each does>.

Group 2 (depends on Group 1): `<JavaFile>` — depends on `<Group-1-file>` for
<relationship, e.g. "inherits its base behavior">.

(Continue per tier from the script's `tiers` output.)

## Already in progress / needs finishing

- `<Class>`: header exists (`<path>`), implementation does not — needs `<missing
  methods>` implemented to match `<JavaFile>.java`.

## Open questions for the spec (don't resolve these yourself — surface them)

- `<JavaFile>` vs `<cpp_file>`: name-matched at <score>% but <why it's not a clean
  match, e.g. "no header, free function instead of a class member"> — confirm
  whether this counts as done or needs rework.
- `<A>` and `<B>` reference each other directly (dependency cycle) — needs a decision
  on how the C++ side breaks this (forward declaration vs. interface extraction)
  before either can be finished.

## Things to preserve

- Behavior parity with each Java original — same public methods, same observable
  results, for every file listed above.
- <Any god-node classes from `god_nodes_hint`>: high fan-in, most call sites depend on
  getting these right — flag for extra test coverage.

## Out of scope for this feature

- Anything not listed above (already-ported files, confirmed not to need rework)
```

Save it as `PORT_FEATURE_BRIEF.md` at the repo root (it's an input document, not a
spec-kit artifact, so it doesn't belong under `.specify/`). This skill's job ends
here: hand the brief to `/speckit-specify` as its `feature_description` input. In
Claude Code, invoke the slash command and paste or reference the brief's contents:

```
/speckit-specify
feature_description: <contents of PORT_FEATURE_BRIEF.md>
feature_id: <NNN-port-to-cpp>
```

What `/speckit-specify` does with it, and anything past that, isn't this skill's
concern.

### Step 5 — Track progress over time

After each porting session: `graphify update <repo_root>` to refresh the graph, then
re-run the script. Files that were `not_ported` and now have a matching stem move into
`ported` automatically — no manual bookkeeping needed.

## Known limitations (read before debugging surprising output)

See `references/graphify-cli-notes.md` for the full detail, but the short version:

- Don't trust `graphify query`/`affected`/`path` for anything precision-critical here —
  same class names on both sides of the port make their fuzzy matching ambiguous.
  This is exactly why the script reads `graph.json` directly instead.
- The matching between Java and C++ files is by filename stem, which assumes the
  repo's normal convention is "one public class per file, C++ file named after the
  Java class it ports." If the repo doesn't follow that convention, matches will be
  sparse and most files will show up as `needs_review` or `not_ported` even when
  they're actually done — ask the user about their naming convention if the gap looks
  implausibly large.
- Fuzzy matches are suggestions, never auto-confirmed — always resolve them with the
  user or via `graphify explain` before finalizing the feature brief.