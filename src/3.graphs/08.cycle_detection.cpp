/**
 * @file 08.cycle_detection.cpp
 * @brief Cycle detection helpers for undirected and directed graphs.
 * @complexity O(N + M).
 * @usage
 *   bool und = has_cycle_undirected(graph);
 *   bool dir = has_cycle_directed(graph);
 * @related 3.graphs/02.topological_sort_kahn.cpp
 * @related 3.graphs/05.zero_one_bfs.cpp
 */

#include <bits/stdc++.h>
using namespace std;

bool has_cycle_undirected(const vector<vector<int>>& g) {
    int n = static_cast<int>(g.size());
    vector<int> vis(n, 0);
    function<bool(int, int)> dfs = [&](int u, int p) {
        vis[u] = 1;
        for (int v : g[u]) {
            if (!vis[v]) {
                if (dfs(v, u)) return true;
            } else if (v != p) {
                return true;
            }
        }
        return false;
    };
    for (int u = 0; u < n; ++u)
        if (!vis[u] && dfs(u, -1))
            return true;
    return false;
}

bool has_cycle_directed(const vector<vector<int>>& g) {
    int n = static_cast<int>(g.size());
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : g[u])
            ++indeg[v];
    queue<int> q;
    for (int u = 0; u < n; ++u)
        if (indeg[u] == 0)
            q.push(u);
    int seen = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++seen;
        for (int v : g[u])
            if (--indeg[v] == 0)
                q.push(v);
    }
    return seen != n;
}

#ifdef RUN_EXAMPLE
int main() {
    vector<vector<int>> und = {
        {1},    // 0
        {0, 2}, // 1
        {1, 3}, // 2
        {2}     // 3
    };
    cout << boolalpha << has_cycle_undirected(und) << "\n"; // false
    und[3].push_back(1);
    und[1].push_back(3);
    cout << has_cycle_undirected(und) << "\n"; // true

    vector<vector<int>> dir = {
        {1}, {2}, {3}, {}
    };
    cout << has_cycle_directed(dir) << "\n"; // false
    dir[3].push_back(1);
    cout << has_cycle_directed(dir) << "\n"; // true
    return 0;
}
#endif
