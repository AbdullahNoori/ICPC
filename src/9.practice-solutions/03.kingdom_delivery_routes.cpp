/**
 * @file 03.kingdom_delivery_routes.cpp
 * @brief Shortest routes with up to K reinforced edges (half cost).
 * @solution Dijkstra over augmented states.
 * @complexity O(K * (N + M) log (K * N)).
 * @related 3.graphs/07.shortest_path_with_edge_discounts.cpp
 * @related 3.graphs/04.dijkstra_shortest_path.cpp
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    if (!(cin >> N >> M >> K)) return 0;
    vector<vector<pair<int, long long>>> g(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        long long t;
        cin >> u >> v >> t;
        g[u].push_back({v, t});
        g[v].push_back({u, t});
    }

    const long long INF = numeric_limits<long long>::max();
    vector<vector<long long>> dist(N + 1, vector<long long>(K + 1, INF));
    using State = tuple<long long, int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[1][0] = 0;
    pq.emplace(0, 1, 0);

    while (!pq.empty()) {
        auto [d, u, used] = pq.top();
        pq.pop();
        if (d != dist[u][used]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v][used] > d + w) {
                dist[v][used] = d + w;
                pq.emplace(dist[v][used], v, used);
            }
            if (used < K) {
                long long half = d + w / 2;
                if (dist[v][used + 1] > half) {
                    dist[v][used + 1] = half;
                    pq.emplace(half, v, used + 1);
                }
            }
        }
    }

    long long ans = *min_element(dist[N].begin(), dist[N].end());
    cout << ans << "\n";
    return 0;
}
