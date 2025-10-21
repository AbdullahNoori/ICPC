/**
 * @file 01.teleporting_cities.cpp
 * @brief ICPC problem: shortest path with zero-cost teleports.
 * @solution Dijkstra on standard adjacency list (non-negative weights).
 * @complexity O((N + M + K) log N).
 * @related 3.graphs/04.dijkstra_shortest_path.cpp
 * @related 3.graphs/05.zero_one_bfs.cpp
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    if (!(cin >> N >> M >> K)) return 0;
    vector<vector<pair<int, int>>> g(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        g[u].push_back({v, t});
        g[v].push_back({u, t});
    }
    for (int i = 0; i < K; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, 0});
    }

    const long long INF = numeric_limits<long long>::max();
    vector<long long> dist(N + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[1] = 0;
    pq.push({0, 1});

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

    cout << (dist[N] == INF ? -1 : dist[N]) << "\n";
    return 0;
}
