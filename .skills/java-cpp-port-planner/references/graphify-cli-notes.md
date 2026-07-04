# Graphify CLI — Verified Behavior & Gotchas

Verified against `graphifyy` 0.8.40 (PyPI). The marketing docs at graphify.net
describe a slightly different/older surface (e.g. a top-level `/graphify
./raw` build command); the installed CLI's actual top-level commands are
below. Re-check with `graphify --help` if behavior seems off — this is an
actively developed single-maintainer tool and flags do shift between
versions.

## Building / refreshing the graph

```bash
graphify update <path>              # AST-only extraction, no LLM call, no API key needed
graphify update <path> --no-cluster # skip Leiden clustering, raw extraction only
graphify update <path> --force      # overwrite even if the rebuild has fewer nodes
                                     # (needed after deleting/renaming files mid-port)
graphify cluster-only <path>        # re-cluster + regenerate report without re-extracting
graphify cluster-only <path> --no-viz  # skip graph.html — flag exists in docs but was
                                        # not directly verified; test before relying on it
```

`update` is the right command for this skill's workflow — it's deterministic
(Tree-sitter AST pass only), costs no tokens, and works identically whether
the graph already exists or not. Run it once before analysis, and again
after each porting session to track progress.

Output lands in `<path>/graphify-out/`: `graph.json` (the queryable graph),
`GRAPH_REPORT.md` (god nodes, communities, knowledge gaps), `graph.html`
(skip with `--no-viz` on large repos).

## Querying

```bash
graphify explain "ClassName"        # reliable for human-readable single-node lookups
graphify query "question" --dfs     # BFS/DFS traversal, good for open-ended exploration
graphify path "A" "B"               # shortest path between two nodes
graphify affected "X" --depth 2     # reverse traversal: what depends on X
```

### Verified limitation: name collisions across the Java/C++ boundary

In a porting repo, the same class name legitimately exists on both sides
(e.g. `Animal` in Java and `Animal` in C++ once ported). Tested directly:

- `graphify affected "Animal"` → `No unique node match for Animal`
- `graphify path "Dog" "Animal"` → ambiguous match warning, then
  `No path found` (it picked the wrong node pair when scores tied)
- `graphify query "what depends on Animal"` → silently returns a BFS that
  mixes nodes from *both* the Java and C++ files, because the keyword
  matcher has no language awareness

**Implication:** don't rely on these three commands for anything where
correctness matters in a porting context. They're fine for `explain` on a
name you know is unique (e.g. a Java-only class with no C++ counterpart
yet), and fine as a human-readable spot-check, but the actual dependency
analysis in this skill is done by `scripts/port_gap_analysis.py` reading
`graph.json` directly and disambiguating by `source_file` path, which is
unambiguous.

### Verified limitation: cross-file symbol resolution is sometimes just a label guess

Inspecting `graph.json` directly: when file A references a class defined in
file B, the edge's target is **not always** the real class node in file B.
Sometimes it's a generic placeholder node with `source_file: ""` that only
matches by label text. The script's `resolve_file()` walks this back to the
real file when the label is unambiguous, and skips the edge rather than
guessing when it isn't.

### Verified limitation: same-package Java references produce no graph edge at all

Java classes in the same package don't need an `import` statement to
reference each other, and in testing, a plain field/parameter reference
between two same-package classes (e.g. `class C { private D d; }`) produced
**no usable cross-file edge** in graphify's own extraction. This is the
majority case in any tightly-coupled module, so the script supplements
graphify's edges with a whole-word class-name scan over the actual source
text — intentionally permissive, since a stray false-positive edge just
makes the suggested port order slightly more conservative (safe failure
direction), whereas a missed edge could suggest porting something before a
real dependency is ready.

## graph.json shape (node-link / D3 format)

```json
{
  "directed": false,
  "nodes": [
    {"label": "Dog", "source_file": "java/.../Dog.java", "id": "...",
     "community": 0, "norm_label": "dog"}
  ],
  "links": [
    {"relation": "inherits", "confidence": "EXTRACTED", "source": "...",
     "target": "...", "confidence_score": 1.0}
  ]
}
```

Relations observed: `contains` (file→type, type→field), `method`
(class→method), `inherits`, `references` (with a `context` like
`parameter_type` / `return_type`), `imports`. Confidence is `EXTRACTED`
(deterministic, AST-derived, 1.0) or `INFERRED`/`AMBIGUOUS` (semantic pass
only — won't appear if you used `update` without an LLM key). `source_file`
is the one field that's reliably populated and unambiguous — prefer it over
label matching whenever possible.

## god nodes & GRAPH_REPORT.md

`GRAPH_REPORT.md`'s "God Nodes" section lists the highest-fan-in
identifiers — these tend to be the riskiest things to port (most call
sites, most behavioral surface area to get exactly right). In the feature
brief, call them out explicitly by name and flag for extra test coverage
rather than grouping them silently with lower-risk files.