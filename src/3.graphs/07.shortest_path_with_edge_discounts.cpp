/**
 * @file 07.shortest_path_with_edge_discounts.cpp
 * @brief Dijkstra on augmented state space (node, used_discounts).
 * @details Allows using up to K discounted edges where cost is halved.
 * @complexity O(K * (N + M) log (K * N)).
 * @usage
 *   auto ans = shortest_path_with_discounts(graph, 0, target, K);
 * @related 3.graphs/04.dijkstra_shortest_path.cpp
 * @related 9.practice-solutions/03.kingdom_delivery_routes.cpp
 */

#include <bits/stdc++.h>
using namespace std;

long long shortest_path_with_discounts(
    const vector<vector<pair<int, long long>>>& g,
    int source,
    int target,
    int discounts) {
    const long long INF = numeric_limits<long long>::max();
    int n = static_cast<int>(g.size());
    vector<vector<long long>> dist(n, vector<long long>(discounts + 1, INF));
    using State = tuple<long long, int, int>; // dist, node, used
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[source][0] = 0;
    pq.emplace(0, source, 0);

    while (!pq.empty()) {
        auto [d, u, used] = pq.top();
        pq.pop();
        if (d != dist[u][used]) continue;
        if (u == target) return d;
        for (auto [v, w] : g[u]) {
            if (dist[v][used] > d + w) {
                dist[v][used] = d + w;
                pq.emplace(dist[v][used], v, used);
            }
            if (used < discounts) {
                long long discounted = d + w / 2;
                if (dist[v][used + 1] > discounted) {
                    dist[v][used + 1] = discounted;
                    pq.emplace(discounted, v, used + 1);
                }
            }
        }
    }
    return *min_element(dist[target].begin(), dist[target].end());
}

#ifdef RUN_EXAMPLE
int main() {
    int n = 5, k = 1;
    vector<vector<pair<int, long long>>> g(n);
    auto add_edge = [&](int u, int v, long long w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };
    add_edge(0, 1, 5);
    add_edge(1, 2, 4);
    add_edge(2, 3, 7);
    add_edge(1, 3, 20);
    add_edge(3, 4, 3);
    cout << shortest_path_with_discounts(g, 0, 4, k) << "\n"; // 5 + 4/2 + 7 + 3 = 17
    return 0;
}
#endif
