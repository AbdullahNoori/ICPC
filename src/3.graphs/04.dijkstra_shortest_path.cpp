/**
 * @file 04.dijkstra_shortest_path.cpp
 * @brief Dijkstra's algorithm for non-negative weighted graphs.
 * @complexity O((N + M) log N) with binary heap.
 * @usage
 *   Dijkstra dij(n);
 *   dij.add_edge(u, v, w, /*undirected=*/true);
 *   auto dist = dij.run(source);
 * @related 3.graphs/05.zero_one_bfs.cpp
 * @related 9.practice-solutions/01.teleporting_cities.cpp
 */

#include <bits/stdc++.h>
using namespace std;

struct Dijkstra {
    struct Edge { int to; long long w; };
    int n;
    vector<vector<Edge>> g;

    explicit Dijkstra(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
    }

    void add_edge(int u, int v, long long w, bool undirected = false) {
        g[u].push_back({v, w});
        if (undirected) g[v].push_back({u, w});
    }

    vector<long long> run(int source) const {
        const long long INF = numeric_limits<long long>::max();
        vector<long long> dist(n, INF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        dist[source] = 0;
        pq.push({0, source});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;
            for (auto [v, w] : g[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};

#ifdef RUN_EXAMPLE
int main() {
    Dijkstra dij(6);
    dij.add_edge(0, 1, 7, true);
    dij.add_edge(0, 2, 9, true);
    dij.add_edge(0, 5, 14, true);
    dij.add_edge(1, 2, 10, true);
    dij.add_edge(1, 3, 15, true);
    dij.add_edge(2, 3, 11, true);
    dij.add_edge(2, 5, 2, true);
    dij.add_edge(3, 4, 6, true);
    dij.add_edge(4, 5, 9, true);
    auto dist = dij.run(0);
    for (int i = 0; i < (int)dist.size(); ++i) {
        cout << "dist[0 -> " << i << "] = " << dist[i] << "\n";
    }
    return 0;
}
#endif
