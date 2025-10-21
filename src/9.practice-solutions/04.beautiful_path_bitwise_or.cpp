/**
 * @file 04.beautiful_path_bitwise_or.cpp
 * @brief Shortest path minimising bitwise OR of edge weights.
 * @solution Dijkstra-like relaxation using bitwise OR as cost accumulation.
 * @complexity O((N + M) log N).
 * @related 3.graphs/04.dijkstra_shortest_path.cpp
 * @related 8.misc/01.bit_manipulation_tricks.cpp
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    int A, B;
    cin >> A >> B;

    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF);
    using State = pair<int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[A] = 0;
    pq.push({0, A});

    while (!pq.empty()) {
        auto [val, u] = pq.top();
        pq.pop();
        if (val != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            int next = val | w;
            if (next < dist[v]) {
                dist[v] = next;
                pq.push({next, v});
            }
        }
    }

    cout << (dist[B] == INF ? -1 : dist[B]) << "\n";
    return 0;
}
