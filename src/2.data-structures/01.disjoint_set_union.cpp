/**
 * @file 01.disjoint_set_union.cpp
 * @brief Union-Find (Disjoint Set Union) with path compression and union by size.
 * @complexity Amortised O(alpha(N)) per operation.
 * @usage
 *   DisjointSetUnion dsu(n);
 *   dsu.unite(u, v);
 *   if (dsu.find(u) == dsu.find(v)) { ... }
 * @related 3.graphs/06.prim_minimum_spanning_tree.cpp
 * @related 5.math/03.inversion_count_fenwick.cpp
 */

#include <bits/stdc++.h>
using namespace std;

struct DisjointSetUnion {
    int n;
    vector<int> parent, size;

    explicit DisjointSetUnion(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        parent.resize(n);
        size.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

    int component_size(int x) { return size[find(x)]; }
};

#ifdef RUN_EXAMPLE
int main() {
    DisjointSetUnion dsu(5);
    dsu.unite(0, 1);
    dsu.unite(3, 4);
    cout << boolalpha;
    cout << (dsu.find(0) == dsu.find(1)) << "\n"; // true
    cout << (dsu.find(0) == dsu.find(2)) << "\n"; // false
    dsu.unite(1, 2);
    cout << dsu.component_size(2) << "\n";        // 3
    return 0;
}
#endif
