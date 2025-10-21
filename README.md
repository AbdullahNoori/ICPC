# 2025 ICPC Reference Toolkit

This toolkit consolidates reusable snippets extracted from the `BaseBallHuh/` practice solutions and the legacy `ICPC-TRD/` notebook.  Code was normalized to modern C++17, annotated with complexity notes, and cross-linked so the folder can serve as a drop-in competitive programming reference.

## Layout
- `src/1.general/` – templates, fast I/O utilities.
- `src/2.data-structures/` – Fenwick tree, segment tree, disjoint set union, and more.
- `src/3.graphs/` – traversal, shortest paths, MST, SCC, and graph DP patterns.
- `src/4.geometry/` – planar geometry helpers.
- `src/5.math/` – modular arithmetic and number theory utilities.
- `src/6.strings/` – pattern matching and parentheses tooling.
- `src/7.dynamic-programming/` – classic DP transitions and optimisations.
- `src/8.misc/` – handy tricks (bit operations, sliding windows, subset generation).
- `src/9.practice-solutions/` – polished ICPC-style solutions grouped by topic.

Each snippet carries a header with: purpose, complexity, usage notes, and references to related files inside `2025_ICPC/src/`.  Example `main` drivers are wrapped in `#ifdef RUN_EXAMPLE` so files can compile standalone or be included as headers.

## Using the notebook
1. Copy the required file into your contest project or include it as a header.
2. If you want to run the embedded sample, compile with `-DRUN_EXAMPLE`.
3. Adjust namespaces/constants as needed; all code sticks to STL and C++17.

When adding new material, follow the same header style and reference additional algorithms with `@related` comments to keep the index consistent.
