/**
 * @file 05.zero_one_bfs.cpp
 * @brief 0-1 BFS for graphs with edge weights in {0, 1}.
 * @complexity O(N + M).
 * @usage
 *   ZeroOneBFS solver(n);
 *   solver.add_edge(u, v, cost, /*undirected=*/false);
 *   auto dist = solver.run(source);
 * @related 3.graphs/04.dijkstra_shortest_path.cpp
 * @related 9.practice-solutions/02.rescue_mission_grid.cpp
 */

#include <bits/stdc++.h>
using namespace std;

struct ZeroOneBFS {
    struct Edge { int to; int w; };
    int n;
    vector<vector<Edge>> g;

    explicit ZeroOneBFS(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
    }

    void add_edge(int u, int v, int w, bool undirected = false) {
        assert(w == 0 || w == 1);
        g[u].push_back({v, w});
        if (undirected) g[v].push_back({u, w});
    }

    vector<int> run(int source) const {
        const int INF = numeric_limits<int>::max();
        vector<int> dist(n, INF);
        deque<int> dq;
        dist[source] = 0;
        dq.push_back(source);
        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();
            for (auto [v, w] : g[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    if (w == 0) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }
        return dist;
    }
};

#ifdef RUN_EXAMPLE
int main() {
    ZeroOneBFS solver(6);
    solver.add_edge(0, 1, 0, true); // portal
    solver.add_edge(1, 2, 1, true);
    solver.add_edge(0, 3, 1, true);
    solver.add_edge(3, 4, 1, true);
    solver.add_edge(4, 5, 1, true);
    solver.add_edge(2, 5, 0, true); // teleport
    auto dist = solver.run(0);
    for (int i = 0; i < (int)dist.size(); ++i)
        cout << "dist[0 -> " << i << "] = " << dist[i] << "\n";
    return 0;
}
#endif
