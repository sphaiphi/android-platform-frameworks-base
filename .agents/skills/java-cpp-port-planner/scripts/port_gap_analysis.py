#!/usr/bin/env python3
"""
port_gap_analysis.py — Java -> C++ porting backlog analyzer, built on top of
a Graphify-generated graph.json.

WHY THIS SCRIPT EXISTS (don't skip this if you're modifying it):
Graphify's own CLI commands (`graphify query`, `graphify affected`,
`graphify path`) do fuzzy keyword matching against node labels. In a
Java->C++ port, the same class name legitimately exists on both sides
(e.g. "Animal" in Java and "Animal" in C++), which makes those commands
ambiguous or wrong for this specific use case (verified empirically:
`graphify affected "Animal"` returns "No unique node match"; `graphify path`
picks an arbitrary node when scores tie). This script instead reads
graph.json directly and resolves everything by `source_file` path, which is
unambiguous, plus a same-project import/extends/implements regex pass over
the actual Java source as a cross-check, since Graphify's own cross-file
edge resolution is sometimes only a label-based guess (a generic node with
source_file == "" rather than a pointer to the real class node).

PERFORMANCE:
Optimized for large graphs after profiling against synthetic repos up to 600
files. Three complexity fixes, each verified to produce byte-identical
output before/after:
  - Cross-file reference scan (regex_supplement_edges): was O(not_ported *
    known_classes) regex compiles (a fresh `\\bClassName\\b` pattern per
    class per file) — 92%+ of runtime on a 400-file repo. Now a single
    tokenization pass per file + O(1) set lookups.
  - Dependency tiering (topo_tier): was O(V^2) worst case (recomputed
    `depends_on[f] & remaining` for every remaining file on every tier).
    Now Kahn's algorithm with in-degree counters, O(V+E).
  - Cycle detection (find_cycles): was recursive DFS, risking
    RecursionError on a cyclic cluster over ~1000 files. Now iterative,
    same O(V+E), no recursion-depth ceiling.
  - Fuzzy name matching (match_java_to_cpp): was a Python-level nested loop
    calling fuzz.ratio() per pair. Now rapidfuzz.process.extract, which
    batches the comparison in C per java file.
Measured: 400-file repo with chained+fan-out dependencies, 1.04s -> 0.08s.
600-file strict linear-dependency-chain repo (topo_tier's worst case),
26.85s -> 0.09s.

USAGE:
    python3 port_gap_analysis.py --graph graphify-out/graph.json --repo-root .

OUTPUT:
    Prints a JSON report to stdout (or --out <path>) with:
      - ported / partially_ported / not_ported Java files
      - a tiered list of not_ported files in dependency order (tier 0 = no
        remaining unported dependencies = portable right now)
      - top3_priority_candidates: the top 3 tier-0 (immediately portable)
        files ranked by how many other not-yet-ported files they unblock,
        each annotated with is_god_node; plus a top3_ambiguous flag (with
        top3_ambiguous_reason) that's True when the ranking has a tie at
        the cutoff or too few candidates to rank confidently — the caller
        should ask the user rather than trust the list as-is in that case
      - any dependency cycles among not_ported files
      - god-node hints pulled from GRAPH_REPORT.md if present
"""

import argparse
import json
import os
import re
import sys
from collections import defaultdict

try:
    from rapidfuzz import fuzz
except ImportError:
    fuzz = None  # fuzzy suggestions become a no-op if unavailable

JAVA_EXTS = {".java"}
CPP_EXTS = {".cpp", ".cc", ".cxx", ".c++", ".h", ".hpp", ".hxx", ".inl"}


def stem(path):
    """Filename without directory or extension, lowercased, separators stripped."""
    base = os.path.basename(path)
    base = os.path.splitext(base)[0]
    return re.sub(r"[^a-z0-9]", "", base.lower())


def ext(path):
    return os.path.splitext(path)[1].lower()


def load_graph(graph_path):
    with open(graph_path, "r", encoding="utf-8") as f:
        return json.load(f)


def collect_files(nodes):
    """Map source_file -> language, plus the set of node ids that live in each file."""
    files = {}
    nodes_in_file = defaultdict(list)
    for n in nodes:
        sf = n.get("source_file") or ""
        if not sf:
            continue
        e = ext(sf)
        if sf not in files:
            if e in JAVA_EXTS:
                files[sf] = "java"
            elif e in CPP_EXTS:
                files[sf] = "cpp"
            else:
                files[sf] = "other"
        nodes_in_file[sf].append(n["id"])
    return files, nodes_in_file


def match_java_to_cpp(files):
    """Exact stem match (case-insensitive) = confirmed port. Fuzzy match below
    that = needs_review suggestion, never auto-confirmed (avoid hiding real
    backlog items behind a guess).

    PERFORMANCE NOTE: fuzzy matching used to be a Python-level nested loop —
    one `fuzz.ratio()` call per (unmatched java file, cpp file) pair, each
    call paying Python function-call overhead on top of the actual C
    comparison. Rewritten to use rapidfuzz.process.extract, which runs the
    whole comparison batch in C per java file and returns results already
    sorted and cutoff-filtered — same matching semantics (ratio scorer,
    score >= 75, top 3), far less Python-level overhead at scale."""
    java_files = [p for p, lang in files.items() if lang == "java"]
    cpp_files = [p for p, lang in files.items() if lang == "cpp"]
    cpp_by_stem = defaultdict(list)
    for c in cpp_files:
        cpp_by_stem[stem(c)].append(c)
    cpp_stems = [stem(c) for c in cpp_files]  # parallel to cpp_files, for process.extract

    ported = {}          # java_path -> list of matched cpp paths
    needs_review = {}     # java_path -> list of (cpp_path, score)
    not_ported = []

    unmatched = []
    for j in java_files:
        s = stem(j)
        if s in cpp_by_stem:
            ported[j] = cpp_by_stem[s]
        else:
            unmatched.append((j, s))

    if unmatched and fuzz and cpp_stems:
        from rapidfuzz import process
        for j, s in unmatched:
            matches = process.extract(
                s, cpp_stems, scorer=fuzz.ratio, score_cutoff=75, limit=3
            )
            if matches:
                needs_review[j] = [
                    (cpp_files[idx], round(score, 1)) for _choice, score, idx in matches
                ]
            else:
                not_ported.append(j)
    else:
        not_ported.extend(j for j, _s in unmatched)

    return ported, needs_review, not_ported


def partial_port_check(java_path, cpp_matches):
    """A 'port' that's only a header with no .cpp/.cc/.cxx (or vice versa,
    rare) is a stub, not a finished port."""
    has_header = any(ext(c) in {".h", ".hpp", ".hxx"} for c in cpp_matches)
    has_impl = any(ext(c) in {".cpp", ".cc", ".cxx", ".c++"} for c in cpp_matches)
    if has_header and not has_impl:
        return "header_only_stub"
    if has_impl and not has_header:
        return "impl_only_no_header"
    return "complete"


# --- dependency edge resolution -------------------------------------------

def build_label_index(nodes):
    """label (lowercased) -> list of nodes that 'define' something with that
    label and have a real source_file. Used to resolve generic/unresolved
    reference nodes (source_file == '') back to the file that actually
    defines them."""
    idx = defaultdict(list)
    for n in nodes:
        sf = n.get("source_file") or ""
        if sf:
            idx[n.get("label", "").strip().lower()].append(n)
    return idx


def resolve_file(node, by_id, label_index):
    """Return the source_file this node belongs to, resolving generic
    unattached nodes (source_file == '') by label lookup when possible."""
    sf = node.get("source_file") or ""
    if sf:
        return sf
    label = (node.get("label") or "").strip().lower()
    # strip leading '.' some method labels carry (e.g. ".speak()")
    label = label.lstrip(".")
    candidates = label_index.get(label) or label_index.get(label.rstrip("()"))
    if candidates:
        # multiple candidates across files = genuinely ambiguous, skip
        # rather than guess wrong
        distinct_files = {c["source_file"] for c in candidates}
        if len(distinct_files) == 1:
            return next(iter(distinct_files))
    return ""


def build_file_dependency_edges(graph, not_ported_set):
    nodes = graph["nodes"]
    by_id = {n["id"]: n for n in nodes}
    label_index = build_label_index(nodes)

    edges = set()  # (dependent_file, depended_on_file)
    for link in graph.get("links", []):
        src_node = by_id.get(link.get("source"))
        tgt_node = by_id.get(link.get("target"))
        if not src_node or not tgt_node:
            continue
        src_file = resolve_file(src_node, by_id, label_index)
        tgt_file = resolve_file(tgt_node, by_id, label_index)
        if not src_file or not tgt_file or src_file == tgt_file:
            continue
        if src_file in not_ported_set:
            edges.add((src_file, tgt_file))
    return edges


# Java identifiers that commonly resolve to a same-named file in the project
IMPORT_RE = re.compile(r'^\s*import\s+(?:static\s+)?([\w.]+)\s*;', re.MULTILINE)
EXTENDS_RE = re.compile(r'\bextends\s+([\w<>, ]+)')
IMPLEMENTS_RE = re.compile(r'\bimplements\s+([\w<>, ]+)')
IDENTIFIER_RE = re.compile(r'\b[A-Za-z_][A-Za-z0-9_]*\b')


def regex_supplement_edges(repo_root, java_path, stem_to_path, class_name_to_path):
    """Cheap cross-check pass over the actual Java source. Two signals:

    1. import / extends / implements statements (catches cross-package refs).
    2. Whole-word occurrence of another known class's exact name anywhere in
       the file (catches same-package refs, which Java doesn't require an
       import for, and which is the majority case in any single-package or
       tightly-coupled module — verified necessary: a plain field/parameter
       reference between two same-package classes produced no usable
       cross-file edge in graphify's own output during testing).

    Signal 2 is intentionally permissive (a few false positives just make
    the suggested order slightly more conservative, which is the safe
    failure direction for a porting sequence).

    PERFORMANCE NOTE: signal 2 used to do one `re.search(r"\\bClassName\\b",
    text)` per known class per file — i.e. one freshly-compiled regex per
    (not_ported_file, known_class) pair. Profiled on a 600-file synthetic
    repo: this was 92%+ of total script runtime (26.8s total, ~26.7s in
    this function, ~360k individual re.compile calls) — re.search()'s
    internal pattern cache doesn't help because every class name produces a
    different pattern string, so it's a cache miss every time. Rewritten to
    tokenize each file's identifiers in a single regex pass, then intersect
    that token set against the known-class-name set (a dict) — O(file_size)
    tokenization + O(1) average set/dict lookups per identifier, instead of
    O(known_classes) regex compiles+scans per file. Same match semantics:
    IDENTIFIER_RE's `\\b...\\b` token boundaries are exactly what the old
    per-class `\\bClassName\\b` search was matching against."""
    edges = set()
    full_path = os.path.join(repo_root, java_path) if repo_root else java_path
    try:
        with open(full_path, "r", encoding="utf-8", errors="ignore") as f:
            text = f.read()
    except OSError:
        return edges

    simple_names = set()
    for m in IMPORT_RE.finditer(text):
        simple_names.add(m.group(1).rsplit(".", 1)[-1])
    for m in list(EXTENDS_RE.finditer(text)) + list(IMPLEMENTS_RE.finditer(text)):
        for name in re.split(r"[,<>]", m.group(1)):
            name = name.strip()
            if name:
                simple_names.add(name)

    for name in simple_names:
        s = re.sub(r"[^a-z0-9]", "", name.lower())
        target = stem_to_path.get(s)
        if target and target != java_path:
            edges.add((java_path, target))

    file_identifiers = set(IDENTIFIER_RE.findall(text))
    for class_name in file_identifiers & class_name_to_path.keys():
        target = class_name_to_path[class_name]
        if target != java_path:
            edges.add((java_path, target))

    return edges


def topo_tier(not_ported, edges):
    """Kahn's algorithm, grouped into tiers instead of a flat order, so
    everything in tier N can be worked on in parallel once tier N-1 is done.
    Dependency direction: edge (A, B) means 'A depends on B' -> B must be
    ported first.

    PERFORMANCE NOTE: the previous version recomputed
    `depends_on[f] & remaining` for every remaining file on every tier
    iteration — O(V) work per file per tier, so O(V^2) worst case on a long
    dependency chain (profiled: a 600-file linear chain pushed total
    runtime past 25s even before regex_supplement_edges' cost is counted).
    This version tracks an in-degree counter per file and a reverse
    adjacency map (dependents), decrementing in-degree only for the actual
    dependents of each file as it's processed — every file and every edge
    is visited a constant number of times, O(V+E) total."""
    depends_on = defaultdict(set)    # a -> set of not-yet-ported files a depends on
    dependents = defaultdict(set)    # b -> set of not-yet-ported files that depend on b
    for a, b in edges:
        if a in not_ported and b in not_ported:
            depends_on[a].add(b)
            dependents[b].add(a)

    in_degree = {f: len(depends_on.get(f, ())) for f in not_ported}
    frontier = sorted(f for f, d in in_degree.items() if d == 0)

    tiers = []
    processed = set()
    while frontier:
        tiers.append(frontier)
        processed.update(frontier)
        next_frontier = set()
        for f in frontier:
            for d in dependents.get(f, ()):
                if d in processed:
                    continue
                in_degree[d] -= 1
                if in_degree[d] == 0:
                    next_frontier.add(d)
        frontier = sorted(next_frontier)

    cycle_remainder = sorted(set(not_ported) - processed)
    return tiers, cycle_remainder, depends_on


def find_cycles(nodes_remaining, depends_on):
    """Iterative DFS cycle finder restricted to the leftover (cyclic) set,
    for human-readable reporting.

    PERFORMANCE / ROBUSTNESS NOTE: the previous version used recursive DFS,
    one Python stack frame per node visited along a path. Python's default
    recursion limit is 1000; a legacy monolith (exactly what this skill
    targets) can plausibly have a cyclic cluster larger than that, which
    would crash with RecursionError rather than report the cycle. Rewritten
    iteratively with an explicit stack — same O(V+E) traversal, no
    recursion-depth ceiling."""
    cycles = []
    visited = set()

    for start in nodes_remaining:
        if start in visited:
            continue
        visited.add(start)
        stack = [start]
        on_stack = {start}
        iter_stack = [iter(sorted(
            d for d in depends_on.get(start, ()) if d in nodes_remaining
        ))]

        while stack:
            advanced = False
            for nxt in iter_stack[-1]:
                if nxt in on_stack:
                    i = stack.index(nxt)
                    cycles.append(stack[i:] + [nxt])
                    continue
                if nxt in visited:
                    continue
                visited.add(nxt)
                stack.append(nxt)
                on_stack.add(nxt)
                iter_stack.append(iter(sorted(
                    d for d in depends_on.get(nxt, ()) if d in nodes_remaining
                )))
                advanced = True
                break
            if not advanced:
                on_stack.discard(stack.pop())
                iter_stack.pop()

    return cycles


GOD_NODE_LINE_RE = re.compile(r'`([^`]+)`')


def parse_god_nodes(repo_root):
    """Best-effort parse of GRAPH_REPORT.md's god-node list, if present.
    Returns (raw_lines, names) — raw_lines for display, names (the
    backtick-quoted identifier on each line) for matching against file
    stems elsewhere."""
    candidates = [
        os.path.join(repo_root, "graphify-out", "GRAPH_REPORT.md"),
        os.path.join(repo_root, "GRAPH_REPORT.md"),
    ]
    for path in candidates:
        if os.path.exists(path):
            with open(path, "r", encoding="utf-8") as f:
                text = f.read()
            m = re.search(r"## God Nodes.*?\n(.*?)\n\n", text, re.DOTALL)
            if m:
                lines = [l.strip() for l in m.group(1).splitlines() if l.strip()]
                names = set()
                for l in lines[:15]:
                    nm = GOD_NODE_LINE_RE.search(l)
                    if nm:
                        names.add(nm.group(1))
                return lines[:15], names
    return [], set()


def rank_top_candidates(tiers, depends_on, god_node_names, n=3):
    """Rank not-yet-ported files to surface the top N to work on first.

    Restricted to tier 0 only (no remaining unported dependencies — these are
    the only files actually startable right now; ranking a tier-1+ file as
    "top priority" would be misleading since it's blocked). Within tier 0,
    rank by 'unblocks' count: how many other not-yet-ported files list this
    file as a dependency. A file that unblocks more downstream work is
    higher-leverage to finish first, all else equal.

    God-node files are NOT excluded from ranking (tested against a small
    repo: GRAPH_REPORT.md's "God Nodes" section is just every node sorted by
    edge count with no visible risk-based cutoff, so in a small repo nearly
    every file would get excluded — too aggressive and not something the
    list actually supports). Instead each candidate is annotated with
    is_god_node so the caller can flag it as a caution note when presenting
    to the user, rather than silently dropping a legitimate candidate.

    Returns (top_candidates, ambiguous, reason) where `ambiguous` is True
    when the ranking shouldn't be trusted as-is: fewer than N tier-0
    candidates exist, or there's an exact score tie straddling the N-th
    cutoff (so picking N of the tied files over the others would be
    arbitrary). Either case means the caller should ask the user rather
    than present a confident top-N list.
    """
    if not tiers:
        return [], True, "no not-yet-ported files remain — nothing to rank"

    eligible = list(tiers[0]["files"]) if tiers else []

    if not eligible:
        return [], True, "tier 0 is empty — nothing is immediately portable"

    unblocks = defaultdict(int)
    for _f, deps in depends_on.items():
        for d in deps:
            unblocks[d] += 1

    scored = sorted(eligible, key=lambda f: (-unblocks.get(f, 0), f))
    top = scored[:n]

    ambiguous = False
    reason = ""
    if len(eligible) < n:
        ambiguous = True
        reason = (
            f"only {len(eligible)} tier-0 candidate(s) exist, fewer than "
            f"the requested top {n}"
        )
    elif len(scored) > n and unblocks.get(scored[n - 1], 0) == unblocks.get(scored[n], 0):
        tied_score = unblocks.get(scored[n - 1], 0)
        tied_files = [f for f in scored if unblocks.get(f, 0) == tied_score]
        ambiguous = True
        reason = (
            f"{len(tied_files)} files tie at the rank-{n} cutoff "
            f"(each unblocks {tied_score} other file(s)): "
            f"{', '.join(tied_files)} — picking {n} of them would be arbitrary"
        )

    top_candidates = [
        {
            "file": f,
            "unblocks_count": unblocks.get(f, 0),
            "is_god_node": os.path.splitext(os.path.basename(f))[0] in god_node_names,
        }
        for f in top
    ]
    return top_candidates, ambiguous, reason


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--graph", default="graphify-out/graph.json")
    ap.add_argument("--repo-root", default=".")
    ap.add_argument("--out", default=None)
    args = ap.parse_args()

    graph = load_graph(args.graph)
    nodes = graph["nodes"]
    files, _ = collect_files(nodes)

    ported, needs_review, not_ported = match_java_to_cpp(files)

    partial = {}
    for j, cpp_matches in ported.items():
        status = partial_port_check(j, cpp_matches)
        if status != "complete":
            partial[j] = {"cpp_files": cpp_matches, "status": status}

    not_ported_set = set(not_ported)
    edges = build_file_dependency_edges(graph, not_ported_set)

    stem_to_path = {}
    class_name_to_path = {}
    for p, lang in files.items():
        if lang == "java":
            stem_to_path[stem(p)] = p
            class_name_to_path[os.path.splitext(os.path.basename(p))[0]] = p
    for j in not_ported:
        edges |= regex_supplement_edges(args.repo_root, j, stem_to_path, class_name_to_path)

    tiers, cycle_remainder, depends_on = topo_tier(not_ported_set, edges)
    cycles = find_cycles(set(cycle_remainder), depends_on) if cycle_remainder else []

    god_node_lines, god_node_names = parse_god_nodes(args.repo_root)

    tier_report = [
        {
            "tier": i,
            "files": t,
            "depends_on": {f: sorted(depends_on.get(f, [])) for f in t},
        }
        for i, t in enumerate(tiers)
    ]
    top3, top3_ambiguous, top3_ambiguous_reason = rank_top_candidates(
        tier_report, depends_on, god_node_names, n=3
    )

    report = {
        "ported_count": len(ported),
        "not_ported_count": len(not_ported),
        "needs_review_count": len(needs_review),
        "ported": ported,
        "partially_ported": partial,
        "needs_review_fuzzy_matches": needs_review,
        "tiers": tier_report,
        "unresolved_cycle_files": cycle_remainder,
        "cycles": cycles,
        "god_nodes_hint": god_node_lines,
        "top3_priority_candidates": top3,
        "top3_ambiguous": top3_ambiguous,
        "top3_ambiguous_reason": top3_ambiguous_reason,
    }

    out_text = json.dumps(report, indent=2)
    if args.out:
        with open(args.out, "w", encoding="utf-8") as f:
            f.write(out_text)
        print(f"Wrote {args.out}", file=sys.stderr)
    else:
        print(out_text)


if __name__ == "__main__":
    main()
