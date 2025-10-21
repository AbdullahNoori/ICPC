/**
 * @file 06.prim_minimum_spanning_tree.cpp
 * @brief Prim's algorithm (lazy variant) for MST on weighted undirected graphs.
 * @complexity O(M log N).
 * @usage
 *   auto [total, taken] = prim_mst(n, edges);
 * @related 2.data-structures/01.disjoint_set_union.cpp
 * @related 3.graphs/04.dijkstra_shortest_path.cpp
 */

#include <bits/stdc++.h>
using namespace std;

struct MSTResult {
    long long total_weight;
    vector<int> parent;
};

MSTResult prim_mst(int n, const vector<tuple<int, int, int>>& edges) {
    vector<vector<pair<int, int>>> g(n);
    for (auto [u, v, w] : edges) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    const long long INF = numeric_limits<long long>::max();
    vector<long long> key(n, INF);
    vector<int> parent(n, -1);
    vector<char> used(n, 0);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

    key[0] = 0;
    pq.push({0, 0});
    long long total = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        if (used[u]) continue;
        used[u] = 1;
        total += w;
        for (auto [v, weight] : g[u]) {
            if (!used[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    return {total, parent};
}

#ifdef RUN_EXAMPLE
int main() {
    vector<tuple<int, int, int>> edges = {
        {0, 1, 4}, {0, 7, 8}, {1, 7, 11}, {1, 2, 8},
        {7, 8, 7}, {7, 6, 1}, {2, 8, 2},  {8, 6, 6},
        {2, 3, 7}, {2, 5, 4}, {6, 5, 2},  {3, 5, 14},
        {3, 4, 9}, {5, 4, 10}
    };
    auto [total, parent] = prim_mst(9, edges);
    cout << "MST weight: " << total << "\n";
    for (int v = 0; v < (int)parent.size(); ++v) {
        cout << "parent[" << v << "] = " << parent[v] << "\n";
    }
    return 0;
}
#endif
