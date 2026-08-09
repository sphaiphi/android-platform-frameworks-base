---
name: java-cpp-port-planner
description: >
  Figures out what to port next when migrating a Java codebase to C++ in a repository
  with Graphify (the knowledge-graph CLI, `graphify`/`graphifyy`) installed or
  installable. Identifies every porting gap, surfaces the top 3 highest-priority
  features to implement first, asks clarifying questions if the analysis can't give a
  confident top 3, has the user pick one, then writes a feature brief for just that
  file — shaped for spec-kit's `/speckit.specify` step, though this skill never calls
  that command itself. Use whenever the user asks what Java code is left to port,
  what to implement next in a Java-to-C++ migration, wants a porting priority list,
  mentions porting/migrating/translating Java to C++ with Graphify, or wants
  leaf/foundation classes ported before their dependents. Trigger on "what should I
  port next", "top priorities for the C++ port", "is X already ported", or "what are
  the porting gaps" in a mixed Java/C++ repo.
---

# Java → C++ Port Planner

Analyzes a repository mid-migration from Java to C++, using a Graphify knowledge graph
of the codebase as the source of structural truth, and helps decide what to port next.
The flow has three parts: identify every gap, surface the top 3 highest-priority
candidates and get the user to pick one, then write a **feature brief** for just that
one file — in a shape suitable as input to spec-kit's `/speckit.specify` step. This
skill does not invoke `/speckit.specify` itself, does not write a `spec.md` or a
`tasks.md`, and does not produce a brief covering the whole backlog — only the single
feature the user selects.

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
- `god_nodes_hint` — highest-fan-in identifiers from `GRAPH_REPORT.md`; call these out
  explicitly if they show up as a candidate, since they carry the most behavioral
  surface area to get right (see `is_god_node` below)
- `top3_priority_candidates` — the top 3 tier-0 (immediately portable, no remaining
  unported dependencies) files, ranked by how many other not-yet-ported files each one
  unblocks; each entry is annotated `is_god_node`
- `top3_ambiguous` / `top3_ambiguous_reason` — `true` when the ranking has a tie at
  the cutoff or too few tier-0 candidates to fill 3 slots confidently; this is the
  signal to ask the user instead of presenting a guessed top 3 (see Step 3)

### Step 3 — Present the top 3 and get the user's pick

Show `top3_priority_candidates` to the user with the `unblocks_count` and
`is_god_node` for each, so the reasoning is visible, not just the file names. Frame it
as a recommendation, not a done deal — the user picks which one to actually spec out.

**If `top3_ambiguous` is `true`, do not present a guessed top 3.** Explain the
`top3_ambiguous_reason` in plain terms and ask the user directly instead:

- Too few tier-0 candidates (fewer than 3 files are currently unblocked) → tell the
  user how many there actually are and ask if they want to proceed with that smaller
  set, or want tier-1 files considered too.
- A tie at the cutoff (several files unblock the same number of others) → list the
  tied files and ask the user to break the tie themselves (they may know which one
  matters more for reasons the graph can't see, like an upcoming deadline or a
  teammate already mid-way through one of them).
- No tier-0 files at all (everything remaining is blocked or in a cycle) → say so
  plainly; the useful next step is probably resolving a cycle (see
  `unresolved_cycle_files` in Step 2), not picking a "top 3."

Either way, wait for the user's explicit selection of **one** file before moving on —
don't default to the highest-ranked candidate on their behalf.

### Step 4 — Write the feature brief for the selected file only

Once the user has picked one file, write a brief scoped to **that file alone** — not
the whole backlog, not the other two candidates from the top 3. If the file is a
member of `needs_review_fuzzy_matches` or `partially_ported`, resolve that first (look
at both files, or use `graphify explain "<ClassName>"` per
`references/graphify-cli-notes.md`) so the brief describes a real gap, not a
false-positive.

This is written as a **feature description**, not a `spec.md` or a `tasks.md` — it's
meant to be handed to a spec-writing step by the user afterward, but this skill does
not invoke any such step itself; producing the brief is the last thing this skill
does. Concrete class and file names are fine to include — they're the actual domain
content of this feature. What to leave out: implementation structure (build target
layout, exact type signatures, header/impl split mechanics) — describe *what* must
end up true, not *how* the C++ should be structured to get there.

```markdown
# Feature Brief: Port `<JavaFile>` to C++

**Source graph:** <repo_root>/graphify-out/graph.json
**Generated:** <date>
**Why this one:** unblocks <unblocks_count> other not-yet-ported file(s)<, flagged as
a god node — high fan-in, treat with extra care, if is_god_node>

## What this feature is

Port `<JavaFile>.java` to C++, preserving behavior: <one paragraph on what the class
does, its public methods/fields, and its role in the codebase>.

## Dependencies

<Either "No remaining unported dependencies — safe to start immediately." if tier 0,
or the specific not-yet-ported files it depends on and their status, if the user chose
outside the top 3.>

## What depends on this

<Files (from `depends_on` reverse lookup / `unblocks_count`) that will become
unblocked once this is done — useful context for why it was prioritized.>

## Open questions for the spec (don't resolve these yourself — surface them)

<Only if relevant to this specific file: a needs_review naming ambiguity that had to
be resolved, a cycle this file participates in, or anything else uncertain.>

## Things to preserve

- Behavior parity with `<JavaFile>.java` — same public methods, same observable
  results.
- <If is_god_node: high fan-in, most call sites depend on getting this right — flag
  for extra test coverage.>

## Out of scope for this feature

- Every other file in the repo, ported or not — this brief covers `<JavaFile>` only.
```

Save it as `PORT_FEATURE_BRIEF_<JavaFile>.md` at the repo root. This skill's job ends
here — it does not invoke `/speckit.specify` or any other downstream command, and does
not assume what the user will do with the brief next.

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
- `is_god_node` is advisory, not a filter — god nodes are NOT excluded from
  `top3_priority_candidates`. Tested directly: in a small repo, GRAPH_REPORT.md's
  "God Nodes" section is just every node sorted by edge count with no visible
  risk-based cutoff, so excluding them would remove most or all tier-0 candidates in
  a small repo. Surface the flag to the user; don't treat it as disqualifying.
