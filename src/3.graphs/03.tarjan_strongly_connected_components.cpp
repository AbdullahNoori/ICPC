/**
 * @file 03.tarjan_strongly_connected_components.cpp
 * @brief Tarjan's algorithm to label SCCs and build condensation DAG.
 * @complexity O(N + M).
 * @usage
 *   TarjanSCC scc(graph);
 *   auto comp = scc.component_of(); // size N
 *   auto dag = scc.condensation_dag(); // size = comp_count()
 * @related 3.graphs/02.topological_sort_kahn.cpp
 * @related 9.practice-solutions/05.airport_reinforcement_scc.cpp
 */

#include <bits/stdc++.h>
using namespace std;

struct TarjanSCC {
    int n;
    const vector<vector<int>>& g;
    vector<int> disc, low, comp, stack_;
    vector<char> in_stack;
    int timer = 0, comp_cnt = 0;

    explicit TarjanSCC(const vector<vector<int>>& graph)
        : n(static_cast<int>(graph.size())), g(graph),
          disc(n, -1), low(n, 0), comp(n, -1), in_stack(n, 0) {
        stack_.reserve(n);
        for (int v = 0; v < n; ++v)
            if (disc[v] == -1)
                dfs(v);
    }

    void dfs(int u) {
        disc[u] = low[u] = timer++;
        stack_.push_back(u);
        in_stack[u] = 1;
        for (int v : g[u]) {
            if (disc[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }
        if (low[u] == disc[u]) {
            while (true) {
                int v = stack_.back();
                stack_.pop_back();
                in_stack[v] = 0;
                comp[v] = comp_cnt;
                if (v == u) break;
            }
            ++comp_cnt;
        }
    }

    const vector<int>& component_of() const { return comp; }
    int component_count() const { return comp_cnt; }

    vector<vector<int>> condensation_dag() const {
        vector<vector<int>> dag(comp_cnt);
        for (int u = 0; u < n; ++u) {
            for (int v : g[u]) {
                if (comp[u] != comp[v])
                    dag[comp[u]].push_back(comp[v]);
            }
        }
        for (auto& edges : dag) {
            sort(edges.begin(), edges.end());
            edges.erase(unique(edges.begin(), edges.end()), edges.end());
        }
        return dag;
    }
};

#ifdef RUN_EXAMPLE
int main() {
    vector<vector<int>> g = {
        {1},        // 0
        {2},        // 1
        {0, 3},     // 2
        {4},        // 3
        {5, 7},     // 4
        {6},        // 5
        {4, 8},     // 6
        {8},        // 7
        {}          // 8
    };
    TarjanSCC scc(g);
    auto comp = scc.component_of();
    cout << "Components:\n";
    for (int v = 0; v < (int)comp.size(); ++v) {
        cout << "node " << v << " -> comp " << comp[v] << "\n";
    }
    auto dag = scc.condensation_dag();
    cout << "Condensation edges:\n";
    for (int u = 0; u < (int)dag.size(); ++u)
        for (int v : dag[u])
            cout << u << " -> " << v << "\n";
    return 0;
}
#endif
