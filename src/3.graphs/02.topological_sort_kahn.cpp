/**
 * @file 02.topological_sort_kahn.cpp
 * @brief Kahn's algorithm for topological order in DAGs.
 * @complexity O(N + M).
 * @usage
 *   auto order = topological_sort(graph);
 *   if (order.empty()) => cycle.
 * @related 3.graphs/08.cycle_detection.cpp
 * @related 7.dynamic-programming/01.knapsack_01.cpp
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> topological_sort(const vector<vector<int>>& g) {
    int n = static_cast<int>(g.size());
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : g[u])
            ++indeg[v];

    queue<int> q;
    for (int u = 0; u < n; ++u)
        if (indeg[u] == 0)
            q.push(u);

    vector<int> order;
    order.reserve(n);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : g[u]) {
            if (--indeg[v] == 0)
                q.push(v);
        }
    }
    if ((int)order.size() != n) return {};
    return order;
}

#ifdef RUN_EXAMPLE
int main() {
    vector<vector<int>> g = {
        {1},      // 0 -> 1
        {2},      // 1 -> 2
        {3},      // 2 -> 3
        {},       // 3
        {1, 2, 3} // 4 -> 1,2,3
    };
    auto order = topological_sort(g);
    if (order.empty()) {
        cout << "Graph has a cycle\n";
    } else {
        for (int v : order) cout << v << ' ';
        cout << '\n';
    }
    return 0;
}
#endif
