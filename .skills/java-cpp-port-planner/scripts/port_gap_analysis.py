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

USAGE:
    python3 port_gap_analysis.py --graph graphify-out/graph.json --repo-root .

OUTPUT:
    Prints a JSON report to stdout (or --out <path>) with:
      - ported / partially_ported / not_ported Java files
      - a tiered list of not_ported files in dependency order (tier 0 = no
        remaining unported dependencies = portable right now)
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
    backlog items behind a guess)."""
    java_files = [p for p, lang in files.items() if lang == "java"]
    cpp_files = [p for p, lang in files.items() if lang == "cpp"]
    cpp_by_stem = defaultdict(list)
    for c in cpp_files:
        cpp_by_stem[stem(c)].append(c)

    ported = {}          # java_path -> list of matched cpp paths
    needs_review = {}     # java_path -> list of (cpp_path, score)
    not_ported = []

    for j in java_files:
        s = stem(j)
        if s in cpp_by_stem:
            ported[j] = cpp_by_stem[s]
            continue
        suggestion = []
        if fuzz:
            for c in cpp_files:
                score = fuzz.ratio(s, stem(c))
                if score >= 75:
                    suggestion.append((c, round(score, 1)))
        if suggestion:
            suggestion.sort(key=lambda t: -t[1])
            needs_review[j] = suggestion[:3]
        else:
            not_ported.append(j)

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
    failure direction for a porting sequence)."""
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

    for class_name, target in class_name_to_path.items():
        if target == java_path:
            continue
        if re.search(r"\b" + re.escape(class_name) + r"\b", text):
            edges.add((java_path, target))

    return edges


def topo_tier(not_ported, edges):
    """Kahn's algorithm, but grouped into tiers instead of a flat order, so
    everything in tier N can be worked on in parallel once tier N-1 is done.
    Dependency direction: edge (A, B) means 'A depends on B' -> B must be
    ported first."""
    depends_on = defaultdict(set)
    for a, b in edges:
        if a in not_ported and b in not_ported:
            depends_on[a].add(b)

    remaining = set(not_ported)
    tiers = []
    while remaining:
        # a file is ready if every not_ported file it depends on is already
        # placed in an earlier tier
        ready = {f for f in remaining if not (depends_on[f] & remaining)}
        if not ready:
            # cycle: everything left depends on something also left
            break
        tiers.append(sorted(ready))
        remaining -= ready

    cycle_remainder = sorted(remaining)
    return tiers, cycle_remainder, depends_on


def find_cycles(nodes_remaining, depends_on):
    """Simple DFS cycle finder restricted to the leftover (cyclic) set, for
    human-readable reporting."""
    cycles = []
    visited = set()
    stack = []

    def dfs(node):
        if node in stack:
            i = stack.index(node)
            cycles.append(stack[i:] + [node])
            return
        if node in visited:
            return
        visited.add(node)
        stack.append(node)
        for dep in depends_on.get(node, ()):
            if dep in nodes_remaining:
                dfs(dep)
        stack.pop()

    for n in nodes_remaining:
        dfs(n)
    return cycles


def parse_god_nodes(repo_root):
    """Best-effort parse of GRAPH_REPORT.md's god-node list, if present."""
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
                return lines[:15]
    return []


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

    god_nodes = parse_god_nodes(args.repo_root)

    report = {
        "ported_count": len(ported),
        "not_ported_count": len(not_ported),
        "needs_review_count": len(needs_review),
        "ported": ported,
        "partially_ported": partial,
        "needs_review_fuzzy_matches": needs_review,
        "tiers": [
            {
                "tier": i,
                "files": t,
                "depends_on": {f: sorted(depends_on.get(f, [])) for f in t},
            }
            for i, t in enumerate(tiers)
        ],
        "unresolved_cycle_files": cycle_remainder,
        "cycles": cycles,
        "god_nodes_hint": god_nodes,
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